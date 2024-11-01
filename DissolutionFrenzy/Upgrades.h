#pragma once

#include "Character.h"

using namespace std;
using namespace System;
using namespace Drawing;

enum UpgradeType {
	HealthBoost = 0, AttackBoost = 1, ResistanceBoost = 2
};

class Upgrade : public Character {
protected:
	UpgradeType type;
public:
	Upgrade(int x, int y, UpgradeType type) {
		// Father
		this->x = x;
		this->y = y;
		dx = 0;
		dy = 0;
		width = 25;
		height = 25;
		imgIndex = 0;
		imgWidth = 1;
		imgHeight = 1;
		// Son
		this->type = type;
	}
	~Upgrade() {}

	UpgradeType getType() {
		return type;
	}

	void draw(BufferedGraphics^ buffer, Character* player, Bitmap^ bmp) {
		Rectangle area = Rectangle(bmp->Width / imgWidth * (imgIndex % imgWidth), bmp->Height / imgHeight * int(imgIndex / imgWidth), bmp->Width / imgWidth, bmp->Height / imgHeight);
		Rectangle limit = Rectangle(getMapAIX(player, 0, 0), getMapAIY(player), width, height);
		buffer->Graphics->DrawImage(bmp, limit, area, GraphicsUnit::Pixel);
	}
};