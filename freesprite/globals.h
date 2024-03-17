#pragma once

//#include <math.h>

#include <string>
#include <format>
#include <map>
#include <new>
#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#define FONT_PATH "appfont-MPLUSRounded1c-Medium.ttf"
#define FONT_PATH_JP "appfontjp-NotoSansJP-VariableFont_wght.ttf"

class EventCallbackListener;
class TextRenderer;
class MainEditor;
class EditorColorPicker;
class BaseScreen;

extern int g_windowW, g_windowH;
extern SDL_Window* g_wd;
extern SDL_Renderer* g_rd;
extern TextRenderer* g_fnt;
extern int g_mouseX, g_mouseY;

void g_addScreen(BaseScreen* a);

struct XY {
	int x, y;
};

#include "platform.h"