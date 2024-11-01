#pragma once

#include <math.h>
#include "Character.h"

using namespace System;
using namespace Drawing;

class Projectile : public Character {
protected:
	// Game Design
	int damage;
	Character* sender;
	int bala_Identity;
public:
	Projectile(float x, float y, float dx, float dy, int width, int height, int damage, Character* sender, int bala_Identity) {
		// Father
		this->x = x;
		this->y = y;
		this->dx = dx;
		this->dy = dy;
		this->width = width;
		this->height = height;
		this->imgIndex = 0;
		this->imgHeight = 1;
		this->imgWidth = 1;
		this->gravityTaken = 0;
		// Son
		this->damage = damage;
		this->sender = sender;
		this->bala_Identity = bala_Identity;
	}
	~Projectile() {}
	int getBala_Identity() {
		return bala_Identity;
	}
	int getDamage() {
		return damage;
	}
	Character* getSender() {
		return sender;
	}
	void move() {
		x += dx;
		y += dy;
	}
	void draw(BufferedGraphics^ buffer, Character* player, Bitmap^ bmp) {
		Rectangle area = Rectangle(bmp->Width / imgWidth * (imgIndex % imgWidth), bmp->Height / imgHeight * int(imgIndex / imgWidth), bmp->Width / imgWidth, bmp->Height / imgHeight);
		Rectangle limit = Rectangle(getMapAIX(player, 0, 0), getMapAIY(player), width, height);
		buffer->Graphics->DrawImage(bmp, limit, area, GraphicsUnit::Pixel);
	}
	void BalaDraw(BufferedGraphics^ buffer, Character* player, Bitmap^ bmp, bool modoJefe, int blockX) {
		Rectangle area = Rectangle(bmp->Width / imgWidth * (imgIndex % imgWidth), bmp->Height / imgHeight * int(imgIndex / imgWidth), bmp->Width / imgWidth, bmp->Height / imgHeight);
		Rectangle limit = Rectangle(getMapAIX(player, modoJefe, blockX), getMapAIY(player), width, height);
		buffer->Graphics->DrawImage(bmp, limit, area, GraphicsUnit::Pixel);
	}

	bool mapIntersects() {
		if ((map[int((y + dy - 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + dy - 0.01) / 20)][int((x + dx + width - 0.01) / 20)] == 'X' || map[int((y + height + 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + height + 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X')) {
			return true;
		}
		return false;
	}
};