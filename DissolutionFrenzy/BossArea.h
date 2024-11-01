#pragma once

#include <math.h>

using namespace std;
using namespace System;
using namespace Drawing;

class BossArea {
protected:
	int blockX;
	int blockY;
	int width;
	int height;
public:
	BossArea(int blockX, int blockY, int width, int height) {
		this->blockX = blockX;
		this->blockY = blockY;
		this->width = 25;
		this->height = 14;
	}
	~BossArea() {}
	int getBlockX() {
		return blockX;
	}
	int getBlockY() {
		return blockY;
	}
	bool possiblyCollides(Character* char2) {
		return
			(
				-this->blockX * 20 + char2->getX() + char2->getDx() > 20
				&&
				-this->blockX * 20 + char2->getX() + char2->getDx() < (this->width + 1) * 20
				&&
				-this->blockY * 20 + char2->getY() + char2->getDy() > 0
				&&
				-this->blockY * 20 + char2->getY() + char2->getDy() < (this->height + 1) * 20
				);
	}
	int test(Character* char2) {
		return -this->blockY * 20 + char2->getY() + char2->getDy();
	}
};