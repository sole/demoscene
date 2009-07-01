#!/usr/bin/env python

"""This is a simple pygtk launcher for the demo, so that you don't need to 
deal with the command line parameters if you don't want to
It only works on linux, though. Maybe if you install python, gtk and pygtk it will
work in your computer too :-)
Feel free to use it as a base for your linux demo launchers!
"""
import pygtk
pygtk.require('2.0')
import gtk
import types
import subprocess
import os

class Launcher:

	def demo_callback(self, widget, data=None):
		
		args = [self.demo_exe]
		
		selected_mode = self.modes_combo.get_active_text()
		dimensions = selected_mode.split("x")
		
		args.append("--width")
		args.append(dimensions[0])
		args.append("--height")
		args.append(dimensions[1])
		
		if self.fullscreen_button.get_active():
			args.append("--fullscreen")
			
		selected_num_samples = self.samples_combo.get_active_text()
		if(selected_num_samples != '0'):
			args.append("--antialias")
			args.append("--antialias-samples")
			args.append(selected_num_samples)
		
		os.execv(self.demo_exe, args)
		
	def die_callback(self, widget, data=None):
		gtk.main_quit()
	
	def destroy(self, widget, data=None):
		gtk.main_quit()
	
	def detect_modes(self):
		output = subprocess.Popen([self.demo_exe, "--list-modes"], stdout=subprocess.PIPE).communicate()[0]
		lines = output.split("\n")
		
		if len(lines) <= 1:
			return -1
		
		lines = lines[1:len(lines)] # slice: always ignore the first line
		
		modes = []
		for line in lines:

			if len(line) > 0:
				modes.append(line)		
		modes.append("640x480")
		modes.reverse()
		
		return modes
	
	def __init__(self):
		self.demo_exe = "./demo"
	
		self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
		self.window.set_title("PPG03: Killotrona")
		self.window.set_border_width(10)
		
		self.window.connect("destroy", self.destroy)
		
		self.v_box = gtk.VBox(False, 0)
		self.window.add(self.v_box)
		
		self.image = gtk.Image()
		self.image.set_from_file("./data/screenshot.png")
		self.v_box.pack_start(self.image, True, True, 0)
		self.image.show()
		
		
		modes = ["1024x768", "800x600", "640x480", "320x240"]
		detected_modes = self.detect_modes()
		if type(detected_modes) is types.ListType:
			modes = detected_modes
		
		self.modes_combo = gtk.combo_box_new_text()
		for m in modes:
			self.modes_combo.append_text(m)
			
		self.modes_combo.set_active(0)
		
		self.v_box.pack_start(self.modes_combo, True, True, 0)
		self.modes_combo.show()
		
		
		self.fullscreen_button = gtk.CheckButton("Fullscreen?")
		self.fullscreen_button.set_active(True)
		self.v_box.pack_start(self.fullscreen_button, True, True, 0)
		self.fullscreen_button.show()
		
		self.aa_box = gtk.HBox(False, 0)
		self.v_box.pack_start(self.aa_box, True, True, 0)
		self.aa_box.show()
		
		self.aa_label = gtk.Label("Antialias samples (0 for no AA)")
		self.aa_box.pack_start(self.aa_label, True, True, 0)
		self.aa_label.show()
		
		self.samples_combo = gtk.combo_box_new_text()
		samples = ['0', '1', '2', '4', '8', '16']
		for s in samples:
			self.samples_combo.append_text(s)
		self.aa_box.pack_start(self.samples_combo, True, True, 0)
		self.samples_combo.set_active(0)
		self.samples_combo.show()
		
		
		self.buttons_box = gtk.HBox(False, 0)
		self.v_box.pack_start(self.buttons_box, True, True, 0)

		self.button_demo = gtk.Button("Demo")
		self.button_demo.connect("clicked", self.demo_callback, None)
		self.buttons_box.pack_start(self.button_demo, True, True, 0)
		self.button_demo.show()

		self.button_die = gtk.Button("Die")
		self.button_die.connect("clicked", self.die_callback, None)
		self.buttons_box.pack_start(self.button_die, True, True, 0)
		self.button_die.show()
		
		self.buttons_box.show()
		
		
		self.v_box.show()

		self.window.show()
		
	
	def main(self):
		gtk.main()
		

if __name__ == "__main__":
	launcher = Launcher()
	launcher.main()
