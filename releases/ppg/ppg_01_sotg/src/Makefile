OBJECTS = main.o scenes.o math3D.o Music.o textures.o Particles.o Mesh.o Camera.o Demo.o Path.o

linux: $(OBJECTS)

	g++ -O3 -o ../ppg01_sotg_linux $(OBJECTS) -L.. -lbass ./SOIL/libSOIL-linux_x86.a -pthread `sdl-config --cflags --libs` -lGL -lGLU -Wl,-R.

# TODO: NOT DONE WITH BASS YET	
#mac: $(OBJECTS)
#	g++ -O3 -o ../ppg01_sotg_mac $(OBJECTS) ../libfmodex.dylib ./SOIL/libSOIL-mac_ub.a -pthread `sdl-config --cflags --libs` -framework OpenGL
#	install_name_tool -change ../libfmodex.dylib ./libfmodex.dylib ../ppg01_sotg_mac

clean:
	rm  $(OBJECTS)
