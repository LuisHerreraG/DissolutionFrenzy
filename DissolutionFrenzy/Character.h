#pragma once

#include <math.h>
#include "Constants.h"
#include <vector>

using namespace System;
using namespace Drawing;

class Character {
protected:
	float x;
	float y;
	float dx;
	float dy;
	int width;
	int height;
	int imgIndex;
	int imgWidth;
	int imgHeight;
	float gravityTaken;
	int health;
	int maxHealth;
	// damage Taken Event
	bool damageTaken;
	float damageTaken_Timer;
	float damageTaken_Timer_Max;
public:
	Character() {}
	~Character() {}

	// Timers
	virtual void timers() {}
	// Damage Taken
	void damageTakenEvent() {
		damageTaken_Timer += 50.0 / 1000;
		if (damageTaken_Timer >= damageTaken_Timer_Max) {
			damageTaken_Timer = 0;
			damageTaken = false;
		}
	}

	// Damage Taken
	void damaged(int healthLoss) {
		if (damageTaken == false) {
			health -= healthLoss;
			damageTaken = true;
		}
	}

	float getX() {
		return x;
	}
	float getY() {
		return y;
	}
	float getDx() {
		return dx;
	}
	float getDy() {
		return dy;
	}
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}
	int getHealth() {
		return health;
	}
	void setHealth(int health) {
		this->health = health;
	}
	int getMaxHealth() {
		return maxHealth;
	}
	void cancelVelocity() {
		this->dx = 0;
		this->dy = 0;
	}
	void borderCollides() {
		if (x + dx < 0) {
			dx = 0;
		}
		if (y + dy < 0) {
			dy = 0;
		}
		if (x + dx + width > sizeX * 20) {
			dx = 0;
		}
		if (y + dy + height > (sizeY - 1) * 20) {
			dy = 0;
		}
	}
	void mapCollides() {
		bool haCambiado = false;
		// X-Collision
		if (map[int((y - 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + height + 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y - 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X' || map[int((y + height + 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X') {
			haCambiado = true;
			if (map[int((y - 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + height + 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X') {
				dx = ((int((x + dx + 0.01) / 20) * 20 - x) + 20);
			}
			else {
				dx = ((int((x + width + dx + 0.01) / 20) * 20 - x - width) - 1 + 0.01);
			}
		}
		// Y Collision
		if (map[int((y + dy - 0.01) / 20)][int((x + 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + 0.01) / 20)] == 'X' || map[int((y + dy - 0.01) / 20)][int((x + width - 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + width - 0.01) / 20)] == 'X') {
			haCambiado = true;
			if (map[int((y + height + dy + 0.01) / 20)][int((x + 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + width - 0.01) / 20)] == 'X') {
				dy = ((int((y + height + dy + 0.01) / 20) * 20 - y - height) - 1 + 0.01);
				gravityTaken = 1;
				cancelStandardVelocity();
			}
			else {
				dy = (((int((y + dy + 0.01) / 20) * 20 + 20) - y) + 1 - 0.01);
				cancelStandardVelocity();
			}
		}
		// Diagonal Collision
		if (!haCambiado && (map[int((y + dy - 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + dy - 0.01) / 20)][int((x + dx + width - 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X')) {
			dx = 0;
		}
	}
	bool possiblyCollides(Character* char2) {
		Rectangle rect1 = Rectangle(x, y, width, height);
		Rectangle rect2 = Rectangle(char2->getX() + char2->getDx(), char2->getY() + char2->getDy(), char2->getWidth(), char2->getHeight());

		return rect1.IntersectsWith(rect2);


		return
			(
				fabs(this->x + this->dx - char2->getX() - char2->getDx()) < this->width ||
				fabs(this->x + this->dx - char2->getX() - char2->getDx()) < char2->getWidth()
				)
			&&
			(
				fabs(this->y + this->dy - char2->getY() - char2->getDy()) < this->height ||
				fabs(this->y + this->dy - char2->getY() - char2->getDy()) < char2->getHeight()
				);
	}
	bool possiblyCollides(Character* obj1, RectangleF* obj2) {
		if ((fabs(obj1->x + obj1->dx - obj2->X) < obj1->width || fabs(obj1->x + obj1->dx - obj2->X) < obj2->Width) && (fabs(obj1->y + obj1->dy - obj2->Y) < obj1->height || fabs(obj1->y + obj1->dy - obj2->Y) < obj2->Height)) {
			delete obj2;
			return true;
		}
		delete obj2;
		return true;
	}
	// Add Velocity to Pos
	void useVelocity() {
		x += dx;
		y += dy;
	}
	int getMapX(bool modoJefe, int blockX) {
		if (!modoJefe) {
			if (int(x / 20) > 6) { // Move to the left
				if (int(x / 20) > sizeX - 20) { // Stop moving
					return 6 * 20 + (int(x) - ((sizeX - 20) * 20));
				}

				return 7 * 20;
			}

			else {
				return x;
			}
		}
		else {
			return x - blockX * 20;
		}
	}
	int getMapY(bool modoJefe, int blockY) {
		/*
		if (int(y / 20) > 12) { // Move to the right
			if (int(y / 20) > sizeY - 2) { // Stop moving
				return 13 * 20 + (int(y) - ((sizeY - 20) * 20));
			}

			return 13 * 20;
		}

		else {
			return y;
		}
		*/
		if (!modoJefe) {
			if (int(int(y - 0.01) / (15 * 20)) == 0) return y;
			if (int(y - 0.01) % (14 * 20) >= 1 * 20) return int(y - 0.01) % (14 * 20);
			return int((y - 0.01) / 20) + y;
		}
		else {
			return y - blockY * 20;
		}
	}
	int getMapAIX(Character* player, bool modoJefe, int bossAreaBlockX) {
		if (!modoJefe) {
			if (int(player->getX() / 20) > 6) { // Move to the left
				if (int(player->getX() / 20) > sizeX - 20) { // Stop moving
					return 6 * 20 + (int(player->getX()) - ((sizeX - 20) * 20)) - (player->getX() - x);
				}

				return 7 * 20 - (player->getX() - x);
			}

			return x;
		}
		return x - bossAreaBlockX * 20;
	}
	int getMapAIY(Character* player) {
		/*
		if (int(player->getY() / 20) > 12) { // Move to the right
			if (int(player->getY() / 20) > sizeY - 2) { // Stop moving
				return 13 * 20 + (int(player->getY()) - ((sizeY - 20) * 20)) - (player->getY() - y);
			}

			return 13 * 20 - (player->getY() - y);
		}

		else {
			return y;
		}
		*/
		if ((int((int(player->getY() / 20) - 0.01) / 14) * 14 * 20 == (int((int(y / 20) - 0.01) / 14) * 14 * 20)))
			return (int(y - 0.01) % (14 * 20));
		return 15 * 20;
	}
	bool cameraIntersect(Character* player, bool modoJefe, int bossAreaBlockX) {
		if (getMapAIX(player, modoJefe, bossAreaBlockX) + width < 0)
			return false;
		if (getMapAIX(player, modoJefe, bossAreaBlockX) > 26 * 20)
			return false;
		if (getMapAIY(player) < 0)
			return false;
		if (getMapAIY(player) > 13 * 20)
			return false;
		return true;
	}

	virtual void draw(BufferedGraphics^ buffer, Character* player, Bitmap^ bmp) {}
	virtual void move() {}
	virtual void cancelStandardVelocity() {}
	
};

class AI : public Character {  //Delete if useless
protected:
	int AI_Identity;
	int direccion;
	int damage;
	bool enemy;
	bool shoot;
	int UPC_IdentityShoot;
public:
	int getAI_Identity() {
		return AI_Identity;
	}
	int getUPC_IdentityShoot() {
		return UPC_IdentityShoot;
	}
	int getDamage() {
		return damage;
	}
	bool getEnemy() {
		return enemy;
	}
	bool getShoot() {
		return shoot;
	}
	int getDireccion() {
		return direccion;
	}
	void setShoot(bool shoot) {
		this->shoot = shoot;
	}

	int getImgIndex() {
		return imgIndex;
	}

	void AIDamaged(int healthLoss) {
		health += -healthLoss;
	}

	bool isPlayerForward(Character* char2) {
		if (direccion == 1) {
			if (
				char2->getX() > x + width
				&&
				(
				fabs(this->y + this->dy - char2->getY() - char2->getDy()) < this->height ||
				fabs(this->y + this->dy - char2->getY() - char2->getDy()) < char2->getHeight()
				)
				) return true;
		}
		if (direccion == -1) {
			if (
				x > char2->getX()
				&&
				(
				fabs(this->y + this->dy - char2->getY() - char2->getDy()) < this->height ||
				fabs(this->y + this->dy - char2->getY() - char2->getDy()) < char2->getHeight()
				)
				) return true;
		}
		return false;
	}

	virtual void AIMove(Character* p) {}
	virtual void AIDraw(BufferedGraphics^ buffer, Character* player, Bitmap^ bmp, bool modoJefe, int blockX) {}
};

/// <summary>
/// Obligaciones para cada AI:
/// 1. Debe tener su propio valor de AI_Identity en el Constructor
/// 2. Debe declarar si es amigo o enemigo (enemy = false, enemy = true)
/// </summary>
class Robotin : public AI {      //Se mueve de derecha a izquierda,
protected:					     //si ve al jugador, carga hacia esa direccion
	int radio;
	int velocidad;
	int derechaMax;
	int izquierdaMax;

	bool shootTimeout;
	float shootTimeout_Timer;
	float shootTimeout_Timer_Max;
public:
	Robotin(int iX, int iY, int maxIzquierda, int maxDerecha) {
		this->x = iX * 20;
		this->y = iY * 20;
		dx = 0;
		dy = 0;
		width = 50;
		height = 50;
		this->radio = 70;
		this->velocidad = 5;
		this->direccion = 1;     // Empiezan moviendose a la derecha
		this->derechaMax =  x + maxDerecha * 20; //agregar iX
		this->izquierdaMax =  x - maxIzquierda * 20;  //agregar iY
		AI_Identity = 0;
		imgIndex = 0;
		imgWidth = 4;
		imgHeight = 2;
		maxHealth = 12;
		health = maxHealth;
		enemy = true;
		shoot = false;
		shootTimeout = false;
		shootTimeout_Timer = 0;
		shootTimeout_Timer_Max = 0.5;
		damage = 4;
	}
	~Robotin() {}

	void AIDraw(BufferedGraphics^ buffer, Character* player, Bitmap^ bmp, bool modoJefe, int blockX) {
		indexPass();

		Rectangle area = Rectangle(bmp->Width / imgWidth * (imgIndex % imgWidth), bmp->Height / imgHeight * int(imgIndex / imgWidth), bmp->Width / imgWidth, bmp->Height / imgHeight);
		Rectangle limit = Rectangle(getMapAIX(player, modoJefe, blockX), getMapAIY(player), width, height);
		buffer->Graphics->DrawImage(bmp, limit, area, GraphicsUnit::Pixel);
	}

	void indexPass() {
		imgIndex++;

		if (imgIndex >= 4 && direccion == -1) {
			imgIndex = 0;
		}
		if (imgIndex < 4 && direccion == 1) {
			imgIndex += 4;
		}
		if (imgIndex >= 8 && direccion == 1) {
			imgIndex = 4;
		}
	}

	void AIMove(Character* p) {
		timers();

		if (!isPlayerForward(p)) {
			accionMovimiento(p);
		}
		else {
			accionAtacar(p);
		}
	}

	void timers() {
		if (shootTimeout) shootTimeoutEvent();
	}

	void shootTimeoutEvent() {
		shootTimeout_Timer += 50 / 1000.0;
		
		if (shootTimeout_Timer >= shootTimeout_Timer_Max) {
			shootTimeout_Timer = 0;
			shootTimeout = false;
		}
	}
	
	void accionMovimiento(Character* p) {
		if (x + dx < izquierdaMax) {    //Si llega a su posición maxima derecha, cambia de dirección
			direccion = 1;
		}
		if (x + dx > derechaMax) {  // Si llega a su posición maxima izquierda, cambia de dirección
			direccion = -1;
		}

		dx = velocidad * direccion;
		x += dx;
		dx = 0;
	}

	void accionAtacar(Character* p) {
		dx = 0;
		dy = 0;
		if (!shootTimeout) shoot = true;

		shootTimeout = true;
	}
};

class Medico1 : public AI {
protected:					     
	int direccion;
	int radio;
	int velocidad;
	int derechaMax;
	int izquierdaMax;
public:
	Medico1(int iX, int iY, int maxX, int maxY){
		this->x = iX * 20;
		this->y = iY * 20;
		dx = 0;
		dy = 0;
		width = 20;
		height = 20;
		this->radio = 70;
		this->velocidad = 12;
		this->direccion = 1;
		AI_Identity = 1;
		health = 99;
		enemy = false;
	}
	~Medico1() {}

	void AIDraw(BufferedGraphics^ buffer, Character* player, Bitmap^ bmp, bool modoJefe, int blockX) {
		buffer->Graphics->FillRectangle(Brushes::Green, getMapAIX(player, modoJefe, blockX), getMapAIY(player), width, height);
	}

	void AIMove(Character* p) {}
};

class Babosin : public AI {
protected:
	float AttackTimer;
	float AttackTimer_Max;
public:
	Babosin(int x, int y) {
		// Character
		this->x = x * 20;
		this->y = y * 20;
		this->dx = 0;
		this->dy = 0;
		this->width = 30;
		this->height = 30;
		this->imgIndex = 0;
		this->imgWidth = 8;
		this->imgHeight = 2;
		this->gravityTaken = 0;
		this->maxHealth = 10;
		this->health = maxHealth;
		this->damageTaken = 0;
		this->damageTaken_Timer = 0;
		this->damageTaken_Timer_Max = 0;
		// AI
		this->AI_Identity = 2;
		this->direccion = 0; // Unused
		this->damage = 4;
		this->enemy = true;
		this->shoot = false;
		// this
		AttackTimer = 0;
		AttackTimer_Max = 1.1;
	}
    ~Babosin(){}

	void AIDraw(BufferedGraphics^ buffer, Character* player, Bitmap^ bmp, bool modoJefe, int blockX) {
		indexPass();

		Rectangle area = Rectangle(bmp->Width / imgWidth * (imgIndex % imgWidth), bmp->Height / imgHeight * int(imgIndex / imgWidth), bmp->Width / imgWidth, bmp->Height / imgHeight);
		Rectangle limit = Rectangle(getMapAIX(player, modoJefe, blockX), getMapAIY(player), width, height);
		buffer->Graphics->DrawImage(bmp, limit, area, GraphicsUnit::Pixel);
	}
	
	void indexPass() {
		imgIndex++;

		if (imgIndex >= imgWidth * imgHeight)
			imgIndex = 0;
	}

	void AIMove(Character* p) {
		AttackTimer += 50.0 / 1000;

		if (AttackTimer >= AttackTimer_Max) {
			accionDispararBaba();
		}
	}

	void accionDispararBaba() {
		AttackTimer = 0;
		shoot = true;
	}
};

class Bumblebee : public AI {
protected:
	bool enIntermedio;
	int bounces;
	int accionObligada;
	bool firstTime;
	bool phase2;
public:
	Bumblebee(int x, int y) {
		// Character
		this->x = x * 20;
		this->y = y * 20;
		this->dx = 0;
		this->dy = 0;
		this->width = 100;
		this->height = 100;
		this->imgIndex = 0;
		this->imgWidth = 4;
		this->imgHeight = 2;
		this->gravityTaken = 0;
		this->maxHealth = 300;
		this->health = maxHealth;
		this->damageTaken = 0;
		this->damageTaken_Timer = 0;
		this->damageTaken_Timer_Max = 0;
		// AI
		this->AI_Identity = 3;
		this->direccion = 0; // Unused
		this->damage = 4;
		this->enemy = true;
		this->shoot = false;
		// this
		this->enIntermedio = true;
		this->bounces = 0;
		this->accionObligada = -1;
		this->firstTime = true;
		this->phase2 = false;
	}
	~Bumblebee() {}

	void AIDraw(BufferedGraphics^ buffer, Character* player, Bitmap^ bmp, bool modoJefe, int blockX) {
		indexPass();


		Rectangle area = Rectangle(bmp->Width / imgWidth * (imgIndex % imgWidth), bmp->Height / imgHeight * int(imgIndex / imgWidth), bmp->Width / imgWidth, bmp->Height / imgHeight);
		Rectangle limit = Rectangle(getMapAIX(player, modoJefe, blockX), getMapAIY(player), width, height);
		buffer->Graphics->DrawImage(bmp, limit, area, GraphicsUnit::Pixel);
	}

	void indexPass() {
		imgIndex++;

		if (imgIndex >= 4 && accionObligada + phase2 != 1)
			imgIndex = 0;
		if (imgIndex >= 8 && accionObligada + phase2 == 1)
			imgIndex = 4;
	}

	bool mapIntersects() {
		if ((map[int((y + dy - 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + dy - 0.01) / 20)][int((x + dx + width - 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X')) {
			return true;
		}
		return false;
	}
	void mapBounces() {
		bool haCambiado = false;
		// X-Collision
		if (map[int((y - 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + height + 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y - 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X' || map[int((y + height + 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X') {
			haCambiado = true;
			dx = -dx;
		}
		// Y Collision
		if (map[int((y + dy - 0.01) / 20)][int((x + 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + 0.01) / 20)] == 'X' || map[int((y + dy - 0.01) / 20)][int((x + width - 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + width - 0.01) / 20)] == 'X') {
			haCambiado = true;
			dy = -dy;
		}
		// Diagonal Collision
		if (!haCambiado && (map[int((y + dy - 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + dy - 0.01) / 20)][int((x + dx + width - 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X')) {
			dx = -dx;
			dy = -dy;
		}
	}

	void AIMove(Character* p) {


		if (!phase2 && maxHealth > health * 2) phase2 = true;
		determineIntermedio();

		if (enIntermedio) {
			accionRebotar();
		}
		else {
			accionesAtacar(p);
			
		}
	}

	void determineIntermedio() {
		if (bounces >= (2 - phase2)) {
			enIntermedio = false;
			bounces = 0;
		}
	}
	
	void accionesAtacar(Character* p) {
		Random^ r = gcnew Random();

		if (accionObligada == -1)
			accionObligada = r->Next(2);

		switch (accionObligada + phase2) {
		case 0:
			accionDisparar();
			break;
		case 1:
			accionLanzarseJugador(p);
			break;
		case 2:
			accionDisparar();
			break;
		}

		delete r;
	}
	void accionRebotar() {
		if (dx == 0 && dy == 0) {
			startBounceDir();
		}
		if (mapIntersects()) {
			bounces++;
			mapBounces();
		}

	}
	void startBounceDir() {
		Random^ r = gcnew Random();

		switch (r->Next(2)) {
		case 0:
			dx = 4*3;
			dy = 3*3;
			break;
		case 1:
			dx = 3*3;
			dy = 4*3;
			break;
		}

		delete r;
	}
	void accionDisparar() {
		shoot = true;

		enIntermedio = true;
		accionObligada = -1;
		firstTime = true;
	}
	void accionLanzarseJugador(Character* p) {
		if (firstTime) {
			int changeX = p->getX() + p->getWidth() / 2.0 - x - width / 2.0;
			int changeY = p->getY() + p->getHeight() / 2.0 - y - height / 2.0;

			double mag = sqrt(changeX * changeX + changeY * changeY);

			dx = 16 * changeX / mag;
			dy = 16 * changeY / mag;

			imgIndex = 4;
			firstTime = false;
		}

		if (mapIntersects()) {
			enIntermedio = true;
			accionObligada = -1;
			dx = 0;
			dy = 0;
			firstTime = true;
		}
	}
};


class HealthStation : public AI {
protected:

public:
	HealthStation(int x, int y) {
		// Character
		this->x = x * 20;
		this->y = y * 20;
		this->dx = 0;
		this->dy = 0;
		this->width = 55;
		this->height = 60;
		this->imgIndex = 0;
		this->imgWidth = 1;
		this->imgHeight = 1;
		this->gravityTaken = 0;
		this->maxHealth = 100;
		this->health = maxHealth;
		this->damageTaken = 0;
		this->damageTaken_Timer = 0;
		this->damageTaken_Timer_Max = 0;
		// AI
		this->AI_Identity = 4;
		this->direccion = 0; // Unused
		this->damage = 4;
		this->enemy = false;
		this->shoot = false;
		// this
	}
	~HealthStation() {}

	void AIDraw(BufferedGraphics^ buffer, Character* player, Bitmap^ bmp, bool modoJefe, int blockX) {
		indexPass();


		Rectangle area = Rectangle(bmp->Width / imgWidth * (imgIndex % imgWidth), bmp->Height / imgHeight * int(imgIndex / imgWidth), bmp->Width / imgWidth, bmp->Height / imgHeight);
		Rectangle limit = Rectangle(getMapAIX(player, modoJefe, blockX), getMapAIY(player), width, height);
		buffer->Graphics->DrawImage(bmp, limit, area, GraphicsUnit::Pixel);

		if (possiblyCollides(player)) {
			RectangleF rect = Rectangle(getMapAIX(player, modoJefe, blockX) - 2, getMapAIY(player) - 5, width + 4, 10);
			buffer->Graphics->FillRectangle(Brushes::White, rect);
			buffer->Graphics->DrawString("E: Interact", gcnew Font("Arial", 7), Brushes::Black, rect);
		}
	}

	void indexPass() {
		imgIndex++;

		if (imgIndex >= imgWidth * imgHeight)
			imgIndex = 0;
	}
};


class UPC : public AI {
protected:
	bool enIntermedio;
	float timer;
	float timer_Max;
	bool phase2;
	int attackEvent;
	bool hazloOnce;
public:
	UPC(int x, int y) {
		// Character
		this->x = x * 20;
		this->y = y * 20;
		this->dx = 0;
		this->dy = 0;
		this->width = 225;
		this->height = 150;
		this->imgIndex = 0;
		this->imgWidth = 4;
		this->imgHeight = 1;
		this->gravityTaken = 0;
		this->maxHealth = 800;
		this->health = maxHealth;
		this->damageTaken = 0;
		this->damageTaken_Timer = 0;
		this->damageTaken_Timer_Max = 0;
		// AI
		this->AI_Identity = 7;
		this->direccion = 0; // Unused
		this->damage = 4;
		this->enemy = true;
		this->shoot = false;
		this->UPC_IdentityShoot = 0;
		// this
		this->enIntermedio = true;
		this->phase2 = false;
		this->attackEvent = -1;
		this->hazloOnce = false;
	}
	~UPC() {}

	void AIDraw(BufferedGraphics^ buffer, Character* player, Bitmap^ bmp, bool modoJefe, int blockX) {
		Rectangle area = Rectangle(bmp->Width / imgWidth * (imgIndex % imgWidth), bmp->Height / imgHeight * int(imgIndex / imgWidth), bmp->Width / imgWidth, bmp->Height / imgHeight);
		Rectangle limit = Rectangle(getMapAIX(player, modoJefe, blockX), getMapAIY(player), width, height);
		buffer->Graphics->DrawImage(bmp, limit, area, GraphicsUnit::Pixel);
	}

	bool mapIntersects() {
		if ((map[int((y + dy - 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + dy - 0.01) / 20)][int((x + dx + width - 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X')) {
			return true;
		}
		return false;
	}
	void mapBounces() {
		bool haCambiado = false;
		// X-Collision
		if (map[int((y - 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + height + 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y - 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X' || map[int((y + height + 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X') {
			haCambiado = true;
			dx = -dx;
		}
		// Y Collision
		if (map[int((y + dy - 0.01) / 20)][int((x + 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + 0.01) / 20)] == 'X' || map[int((y + dy - 0.01) / 20)][int((x + width - 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + width - 0.01) / 20)] == 'X') {
			haCambiado = true;
			dy = -dy;
		}
		// Diagonal Collision
		if (!haCambiado && (map[int((y + dy - 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + dy - 0.01) / 20)][int((x + dx + width - 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X')) {
			dx = -dx;
			dy = -dy;
		}
	}
	
	void AIMove(Character* p) {
		elegirIntermedio();

		if (enIntermedio) {
			accionDescansar();
		}
		else {
			accionesAtacar(p);

		}
	}
	void elegirIntermedio() {
		timer += 50 / 1000.0;

		if (maxHealth >= health * 2) phase2 = true;
		if (enIntermedio && timer >= timer_Max) {
			Random^ r = gcnew Random();

			enIntermedio = false;
			attackEvent = r->Next(3);
			hazloOnce = false;
			timer = 0;
			UPC_IdentityShoot = attackEvent;
			switch (attackEvent) {
			case 0:
				timer_Max = 2;
				break;
			case 1:
				timer_Max = 2;
				break;
			case 2:
				timer_Max = 2 - phase2 * 0.5;
				break;
			}

			delete r;
		}
		if (!enIntermedio && timer >= timer_Max) {
			enIntermedio = true;
			hazloOnce = false;
			attackEvent = -1;
			timer = 0;
			timer_Max = 2 - phase2 * 1.75;
			attackEvent = 0;
		}
	}
	void accionDescansar() {
		imgIndex = 0;

		if (timer >= timer_Max) {
			enIntermedio = false;
		}
	}
	void accionesAtacar(Character* p) {
		switch (attackEvent) {
		case 0:
			accionFire();
			break;
		case 1:
			accionMissiles();
			break;
		case 2:
			accionWall();
			break;
		}
	}
	void accionFire() {
		imgIndex = 1;

		Random^ r = gcnew Random();

		if (r->Next(2)) {
			shoot = true;
		}

		delete r;
	}
	void accionMissiles() {
		imgIndex = 2;

		Random^ r = gcnew Random();

		if (timer <= 1 && r->Next(2)) {
			shoot = true;
		}

		delete r;
	}
	void accionWall() {
		imgIndex = 3;

		if (timer >= 1 - phase2 * 0.5 && !hazloOnce) {
			hazloOnce = true;
			shoot = true;
		}
	}
	
	/*
	void determineIntermedio() {
		if (bounces >= (2 - phase2)) {
			enIntermedio = false;
			bounces = 0;
		}
	}

	void accionesAtacar(Character* p) {
		Random^ r = gcnew Random();

		if (accionObligada == -1)
			accionObligada = r->Next(2);

		switch (accionObligada + phase2) {
		case 0:
			accionDisparar();
			break;
		case 1:
			accionLanzarseJugador(p);
			break;
		case 2:
			accionDisparar();
			break;
		}

		delete r;
	}
	void accionRebotar() {
		if (dx == 0 && dy == 0) {
			startBounceDir();
		}
		if (mapIntersects()) {
			bounces++;
			mapBounces();
		}

	}
	void startBounceDir() {
		Random^ r = gcnew Random();

		switch (r->Next(2)) {
		case 0:
			dx = 4 * 3;
			dy = 3 * 3;
			break;
		case 1:
			dx = 3 * 3;
			dy = 4 * 3;
			break;
		}

		delete r;
	}
	void accionDisparar() {
		shoot = true;

		enIntermedio = true;
		accionObligada = -1;
		firstTime = true;
	}
	void accionLanzarseJugador(Character* p) {
		if (firstTime) {
			int changeX = p->getX() + p->getWidth() / 2.0 - x - width / 2.0;
			int changeY = p->getY() + p->getHeight() / 2.0 - y - height / 2.0;

			double mag = sqrt(changeX * changeX + changeY * changeY);

			dx = 16 * changeX / mag;
			dy = 16 * changeY / mag;

			imgIndex = 4;
			firstTime = false;
		}

		if (mapIntersects()) {
			enIntermedio = true;
			accionObligada = -1;
			dx = 0;
			dy = 0;
			firstTime = true;
		}
	}
	*/
};

class Aranha : public AI {
protected:
	float AttackTimer;
	float AttackTimer_Max;
public:
	Aranha(int x, int y) {
		// Character
		this->x = x * 20;
		this->y = y * 20;
		this->dx = 0;
		this->dy = 0;
		this->width = 30;
		this->height = 50;
		this->imgIndex = 0;
		this->imgWidth = 1;
		this->imgHeight = 1;
		this->gravityTaken = 0;
		this->maxHealth = 12;
		this->health = maxHealth;
		this->damageTaken = 0;
		this->damageTaken_Timer = 0;
		this->damageTaken_Timer_Max = 0;
		// AI
		this->AI_Identity = 6;
		this->direccion = 0; // Unused
		this->damage = 6;
		this->enemy = true;
		this->shoot = false;
		// this
		AttackTimer = 0;
		AttackTimer_Max = 1.1;
	}
	~Aranha() {}

	void AIDraw(BufferedGraphics^ buffer, Character* player, Bitmap^ bmp, bool modoJefe, int blockX) {
		indexPass();

		Rectangle area = Rectangle(bmp->Width / imgWidth * (imgIndex % imgWidth), bmp->Height / imgHeight * int(imgIndex / imgWidth), bmp->Width / imgWidth, bmp->Height / imgHeight);
		Rectangle limit = Rectangle(getMapAIX(player, modoJefe, blockX), getMapAIY(player) - 10, width, height);
		buffer->Graphics->DrawImage(bmp, limit, area, GraphicsUnit::Pixel);
	}

	void indexPass() {
		imgIndex++;

		if (imgIndex >= imgWidth * imgHeight)
			imgIndex = 0;
	}

	void AIMove(Character* p) {
		AttackTimer += 50.0 / 1000;

		if (AttackTimer >= AttackTimer_Max) {
			accionDispararBaba();
		}
	}

	void accionDispararBaba() {
		AttackTimer = 0;
		shoot = true;
	}
};


class Bicho : public AI {      //Se mueve de derecha a izquierda,
protected:					     //si ve al jugador, carga hacia esa direccion
	int radio;
	int velocidad;
	int derechaMax;
	int izquierdaMax;

	bool shootTimeout;
	float shootTimeout_Timer;
	float shootTimeout_Timer_Max;
public:
	Bicho(int iX, int iY, int maxIzquierda, int maxDerecha) {
		this->x = iX * 20;
		this->y = iY * 20;
		dx = 0;
		dy = 0;
		width = 50;
		height = 50;
		this->radio = 70;
		this->velocidad = 5;
		this->direccion = 1;     // Empiezan moviendose a la derecha
		this->derechaMax = x + maxDerecha * 20; //agregar iX
		this->izquierdaMax = x - maxIzquierda * 20;  //agregar iY
		// AI IDENTITY
		AI_Identity = 5;
		imgIndex = 0;
		imgWidth = 4;
		imgHeight = 2;
		maxHealth = 15;
		health = maxHealth;
		enemy = true;
		shoot = false;
		shootTimeout = false;
		shootTimeout_Timer = 0;
		shootTimeout_Timer_Max = 0.5;
		damage = 7;
	}
	~Bicho() {}

	void AIDraw(BufferedGraphics^ buffer, Character* player, Bitmap^ bmp, bool modoJefe, int blockX) {
		indexPass();

		Rectangle area = Rectangle(bmp->Width / imgWidth * (imgIndex % imgWidth), bmp->Height / imgHeight * int(imgIndex / imgWidth), bmp->Width / imgWidth, bmp->Height / imgHeight);
		Rectangle limit = Rectangle(getMapAIX(player, modoJefe, blockX), getMapAIY(player), width, height);
		buffer->Graphics->DrawImage(bmp, limit, area, GraphicsUnit::Pixel);
	}

	void indexPass() {
		imgIndex++;

		if (imgIndex >= 4 && direccion == -1) {
			imgIndex = 0;
		}
		if (imgIndex < 4 && direccion == 1) {
			imgIndex += 4;
		}
		if (imgIndex >= 8 && direccion == 1) {
			imgIndex = 4;
		}
	}

	void AIMove(Character* p) {
		timers();

		if (!isPlayerForward(p)) {
			accionMovimiento(p);
		}
		else {
			accionAtacar(p);
		}
	}

	void timers() {
		if (shootTimeout) shootTimeoutEvent();
	}

	void shootTimeoutEvent() {
		shootTimeout_Timer += 50 / 1000.0;

		if (shootTimeout_Timer >= shootTimeout_Timer_Max) {
			shootTimeout_Timer = 0;
			shootTimeout = false;
		}
	}

	void accionMovimiento(Character* p) {
		if (x + dx < izquierdaMax) {    //Si llega a su posición maxima derecha, cambia de dirección
			direccion = 1;
		}
		if (x + dx > derechaMax) {  // Si llega a su posición maxima izquierda, cambia de dirección
			direccion = -1;
		}

		dx = velocidad * direccion;
		x += dx;
		dx = 0;
	}

	void accionAtacar(Character* p) {
		dx = 0;
		dy = 0;
		if (!shootTimeout) shoot = true;

		shootTimeout = true;
	}
};

class PuppetMaster : public AI {
protected:
	bool enIntermedio;
	float timer;
	float timer_Max;
	bool phase2;
	int attackEvent;
	bool hazloOnce;
	float teleportTimer;
	float teleportTimer_Max;
	int blockX;
	int blockY;
public:
	PuppetMaster(int x, int y) {
		// Character
		this->x = x * 20;
		this->y = y * 20;
		this->dx = 0;
		this->dy = 0;
		this->width = 60;
		this->height = 60;
		this->imgIndex = 0;
		this->imgWidth = 4;
		this->imgHeight = 1;
		this->gravityTaken = 0;
		this->maxHealth = 800;
		this->health = maxHealth;
		this->damageTaken = 0;
		this->damageTaken_Timer = 0;
		this->damageTaken_Timer_Max = 0;
		// AI
		this->AI_Identity = 7;
		this->direccion = 0; // Unused
		this->damage = 4;
		this->enemy = true;
		this->shoot = false;
		this->UPC_IdentityShoot = 0;
		// this
		this->enIntermedio = true;
		this->phase2 = false;
		this->attackEvent = -1;
		this->hazloOnce = false;
		this->teleportTimer = 0;
		this->teleportTimer_Max = 0.5;
		// Components that should've been parameters
		this->blockX = 25;
		this->blockY = 14 * 3;
	}
	~PuppetMaster() {}

	void AIDraw(BufferedGraphics^ buffer, Character* player, Bitmap^ bmp, bool modoJefe, int blockX) {
		Rectangle area = Rectangle(bmp->Width / imgWidth * (imgIndex % imgWidth), bmp->Height / imgHeight * int(imgIndex / imgWidth), bmp->Width / imgWidth, bmp->Height / imgHeight);
		Rectangle limit = Rectangle(getMapAIX(player, modoJefe, blockX), getMapAIY(player), width, height);
		buffer->Graphics->DrawImage(bmp, limit, area, GraphicsUnit::Pixel);
	}

	bool mapIntersects() {
		if ((map[int((y + dy - 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + dy - 0.01) / 20)][int((x + dx + width - 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X')) {
			return true;
		}
		return false;
	}
	void mapBounces() {
		bool haCambiado = false;
		// X-Collision
		if (map[int((y - 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + height + 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y - 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X' || map[int((y + height + 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X') {
			haCambiado = true;
			dx = -dx;
		}
		// Y Collision
		if (map[int((y + dy - 0.01) / 20)][int((x + 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + 0.01) / 20)] == 'X' || map[int((y + dy - 0.01) / 20)][int((x + width - 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + width - 0.01) / 20)] == 'X') {
			haCambiado = true;
			dy = -dy;
		}
		// Diagonal Collision
		if (!haCambiado && (map[int((y + dy - 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + dy - 0.01) / 20)][int((x + dx + width - 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + dx + 0.01) / 20)] == 'X' || map[int((y + height + dy + 0.01) / 20)][int((x + width + dx - 0.01) / 20)] == 'X')) {
			dx = -dx;
			dy = -dy;
		}
	}

	void AIMove(Character* p) {
		elegirIntermedio();

		if (enIntermedio) {
			accionTeleportar();
		}
		else {
			accionesAtacar(p);

		}
	}
	void elegirIntermedio() {
		timer += 50 / 1000.0;

		if (maxHealth >= health * 2) phase2 = true;
		if (enIntermedio && timer >= timer_Max) {
			Random^ r = gcnew Random();

			enIntermedio = false;
			teleportTimer = 0;
			attackEvent = r->Next(3);
			hazloOnce = false;
			timer = 0;
			UPC_IdentityShoot = attackEvent;
			switch (attackEvent) {
			case 0:
				timer_Max = 2;
				break;
			case 1:
				timer_Max = 2;
				break;
			case 2:
				timer_Max = 2 - phase2 * 0.5;
				break;
			}

			delete r;
		}
		if (!enIntermedio && timer >= timer_Max) {
			enIntermedio = true;
			hazloOnce = false;
			attackEvent = -1;
			timer = 0;
			timer_Max = 2 - phase2 * 1.75;
			attackEvent = 0;
		}
	}
	void accionTeleportar() {
		imgIndex = 0;
		teleportTimer += 50 / 1000.0;

		if (teleportTimer >= teleportTimer_Max) {
			Random^ r = gcnew Random();

			x = r->Next((blockX + 1) * 20, (blockX + 24) * 20 - width);
			y = r->Next((blockY + 2) * 20, (blockY + 4) * 20);

			delete r;

			teleportTimer = 0;
		}

		if (timer >= timer_Max) {
			enIntermedio = false;
		}
	}
	void accionesAtacar(Character* p) {
		switch (attackEvent) {
		case 0:
			accionFire();
			break;
		case 1:
			accionMissiles();
			break;
		case 2:
			accionWall();
			break;
		}
	}
	void accionFire() {
		if (!hazloOnce) {
			x = (blockX + 24) * 20 - width;
			y = (blockY + 3) * 20;
			hazloOnce = true;
		}

		imgIndex = 1;

		Random^ r = gcnew Random();

		if (r->Next(2)) {
			shoot = true;
		}

		delete r;
	}
	void accionMissiles() {
		if (!hazloOnce) {
			x = (blockX + 2) * 20;
			y = (blockY + 3) * 20;
			hazloOnce = true;
		}

		imgIndex = 2;

		Random^ r = gcnew Random();

		if (timer <= 1 && r->Next(2)) {
			shoot = true;
		}

		delete r;
	}
	void accionWall() {
		imgIndex = 3;

		if (timer >= 1 - phase2 * 0.5 && !hazloOnce) {
			hazloOnce = true;
			shoot = true;
		}
	}

	/*
	void determineIntermedio() {
		if (bounces >= (2 - phase2)) {
			enIntermedio = false;
			bounces = 0;
		}
	}

	void accionesAtacar(Character* p) {
		Random^ r = gcnew Random();

		if (accionObligada == -1)
			accionObligada = r->Next(2);

		switch (accionObligada + phase2) {
		case 0:
			accionDisparar();
			break;
		case 1:
			accionLanzarseJugador(p);
			break;
		case 2:
			accionDisparar();
			break;
		}

		delete r;
	}
	void accionRebotar() {
		if (dx == 0 && dy == 0) {
			startBounceDir();
		}
		if (mapIntersects()) {
			bounces++;
			mapBounces();
		}

	}
	void startBounceDir() {
		Random^ r = gcnew Random();

		switch (r->Next(2)) {
		case 0:
			dx = 4 * 3;
			dy = 3 * 3;
			break;
		case 1:
			dx = 3 * 3;
			dy = 4 * 3;
			break;
		}

		delete r;
	}
	void accionDisparar() {
		shoot = true;

		enIntermedio = true;
		accionObligada = -1;
		firstTime = true;
	}
	void accionLanzarseJugador(Character* p) {
		if (firstTime) {
			int changeX = p->getX() + p->getWidth() / 2.0 - x - width / 2.0;
			int changeY = p->getY() + p->getHeight() / 2.0 - y - height / 2.0;

			double mag = sqrt(changeX * changeX + changeY * changeY);

			dx = 16 * changeX / mag;
			dy = 16 * changeY / mag;

			imgIndex = 4;
			firstTime = false;
		}

		if (mapIntersects()) {
			enIntermedio = true;
			accionObligada = -1;
			dx = 0;
			dy = 0;
			firstTime = true;
		}
	}
	*/
};