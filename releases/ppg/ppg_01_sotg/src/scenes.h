#define WIDTH 320
#define HEIGHT 240
#define MAXV 30 // numero maximo de vertices para interpolar...


 

void initScenes(void);
void finishScenes(void);
void ejes(void);
void scene000(void);
void sceneSimbolo(int row);
void sceneCircles(int row);
void sceneLatidos(int row);
void sceneRotante(int row, float tiempo);
void sceneRotante2(int row, float tiempo);
void sceneDiscos(int row, float tiempo);
void sceneDiscos2(int row, float tiempo);
void sceneDiscos3(int row, float tiempo);
void scenePrueba(int row,float tiempo);
void scenePrueba2(int row,float tiempo);
void sceneMeshField(int row,float tiempo);
void sceneSurface(int row,float tiempo);
void sceneSnow(int row, float tiempo, int pat);
void sceneSurfaceBlur (int pat, int row, float tiempo, float *fft);
void sceneKryptBlur (int row, float tiempo);
void scene4segundos (int row);

void setCurrentHeight(int _height);
void setCurrentWidth(int _width);
//void ponOrtopedico(void);
void ponOrtopedico(float xres = 640, float yres = 480);
void quitaOrtopedico(void);

void ponLetra(char letra);
void ponLetraPix(char letra);

void drawCube(bool wired=false, float size=1);

GLuint EmptyTexture();