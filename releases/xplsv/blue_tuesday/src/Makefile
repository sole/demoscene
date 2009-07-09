OBJECTS = Algebra.o Camera.o CurvaBezier.o Demo.o Effect.o Events.o FXfade.o FXpanorama.o FXplane.o FXplaneCort.o FXscIntro.o FXscCintas.o FXscCintas2.o FXscCuadricula.o FXscOtra.o FXspiral.o FXtape.o FXTVDistort.o main.o math3D.o Music.o Path.o textures.o

TARGET = demo

linux: $(OBJECTS)
	php process_synch.php
	cp ./bass/libbass.so ../libbass.so
	g++ -O3 -o ../$(TARGET) $(OBJECTS) -L./bass -lbass ./SOIL/libSOIL-linux_x86_32.a -pthread `sdl-config --cflags --libs` -lGL -lGLU -Wl,-R.

mac: $(OBJECTS)
	/bin/sh bundle.sh $(TARGET)
	g++ -O3 -o $(TARGET).app/Contents/MacOS/$(TARGET) $(OBJECTS) ./bass/libbass.dylib ./SOIL/libSOIL-mac_ub.a -pthread `sdl-config --cflags --libs` -framework OpenGL
	install_name_tool -change ./bass/libbass.dylib ./libbass.dylib ./$(TARGET).app/Contents/MacOS/$(TARGET)
	cp ./bass/libbass.dylib $(TARGET).app/Contents/MacOS/
	cp ./mac/icon.icns $(TARGET).app/Contents/Resources/
	rm -R ../$(TARGET).app; mv $(TARGET).app ./..
	
clean:
	rm  $(OBJECTS)
