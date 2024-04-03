#pragma once
#include "globals.h"
#include "EventCallbackListener.h"
#include "drawable.h"
#include "DrawableManager.h"
#include "BaseScreen.h"
#include "UITextField.h"
#include "UIButton.h"
#include "maineditor.h"
#include "UILabel.h"
#include "TabbedView.h"
#include "BaseTemplate.h"
#include "TemplateRPG2KCharset.h"

class StartScreen : public BaseScreen, public EventCallbackListener
{
public:
	DrawableManager wxsManager;

	TabbedView* newImageTabs;

	int newImgW = 0, newImgH = 0;

	UITextField* tab0TextFieldW;
	UITextField* tab0TextFieldH;

	UITextField* tab1TextFieldCW;
	UITextField* tab1TextFieldCH;
	UITextField* tab1TextFieldCWX;
	UITextField* tab1TextFieldCHX;

	BaseTemplate* tab2templates[1] = {
		new TemplateRPG2KCharset()
	};

	StartScreen() {
		newImageTabs = new TabbedView({ {"Pixel dimensions"}, {"Sprites/Tiles"}, {"Templates"} }, 160);
		newImageTabs->position = XY{ 10, 110 };
		wxsManager.addDrawable(newImageTabs);


		//tab 0
		tab0TextFieldW = new UITextField();
		tab0TextFieldW->setCallbackListener(2, this);
		tab0TextFieldW->position = xySubtract(XY{80,120}, newImageTabs->position);
		tab0TextFieldW->wxWidth = 200;
		tab0TextFieldW->numeric = true;
		newImageTabs->tabs[0].wxs.addDrawable(tab0TextFieldW);

		tab0TextFieldH = new UITextField();
		tab0TextFieldH->setCallbackListener(3, this);
		tab0TextFieldH->position = xySubtract(XY{ 80,155 }, newImageTabs->position);
		tab0TextFieldH->wxWidth = 200;
		tab0TextFieldH->numeric = true;
		newImageTabs->tabs[0].wxs.addDrawable(tab0TextFieldH);

		UILabel* wLabel = new UILabel();
		wLabel->text = "Width";
		wLabel->position = xySubtract(XY{ 10,120 }, newImageTabs->position);
		newImageTabs->tabs[0].wxs.addDrawable(wLabel);

		UILabel* hLabel = new UILabel();
		hLabel->text = "Height";
		hLabel->position = xySubtract(XY{ 10,155 }, newImageTabs->position);
		newImageTabs->tabs[0].wxs.addDrawable(hLabel);

		//tab 1
		tab1TextFieldCW = new UITextField();
		tab1TextFieldCW->position = xySubtract(XY{ 110,120}, newImageTabs->position);
		tab1TextFieldCW->wxWidth = 160;
		tab1TextFieldCW->numeric = true;
		newImageTabs->tabs[1].wxs.addDrawable(tab1TextFieldCW);

		tab1TextFieldCH = new UITextField();
		tab1TextFieldCH->position = xySubtract(XY{ 110,155 }, newImageTabs->position);
		tab1TextFieldCH->wxWidth = 160;
		tab1TextFieldCH->numeric = true;
		newImageTabs->tabs[1].wxs.addDrawable(tab1TextFieldCH);

		tab1TextFieldCWX = new UITextField();
		tab1TextFieldCWX->position = xySubtract(XY{ 300,120}, newImageTabs->position);
		tab1TextFieldCWX->wxWidth = 40;
		tab1TextFieldCWX->numeric = true;
		tab1TextFieldCWX->text = "1";
		newImageTabs->tabs[1].wxs.addDrawable(tab1TextFieldCWX);

		tab1TextFieldCHX = new UITextField();
		tab1TextFieldCHX->position = xySubtract(XY{ 300,155 }, newImageTabs->position);
		tab1TextFieldCHX->wxWidth = 40;
		tab1TextFieldCHX->numeric = true;
		tab1TextFieldCHX->text = "1";
		newImageTabs->tabs[1].wxs.addDrawable(tab1TextFieldCHX);

		UILabel* w2Label = new UILabel();
		w2Label->text = "Cell width";
		w2Label->position = xySubtract(XY{ 10,120 }, newImageTabs->position);
		newImageTabs->tabs[1].wxs.addDrawable(w2Label);

		UILabel* h2Label = new UILabel();
		h2Label->text = "Cell height";
		h2Label->position = xySubtract(XY{ 10,155 }, newImageTabs->position);
		newImageTabs->tabs[1].wxs.addDrawable(h2Label);

		UILabel* w2Label2 = new UILabel();
		w2Label2->text = "x";
		w2Label2->position = xySubtract(XY{ 280,120 }, newImageTabs->position);
		newImageTabs->tabs[1].wxs.addDrawable(w2Label2);

		UILabel* h2Label2 = new UILabel();
		h2Label2->text = "x";
		h2Label2->position = xySubtract(XY{ 280,155 }, newImageTabs->position);
		newImageTabs->tabs[1].wxs.addDrawable(h2Label2);

		for (int x = 0; x < 1; x++) {
			UIButton* buttonTemplate = new UIButton();
			buttonTemplate->position = XY{ 40, 5 + x * 30 };
			buttonTemplate->text = tab2templates[x]->getName();
			buttonTemplate->setCallbackListener(10 + x, this);
			buttonTemplate->wxWidth = 400;
			newImageTabs->tabs[2].wxs.addDrawable(buttonTemplate);
		}

		for (int x = 0; x < 2; x++) {
			UIButton* buttonNewImage = new UIButton();
			buttonNewImage->setCallbackListener(4, this);
			buttonNewImage->position = XY{ 30,150 };
			buttonNewImage->wxWidth = 100;
			buttonNewImage->text = "Create...";
			newImageTabs->tabs[x].wxs.addDrawable(buttonNewImage);
		}
	}
	~StartScreen() {
		wxsManager.freeAllDrawables();
	}

	void render() override;
	void tick() override;
	void takeInput(SDL_Event evt) override;

	void eventTextInput(int evt_id, std::string data) override {
		switch (evt_id) {
			case 2:
				newImgW = std::stoi(data);
				break;
			case 3:
				newImgH = std::stoi(data);
				break;
		}
	}
	void eventButtonPressed(int evt_id) override {
		if (evt_id == 4) {
			switch (newImageTabs->openTab) {
				case 0:
					if (!tab0TextFieldW->text.empty() && !tab0TextFieldH->text.empty()) {
						int newImgW = std::stoi(tab0TextFieldW->text);
						int newImgH = std::stoi(tab0TextFieldH->text);
						g_addScreen(new MainEditor(XY{ newImgW, newImgH }));
					}
					break;
				case 1:
					if (!tab1TextFieldCH->text.empty() && !tab1TextFieldCW->text.empty()
						&& !tab1TextFieldCHX->text.empty() && !tab1TextFieldCWX->text.empty()) {
						XY cellSize = XY{ std::stoi(tab1TextFieldCW->text) , std::stoi(tab1TextFieldCH->text) };
						int newImgW = cellSize.x * std::stoi(tab1TextFieldCWX->text);
						int newImgH = cellSize.y * std::stoi(tab1TextFieldCHX->text);
						MainEditor* newMainEditor = new MainEditor(XY{ newImgW, newImgH });
						newMainEditor->tileDimensions = cellSize;
						g_addScreen(newMainEditor);
					}
					break;
			}
		}
		else if (evt_id >= 10) {
			MainEditor* newMainEditor = new MainEditor(tab2templates[evt_id-10]->generate());
			newMainEditor->tileDimensions = tab2templates[evt_id - 10]->tileSize();
			g_addScreen(newMainEditor);
		}
	}
};

