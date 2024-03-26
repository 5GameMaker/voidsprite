#pragma once
#include "globals.h"
#include "BaseScreen.h"
#include "DrawableManager.h"
#include "EditorColorPicker.h"
#include "BaseBrush.h"
#include "Brush1x1.h"
#include "Brush3pxCircle.h"
#include "Brush1pxLine.h"
#include "BrushRect.h"
#include "BrushRectFill.h"
#include "ToolColorPicker.h"
#include "Layer.h"

class MainEditor : public BaseScreen, public EventCallbackListener
{
protected:
	Layer* getCurrentLayer() {
		return layers[selLayer];
	}
public:
	std::vector<Layer*> layers;
	int selLayer = 0;
	
	Layer* flattenImage();

	int maxUndoHistory = 100;
	std::vector<Layer*> undoStack, redoStack;

	int texW = -1, texH = -1;
	XY tileDimensions = XY{ 0,0 };
	uint8_t tileGridAlpha = 0x40;
	XY canvasCenterPoint = XY{0,0};
	XY mousePixelTargetPoint;
	int scale = 1;
	XY mouseHoldPosition;
	BaseBrush* currentBrush = new Brush1x1();
	bool leftMouseHold = false;
	bool middleMouseHold = false;

	bool eraserMode = false;
	uint32_t pickedColor = 0xFFFFFF;

	GlobalNavBar* navbar;
	DrawableManager wxsManager;
	EditorColorPicker* colorPicker;
	EditorBrushPicker* brushPicker;

	SDL_Color backgroundColor = SDL_Color{0,0,0,255};

	MainEditor(XY dimensions);
	MainEditor(SDL_Surface* srf);
	MainEditor(Layer* srf);
	MainEditor(std::vector<Layer*> layers);
	~MainEditor();

	void render() override;
	void tick() override;
	void takeInput(SDL_Event evt) override;

	void eventFileSavedW(int evt_id, std::wstring name) override;
	
	void DrawBackground();
	void DrawForeground();
	void initLayers();
	void SetUpWidgets();
	void RecalcMousePixelTargetPoint(int x, int y);
	void FillTexture();
	void SetPixel(XY position, uint32_t color);
	void DrawLine(XY from, XY to, uint32_t color);
	void trySaveImage();
	void recenterCanvas();

	void commitStateToCurrentLayer();
	void undo();
	void redo();

	void layer_flipHorizontally();
	void layer_swapLayerRGBtoBGR();
	uint32_t layer_getPixelAt(XY pos);
};

