OBJECTS = main.o Camera.o Demo.o Effect.o FXespaciok.o FXfade.o FXmanga.o FXmuros.o FXparon1.o FXradialblur.o FXrueda.o FXsinusplasma.o FXtext.o math3D.o Mesh.o Music.o Particles.o Path.o textures.o

TARGET = demo

linux: $(OBJECTS)
	g++ -O3 -o ../$(TARGET) $(OBJECTS) -L.. -lbass ./SOIL/libSOIL-linux_x86_32.a -pthread `sdl-config --cflags --libs` -lGL -lGLU -Wl,-R.

mac: $(OBJECTS)
	/bin/sh bundle.sh $(TARGET)
	g++ -O3 -o $(TARGET).app/Contents/MacOS/$(TARGET) $(OBJECTS) ./bass/libbass.dylib ./SOIL/libSOIL-mac_ub.a -pthread `sdl-config --cflags --libs` -framework OpenGL
	install_name_tool -change ./bass/libbass.dylib ./libbass.dylib ./$(TARGET).app/Contents/MacOS/$(TARGET)
	cp ./bass/libbass.dylib $(TARGET).app/Contents/MacOS/
	cp ./mac/icon.icns $(TARGET).app/Contents/Resources/
	rm -R ../$(TARGET).app; mv $(TARGET).app ./..
	
clean:
	rm  $(OBJECTS)
