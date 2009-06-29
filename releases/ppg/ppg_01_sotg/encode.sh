#!/bin/bash
# This is a simple encoder for converting a video capture done with glc
# to something a bit more palatable by VLC, mplayer et al.
#
# Here's how to capture, once glc has been installed:
# glc-capture --out ./capture.glc -s ./ppg01_sotg_linux
# And then use this script with
# ./encode.sh ./capture.glc
# which will (hopefully) generate a capture.glc.mp4 in this dir.
#
# It might, or might not, work in your computer.
# Based on the sample script provided in glc docs.
#
# Check glc, it's pretty cool: http://nullkey.ath.cx/projects/glc/
# If you use windows instead, have a look at .kkapture: http://www.farb-rausch.de/~fg/kkapture/
# For mac users, I have honestly no idea of what could be used to capture.

mkdir ./tmp
glc-play $1 -o ./tmp/audio.wav -a 1
sox ./tmp/audio.wav ./tmp/audio2.wav remix 1 2 # convert from 6 channels to 2, no idea why do I get 6 channels
lame -hV2 ./tmp/audio2.wav ./tmp/audio.mp3

glc-play $1 -o - -y 1 | mencoder -demuxer y4m - -nosound -ovc x264 -x264encopts qp=18:pass=1 -of avi -o ./tmp/video.avi
glc-play $1 -o - -y 1 | mencoder -demuxer y4m - -audiofile ./tmp/audio.mp3 -oac copy -ovc x264 -x264encopts qp=18:pass=2 -of avi -o ./tmp/video.avi
mv ./tmp/video.avi $1.mp4

