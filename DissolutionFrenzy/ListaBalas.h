#pragma once

#include "Character.h"
#include "ListaNPCs.h"
#include "Balas.h"
#include <vector>
#include "Player.h"



using namespace std;
using namespace System;
using namespace Drawing;

class ListaBalas {
public:
	vector <Projectile*> teamBalas;

	ListaBalas() {}
	~ListaBalas() {
		for (int i = 0; i < teamBalas.size(); i++) {
			delete teamBalas[i];
		}
	}

	void checkCollision(Character* jug, ListaAI* AIActivos, bool modoJefe, int blockX) {
		for (int i = 0; i < teamBalas.size(); i++) {
			if (teamBalas[i]->cameraIntersect(jug, modoJefe, blockX) && !teamBalas[i]->mapIntersects()) {
				if (checkHitPlayer(jug, i)) {
					i--;
					continue;
				} /////////////////////
				if (checkHitAIGroup(AIActivos, i)) i--;
			}
			else {
				removeItem(i);
			}
		}
	}
	void addItem(float x, float y, float dx, float dy, int width, int height, int damage, Character* sender, int bala_Identity) {
		teamBalas.push_back(new Projectile(x, y, dx, dy, width, height, damage, sender, bala_Identity));
	}
	void removeItem(int i) {
		delete teamBalas[i];
		teamBalas.erase(teamBalas.begin() + i);
	}
	bool checkHitPlayer(Character* jug, int i) {
		if (jug != teamBalas[i]->getSender() && teamBalas[i]->possiblyCollides(jug)) {
			jug->damaged(teamBalas[i]->getDamage());
			
			removeItem(i);
			return true;
		}
		return false;
	}
	bool checkHitAIGroup(ListaAI* AIGroup, int i) {
		for (int j = 0; j < AIGroup->size(); j++) {
			if (AIGroup->compound[j]->getEnemy() == true && AIGroup->compound[j] != teamBalas[i]->getSender() && teamBalas[i]->possiblyCollides(AIGroup->compound[j])) {
				AIGroup->compound[j]->AIDamaged(teamBalas[i]->getDamage());
				removeItem(i);
				return true;
			}
		}
		return false;
	}
	void todosUseVelocity() {
		for (int i = 0; i < teamBalas.size(); i++) {
			teamBalas[i]->useVelocity();
		}
	}
	void createAIShoots(ListaAI* AIGroup) {
		Random^ r = gcnew Random();
		for (int i = 0; i < AIGroup->compound.size(); i++) {
			if (AIGroup->compound[i]->getShoot()) {
				switch (AIGroup->compound[i]->getAI_Identity()) {
				case 0: // ROBOTIN
					addItem(AIGroup->compound[i]->getX(), AIGroup->compound[i]->getY(), AIGroup->compound[i]->getDireccion() * 20, 0, 10, 5, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 1);
					break;
				case 1: // MEDICO
					break;
				case 2: // BABASIN
					addItem(AIGroup->compound[i]->getX(), AIGroup->compound[i]->getY(), 0, 20, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
					break;
				case 3: // ABEJORRO
					addItem(AIGroup->compound[i]->getX() + AIGroup->compound[i]->getWidth() / 2, AIGroup->compound[i]->getY() + AIGroup->compound[i]->getHeight() / 2, 5, 0, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
					addItem(AIGroup->compound[i]->getX() + AIGroup->compound[i]->getWidth() / 2, AIGroup->compound[i]->getY() + AIGroup->compound[i]->getHeight() / 2, 0, 5, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
					addItem(AIGroup->compound[i]->getX() + AIGroup->compound[i]->getWidth() / 2, AIGroup->compound[i]->getY() + AIGroup->compound[i]->getHeight() / 2, 4, 3, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
					addItem(AIGroup->compound[i]->getX() + AIGroup->compound[i]->getWidth() / 2, AIGroup->compound[i]->getY() + AIGroup->compound[i]->getHeight() / 2, -4, 3, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
					addItem(AIGroup->compound[i]->getX() + AIGroup->compound[i]->getWidth() / 2, AIGroup->compound[i]->getY() + AIGroup->compound[i]->getHeight() / 2, -5, 0, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
					addItem(AIGroup->compound[i]->getX() + AIGroup->compound[i]->getWidth() / 2, AIGroup->compound[i]->getY() + AIGroup->compound[i]->getHeight() / 2, 0, -5, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
					addItem(AIGroup->compound[i]->getX() + AIGroup->compound[i]->getWidth() / 2, AIGroup->compound[i]->getY() + AIGroup->compound[i]->getHeight() / 2, 4, -3, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
					addItem(AIGroup->compound[i]->getX() + AIGroup->compound[i]->getWidth() / 2, AIGroup->compound[i]->getY() + AIGroup->compound[i]->getHeight() / 2, -4, -3, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
					break;
				case 4: // STATION
					break;
				case 5: // EL BICHO
					addItem(AIGroup->compound[i]->getX(), AIGroup->compound[i]->getY(), AIGroup->compound[i]->getDireccion() * 20, 0, 10, 5, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 1);
					break;
				case 6: // ARANHA
					addItem(AIGroup->compound[i]->getX(), AIGroup->compound[i]->getY() + AIGroup->compound[i]->getHeight() / 2.0 + 0.1, 0, 15, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
					break;
				case 7: // UPC
					switch (AIGroup->compound[i]->getUPC_IdentityShoot()) {
					case 0: // Fire from Above
						switch (r->Next(3)) {
						case 0:
							addItem(AIGroup->compound[i]->getX() - r->Next(225), AIGroup->compound[i]->getY() - 6 * 20, 0, 15, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
							addItem(AIGroup->compound[i]->getX() - r->Next(300), AIGroup->compound[i]->getY() - 6 * 20, 0, 15, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
							break;
						case 1:
							addItem(AIGroup->compound[i]->getX() - r->Next(300), AIGroup->compound[i]->getY() - 6 * 20, 0, 15, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
							addItem(AIGroup->compound[i]->getX() - r->Next(125), AIGroup->compound[i]->getY() - 6 * 20, 0, 15, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
							break;
						case 2:
							addItem(AIGroup->compound[i]->getX() - r->Next(125), AIGroup->compound[i]->getY() - 6 * 20, 0, 15, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
							if (r->Next(2)) addItem(AIGroup->compound[i]->getX() - r->Next(225), AIGroup->compound[i]->getY() - 6 * 20, 0, 15, 15, 20, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 2);
							break;
						}
						break;
					case 1: // Missile From the Right
						addItem(AIGroup->compound[i]->getX() + AIGroup->compound[i]->getWidth(), AIGroup->compound[i]->getY() + AIGroup->compound[i]->getHeight() - r->Next(50), -15, 0, 10, 5, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 4);
						addItem(AIGroup->compound[i]->getX() - r->Next(300), AIGroup->compound[i]->getY() - 6 * 20, 0, 15, 10, 5, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 4);
						break;
					case 2: // Wall from the Front
						addItem(AIGroup->compound[i]->getX() - 10, AIGroup->compound[i]->getY() + AIGroup->compound[i]->getHeight() / 2, -17, 0, 50, 60, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 3);
						addItem(AIGroup->compound[i]->getX() - 235, AIGroup->compound[i]->getY() - 6 * 20, 0, 15, 50, 60, AIGroup->compound[i]->getDamage(), AIGroup->compound[i], 3);
						break;
					}
					break;
				case 8: // PUPPET MASTER
					break;

				}
				AIGroup->compound[i]->setShoot(false);
			}
		}
		delete r;
	}
	void todosDraw(BufferedGraphics^ buffer, Character* player, bool modoJefe, int blockX, Bitmap^ disparoJugador, Bitmap^ disparoRobotin, Bitmap^ disparoBabosin, Bitmap^ disparoWall, Bitmap^ fuego) {
		for (int i = 0; i < teamBalas.size(); i++) {
			switch (teamBalas[i]->getBala_Identity()) {
			case 0: // DISPARO JUGADOR
				teamBalas[i]->BalaDraw(buffer, player, disparoJugador, modoJefe, blockX); // Sprite de 5x8
				break;
			case 1: // DISPARO ROBOTIN
				teamBalas[i]->BalaDraw(buffer, player, disparoRobotin, modoJefe, blockX);
				break;
			case 2: // DISPARO BABASIN
				teamBalas[i]->BalaDraw(buffer, player, disparoBabosin, modoJefe, blockX);
				break;
			case 3: // DISPARO WALL
				teamBalas[i]->BalaDraw(buffer, player, disparoWall, modoJefe, blockX);
				break;
			case 4: // DISPARO WALL
				teamBalas[i]->BalaDraw(buffer, player, fuego, modoJefe, blockX);
				break;
			}
		}
	}
};