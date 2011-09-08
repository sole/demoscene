import os
import subprocess
import re
import argparse
import sys

def execute(command):
	# redirecting stderr->stdout because ffmpeg outputs its 'error' to stderr
	process = subprocess.Popen(command, shell=True, stderr=subprocess.STDOUT, stdout=subprocess.PIPE).stdout

	lines = []

	while True:
		line = process.readline()
		
		if not line:
			break

		lines.append(line)
	
	return lines

def inspect_file(filename):
	ffout = execute('ffmpeg -i %s' % filename)

	# find video dimensions
	w = None
	h = None
	video_re = re.compile(r"^\s+Stream #\d.\d: Video: .*? (?P<width>\d+)x(?P<height>\d+)")
	for line in ffout:
		match = video_re.match(line)
		if match:
			w = int(match.group('width'))
			h = int(match.group('height'))

	
	return {'width': w, 'height': h}


def process(args):
	print args.in_files, '->', args.out_file

	# inspect all input files to determine max WxH
	max_w = 0
	max_h = 0
	
	crop_h = args.in_crop_top + args.in_crop_bottom

	proper_files = []

	for f in args.in_files:
		props = inspect_file(f)
		w = props['width']
		h = props['height']

		if w is None or h is None:
			print ('Oh no! %s has no size!' % f)
		else:
			h = h - crop_h
			
			if w >= max_w and h >= max_h:
				max_w = w
				max_h = h

			proper_files.append(f)
	
	print "MAX W, H %d %d" % (max_w, max_h)

	# Decide output size
	# We'll try to resample by a multiple of 2
	print 'target is ', args.target_quality
	target = args.target_quality

	if target == 'hd':
		min_w = 1280
		min_h = 800
	elif target == 'full_hd':
		min_w = 1920
		min_h = 1080

	target_w = max_w
	target_h = max_h

	while target_w < min_w and target_h < min_h:
		target_w = target_w * 2
		target_h = target_h * 2

	print 'output target', target_w, target_h

	# foreach input file calculate padding if required, encode
	tmp_files = []
	i = 0
	num_files = len(proper_files)

	for f in proper_files:
		i = i + 1
		props = inspect_file(f)
		w = props['width']
		h = props['height']

		if w is None or h is None:
			continue

		h = h - crop_h
		tmp_out_file = f + '.tmp' + '.' + args.target_format

		if os.path.exists(tmp_out_file):
			print tmp_out_file, 'already exists, skipping'
			continue

		tmp_files.append(tmp_out_file)

		dest_w = w * (target_w / w)
		dest_h = h * (target_h / h)

		pad_w = target_w - dest_w
		pad_h = target_h - dest_h

		video_filter_args = []
		video_filter = ''

		cropping = ''
		if args.in_crop_top > 0 or args.in_crop_bottom > 0:
			cropping = '-croptop %d -cropbottom %d' % (args.in_crop_top, args.in_crop_bottom)
			# It should be the following instead of the deprecated option above
			# but for some reason I can't manage to make it work! It's just ignored! X-(
			#video_filter_args.append('crop=in_w:in_h-%d' % (crop_h))

		if pad_w > 0 or pad_h > 0:
			video_filter_args.append('pad=%d:%d:%d:%d:black' % (target_w, target_h, pad_w / 2, pad_h / 2))

		# Scale is last so that it applies to the cropped/padded input
		video_filter_args.append('scale=%d:%d' % (dest_w, dest_h))

		if len(video_filter_args) > 0:
			video_filter = '-vf ' + ','.join(video_filter_args)
			
		if args.target_format == 'mp4':
			vcodec = 'libx264'
			vpreset = '-vpre slow -vpre baseline'
			acodec = 'libmp3lame'
		else:
			vcodec = 'libvpx'
			vpreset = ''
			acodec = 'libvorbis'
		
		cmd = 'ffmpeg -i %s -sws_flags neighbor+full_chroma_inp %s %s -r 30 -vcodec %s %s -crf 20 -acodec %s -aq 7 -threads 0 -y -f %s %s' % (f, cropping, video_filter, vcodec, vpreset, acodec, args.target_format, tmp_out_file)
		
		#cmd = 'ffmpeg -i %s -sws_flags neighbor+full_chroma_inp %s %s -r 30 -vcodec libx264 -vpre slow -vpre baseline -crf 20 -acodec libmp3lame -aq 7 -threads 0 -y -f %s %s' % (f, cropping, video_filter, args.target_format, tmp_out_file)

		print "ENCODING (%d/%d) %s -> %s" % (i, num_files, f, tmp_out_file)
		print cmd

		i = i + 1

		cmdout=execute(cmd)
		print '\n'.join(cmdout)


		#sys.exit(0)

	# and finally concat all files into one (if required)
	if len(tmp_files) > 1:
		first, rest = tmp_files[0], tmp_files[1:]
		print first

		if args.target_format == 'mp4':
			cmd = 'MP4Box -add %s %s -new %s' % (first, ' '.join(['-cat %s' % t for t in rest]), args.out_file)
		else:
			cmd = 'mkvmerge -o %s %s %s' % (args.out_file, first, ' '.join(['+%s' % t for t in rest]))
		print cmd

		out = execute(cmd)
		print out

	# or simply hint the file so it's got a proper faststart atom etc
	else:
		execute('MP4Box -hint %s' % (tmp_files[0]))
		os.rename(tmp_files[0], args.out_file)

def parse_args():
	parser = argparse.ArgumentParser(description='Prepare captures for uploading')
	parser.add_argument('--in', help='Input files', dest='in_files', metavar='video1 [video2 video3... videoN]', nargs='*', required=True)
	parser.add_argument('--in-crop-top', help='Amount of pixels to crop from top', dest='in_crop_top', type=int, default=0)
	parser.add_argument('--in-crop-bottom', help='Amount of pixels to crop from bottom', dest='in_crop_bottom', type=int, default=0)
	parser.add_argument('--out', help='Out file', dest='out_file', metavar='out.file', required=True)
	parser.add_argument('--target_quality', help='Desired target quality', choices = ['hd', 'full_hd'], default='hd')
	parser.add_argument('--target-format', help='Desired target format', dest='target_format', choices = ['mp4', 'webm'], default='mp4')

	args = parser.parse_args()

	return args

def main(argv=None):

	args = parse_args()
	process(args)


if __name__ == "__main__":
	main()
