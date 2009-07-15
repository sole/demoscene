OBJECTS = main.o luisita.o

TARGET = demo

linux: $(OBJECTS)
	cp ./bass/libbass.so ../libbass.so
	g++ -O3 -o ../$(TARGET) $(OBJECTS) -L./bass -lbass ./SOIL/libSOIL-linux_x86_32.a ./lua/liblua-linux_x86_32b.a -pthread `sdl-config --cflags --libs` -lGL -lGLU -Wl,-R.

mac: $(OBJECTS)
	/bin/sh bundle.sh $(TARGET)
	g++ -O3 -o $(TARGET).app/Contents/MacOS/$(TARGET) $(OBJECTS) ./bass/libbass.dylib ./SOIL/libSOIL-mac_ub.a ./lua/liblua-mac_ub.a -pthread `sdl-config --cflags --libs` -framework OpenGL
	install_name_tool -change ./bass/libbass.dylib ./libbass.dylib ./$(TARGET).app/Contents/MacOS/$(TARGET)
	cp ./bass/libbass.dylib $(TARGET).app/Contents/MacOS/
	cp ./mac/icon.icns $(TARGET).app/Contents/Resources/
	rm -R ../$(TARGET).app; mv $(TARGET).app ./..
	
clean:
	rm  $(OBJECTS)
