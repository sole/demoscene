OBJECTS = Algebra.o Camera.o Demo.o Effect.o Logger.o main.o MathExpression.o Music.o Render.o RenderBlending.o Resource.o ResourceFactory.o ResourceBoxBlur.o ResourceColorPlane.o ResourceDistortPolar.o ResourceDistortRipple.o ResourceDistortSine.o ResourceEmpty.o ResourceFilterDithering.o ResourceFilterFlipColors.o ResourceFilterHighPass.o ResourceFilterLowPass.o ResourceFilterMidTone.o ResourceFilterMonoTone.o ResourceGeneric.o ResourceImage.o ResourceImageSequence.o ResourceMotionBlur.o  ResourceObjectTerrain.o ResourceParticleSystemSnow.o ResourcePsychoCircles.o ResourcePsychoFire.o ResourcePsychoPlasma.o ResourcePsychoWhiteNoise.o ResourceRadialBlur.o ResourceRadialBlurImproved.o  ResourceSceneTGForest.o ResourceSceneTubeBeginning.o ResourceSceneTubeGreetings.o ResourceSotgPoints.o Texture.o tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o Xml.o

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
