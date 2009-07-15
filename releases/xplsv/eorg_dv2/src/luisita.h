#ifndef LUISITA_H
#define LUISITA_H

#include "lua/lua.hpp"

extern int		luisita_init();
extern int		luisita_end();
extern int		luisita_runScript(const char *scriptFile);
extern int		luisita_hasFinished();
extern void		luisita_render();

void			luisita_reportErrors(lua_State *L, int status);

// Graphic functions
// ------------------------------------
// miscellaneous
void			luisita_gfxLoadingProgressBar(float value);

// images
int				luisita_gfxLoadImage(const char filename);
void			luisita_gfxShowImage(int textureId, float x, float y, float width, float height);

// cameras, views and co
void			luisita_gfxSetOrtho(float xres = -1.0, float yres = -1.0);
void			luisita_gfxRestoreProjection();


// Functions which are available to lua
// -------------------------------------

static int luisita_luaLoadMusicModule(lua_State *L);
static int luisita_luaPlayMusicModule(lua_State *L);
static int luisita_luaIsMusicModuleFinished(lua_State *L);
static int luisita_luaGetMusicModuleTime(lua_State *L);
static int luisita_luaGetMusicModuleRow(lua_State *L);
static int luisita_luaGetMusicModulePattern(lua_State *L);
static int luisita_luaGetMusicModuleOrder(lua_State *L);

static int luisita_luaLoadMusicStream(lua_State *L);
static int luisita_luaPlayMusicStream(lua_State *L);
static int luisita_luaIsMusicStreamFinished(lua_State *L);
static int luisita_luaGetMusicStreamTime(lua_State *L);

static int luisita_luaGetSoundFFT(lua_State *L);

static int luisita_luaSwapBuffers(lua_State *L);
static int luisita_luaLoadingProgressBar(lua_State *L);

static int luisita_luaTrace(lua_State *L);
static int luisita_luaAntialias(lua_State *L);
static int luisita_luaFullScreen(lua_State *L);
static int luisita_luaSize(lua_State *L);
static int luisita_luaWindowTitle(lua_State *L);
static int luisita_luaSetupIsDone(lua_State *L);
static int luisita_luaQuit(lua_State *L);

// 2D primitives
static int luisita_luaLine(lua_State *L);
static int luisita_luaTriangle(lua_State *L);
static int luisita_luaStipple(lua_State *L);
static int luisita_luaNoStipple(lua_State *L);

// Color
static int luisita_luaBackground(lua_State *L);
static int luisita_luaFill(lua_State *L);
static int luisita_luaNoFill(lua_State *L);
static int luisita_luaStroke(lua_State *L);
static int luisita_luaNoStroke(lua_State *L);
static int luisita_luaColor(lua_State *L);
static int luisita_luaColorMode(lua_State *L);

// Attributes
static int luisita_luaStrokeWeight(lua_State *L);
static int luisita_luaPointSize(lua_State *L);

// Vertex
static int luisita_luaBeginShape(lua_State *L);
static int luisita_luaEndShape(lua_State *L);
static int luisita_luaVertex(lua_State *L);
static int luisita_luaNormal(lua_State *L);

// Blendings
static int luisita_luaBlending(lua_State *L);
static int luisita_luaNoBlending(lua_State *L);

// Images
static int luisita_luaLoadImage(lua_State *L);
static int luisita_luaImage(lua_State *L);
static int luisita_luaUseTexture(lua_State *L);
static int luisita_luaNoTexture(lua_State *L);

// Cameras
static int luisita_luaOrtho(lua_State *L);
static int luisita_luaRestoreProjection(lua_State *L);
static int luisita_luaCamera(lua_State *L);
static int luisita_luaPerspective(lua_State *L);
static int luisita_luaDepthTest(lua_State *L);
static int luisita_luaNoDepthTest(lua_State *L);

// Lights
static int luisita_luaNoLights(lua_State *L);
static int luisita_luaLightEnabled(lua_State *L);
static int luisita_luaLightPosition(lua_State *L);
static int luisita_luaLightAmbient(lua_State *L);
static int luisita_luaLightDiffuse(lua_State *L);
static int luisita_luaLightSpotDirection(lua_State *L);

// Fog
static int luisita_luaFogMode(lua_State *L);
static int luisita_luaFogDensity(lua_State *L);
static int luisita_luaFogStartEnd(lua_State *L);
static int luisita_luaFogColor(lua_State *L);


#endif
