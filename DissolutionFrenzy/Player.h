#pragma once

#include "Constants.h"
#include "Character.h"
#include "ListaBalas.h"

using namespace System;
using namespace System::Drawing;

class Player : public Character {
protected:
	float standardDX;
	float standardDY;
	float inputDX;
	float inputDY;
	int walkSpeed;
	bool powerMove;
	bool loop;
	float tick;
	int lastDirX;
	// Upgrade Required Variables
	int attack;
	int resistance;
	// Shooting Event
	bool shootTimeout;
	float shootTimeout_Timer;
	float shootTimeout_Timer_Max;
public:
	Player(int x, int y) {
		// Father
		this->x = x;
		this->y = y;
		dx = 0;
		dy = 0;
		width = 20;
		height = 20;
		walkSpeed = 8;
		gravityTaken = 1;
		maxHealth = 10;
		health = maxHealth;
		imgIndex = 0;
		imgWidth = 2;
		imgHeight = 2;
		// Son
		powerMove = false;
		loop = true;
		tick = 0;
		standardDX = 0;
		standardDY = 0;
		inputDX = 0;
		inputDY = 0;
		damageTaken = false;
		damageTaken_Timer = 0;
		damageTaken_Timer_Max = 1.2;
		lastDirX = 1;
		attack = 4;
		resistance = 2;
		shootTimeout = false;
		shootTimeout_Timer = 0;
		shootTimeout_Timer_Max = 0.25;
	}
	~Player() {}

	void timers() {
		if (damageTaken) damageTakenEvent();
		if (shootTimeout) shootTimeoutEvent();
	}

	void shootTimeoutEvent() {
		shootTimeout_Timer += 50.0 / 1000;
		if (shootTimeout_Timer >= shootTimeout_Timer_Max) {
			shootTimeout_Timer = 0;
			shootTimeout = false;
		}
	}

	// Upgrades
	void upgrade_Health() {
		maxHealth += 2;
		health += 2;
	}
	void upgrade_Resistance() {
		resistance += 2;
	}
	void upgrade_Attack() {
		attack += 2;
	}
	int getAttack() {
		return attack;
	}
	int getResistance() {
		return resistance;
	}

	// Store Game Tick for Calculations
	void storeGameTick(int tick) {
		this->tick = tick;
	}
	bool isInGround() {
		return gravityTaken <= 1.06;
	}
	void cancelInputVelocity() {
		inputDX = 0;
		inputDY = 0;
	}
	void jump(bool jump) {
		if (jump && isInGround()) {
			standardDY += -13;
		}
	}
	void capVelocity() {
		if (dx >= 20)
			dx = 19.9;
		if (dx <= -20)
			dx = -19.9;
		if (dy >= 20)
			dy = 19.9;
		if (dy <= -20)
			dy = -19.9;
	}
	float getGravityTaken() {
		return gravityTaken;
	}
	// Move
	void draw(BufferedGraphics^ buffer, Bitmap^ bmp, bool modoJefe, int blockX, int blockY) {
		indexPass();
		/*
			if (damageTaken == false)
				buffer->Graphics->FillRectangle(Brushes::Red, getMapX(modoJefe, blockX), getMapY(modoJefe, blockY), width, height);
			if (damageTaken == true)
				buffer->Graphics->FillRectangle(Brushes::White, getMapX(modoJefe, blockX), getMapY(modoJefe, blockY), width, height);
		*/
		Rectangle area = Rectangle(bmp->Width / imgWidth * (imgIndex % imgWidth), bmp->Height / imgHeight * int(imgIndex / imgWidth), bmp->Width / imgWidth, bmp->Height / imgHeight);
		Rectangle limit = Rectangle(getMapX(modoJefe, blockX), getMapY(modoJefe, blockY), width, height);
		buffer->Graphics->DrawImage(bmp, limit, area, GraphicsUnit::Pixel);
	}
	void indexPass() {
		//imgIndex++;
		if (damageTaken) {
			imgIndex += 2;
		}

		if (imgIndex >= imgWidth * imgHeight) {
			imgIndex = 0;
		}
	}

	// Reset Velocity
	void combineVelocity() {
		this->dx += standardDX + inputDX;
		this->dy += standardDY + inputDY;
	}
	// WASD Direction
	void movementInput(int dirX, int dirY) {
		if (!powerMove) {
			this->inputDX += dirX * walkSpeed;
			this->inputDY += dirY * walkSpeed;
			if (dirX != 0) lastDirX = dirX;

			switch (dirX) {
			case -1:
				imgIndex = 1;
				break;
			case 1:
				imgIndex = 0;
				break;
			case 0:
				if (damageTaken) {
					imgIndex -= 2;
				}
				break;
			}
		}
	}
	// Gravity
	void gravity() {
		standardDY += 9.81 * (tick / 1000.0) * gravityTaken;
		gravityTaken += tick / 1000.0;
	}

	void cancelStandardVelocity() {
		standardDX = 0;
		standardDY = 0;
	}
	// Shoot
	void shoot(bool shoot, int inputX, int dirY, ListaBalas* balasActivas) {
		if (shoot && !shootTimeout) {
			if (dirY != 0)
				balasActivas->addItem(x, y, 15 * inputX, dirY * 15, 10, 5, attack, this, 0);
			else
				balasActivas->addItem(x, y, 15 * lastDirX, dirY * 15, 10, 5, attack, this, 0);
			shootTimeout = true;
		}
	}
};