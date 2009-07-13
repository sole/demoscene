OBJECTS = Algebra.o Camera.o Demo.o Effect.o EffectClearBuffer.o EffectFactory.o EffectFlash.o EffectMotionBlur.o EffectRender2Texture.o EffectTest.o EffectWeirdBlur.o EventList.o FXplaneCort.o GeomObject.o LightObject.o main.o math3D.o Music.o Particles.o Path.o Scene.o Scene01.o Scene3D.o SceneCredits.o SceneFactory.o SceneGreets.o ScenePlano.o SceneScroller.o SceneTest.o ScriptLoader.o textures.o tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o

TARGET = demo

linux: $(OBJECTS)
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
