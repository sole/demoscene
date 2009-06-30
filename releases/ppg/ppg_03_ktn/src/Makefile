OBJECTS = main.o Camera.o Demo.o Effect.o FXespaciok.o FXfade.o FXmanga.o FXmuros.o FXparon1.o FXradialblur.o FXrueda.o FXsinusplasma.o FXtext.o math3D.o Mesh.o Music.o Particles.o Path.o textures.o

linux: $(OBJECTS)

	g++ -O3 -o ../ppg03_ktn_linux $(OBJECTS) -L.. -lbass ./SOIL/libSOIL-linux_x86_32.a -pthread `sdl-config --cflags --libs` -lGL -lGLU -Wl,-R.

# TODO: NOT DONE WITH BASS YET	
#mac: $(OBJECTS)
#	g++ -O3 -o ../ppg01_sotg_mac $(OBJECTS) ../libfmodex.dylib ./SOIL/libSOIL-mac_ub.a -pthread `sdl-config --cflags --libs` -framework OpenGL
#	install_name_tool -change ../libfmodex.dylib ./libfmodex.dylib ../ppg01_sotg_mac

clean:
	rm  $(OBJECTS)
