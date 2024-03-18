#pragma once
#include "BaseBrush.h"
class BrushRect :
    public BaseBrush
{
	XY startPos = XY{ 0,0 };

	void resetState() {
		startPos = XY{ 0,0 };
	}
	std::string getName() override { return "1px Rectangle"; };
	std::string getIconPath() override { return "assets/brush_1pxrect.png"; }
	void clickPress(MainEditor* editor, XY pos) override;
	void clickDrag(MainEditor* editor, XY from, XY to) override {}
	void clickRelease(MainEditor* editor, XY pos) override;
};

