#pragma once
#include "globals.h"
#include "drawable.h"
#include "mathops.h"

class UITextField : public Drawable
{
public:
	std::string text = "";
	bool numeric = false;
	int wxWidth = 250, wxHeight = 30;
	SDL_Color bgColor = { 0,0,0, 0xff };


	bool isMouseIn(XY thisPositionOnScreen, XY mousePos) override {
		return pointInBox(mousePos, SDL_Rect{ thisPositionOnScreen.x, thisPositionOnScreen.y, wxWidth, wxHeight });
	}
	void render(XY pos) override;
	void handleInput(SDL_Event evt, XY gPosOffset) override;
};

