#ifndef __DEMO__
#define __DEMO__

class Demo {
public:
	Demo(int _height, int _width);
	void setSize(int _height, int _width);
	int getWidth(void);
	int getHeight(void);
	bool isFullScreen(void);
	void setFullScreen(bool _fullscr);
	void setTitle(char *_title);
	char *getTitle(void);
	void ponOrtopedico(float xres = -1, float yres = -1);
	void quitaOrtopedico(void);
	
	void ejes(void);
	
private:
	int height;
	int width;
	bool fullscreen;
	char title[255];
};

#endif
