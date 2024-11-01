#pragma once

#include "Character.h"
#include "Player.h"
#include <vector>

using namespace std;
using namespace System;
using namespace Drawing;

class ListaAI { // Nombre Completo: ListaAIActivos
public:
	vector <AI*> compound;
	ListaAI() {}
	~ListaAI() {
		for (int i = 0; i < compound.size(); i++) {
			delete compound[i];
		}
	}

	int size() {
		return compound.size();
	}

	void todosAIMove(Character* p, bool modoJefe, int blockX) {
		for (int i = 0; i < compound.size(); i++) {
			if (compound[i]->cameraIntersect(p, modoJefe, blockX)) {
				compound[i]->AIMove(p);
			}
		}
	}
	void todosUseVelocity() {
		for (int i = 0; i < compound.size(); i++) {
			compound[i]->useVelocity();
		}
	}
	void todosDraw(BufferedGraphics^ buffer, Character* player, bool modoJefe, int blockX, Bitmap^ robotin, Bitmap^ babosin, Bitmap^ abejorro, Bitmap^ aranha, Bitmap^ bicho, Bitmap^ upc, Bitmap^ capsula) {
		for (int i = 0; i < compound.size(); i++) {
			if (compound[i]->cameraIntersect(player, modoJefe, blockX)) {
				switch (compound[i]->getAI_Identity()) {
				case 0: // ROBOTIN
					compound[i]->AIDraw(buffer, player, robotin, modoJefe, blockX); // Sprite de 5x8
					break;
				case 1: // MEDICO
					compound[i]->AIDraw(buffer, player, robotin, modoJefe, blockX);
					break;
				case 2: // BABASIN
					compound[i]->AIDraw(buffer, player, babosin, modoJefe, blockX);
					break;
				case 3: // ABEJORRO
					compound[i]->AIDraw(buffer, player, abejorro, modoJefe, blockX);
					break;
				case 4: // STATION
					compound[i]->AIDraw(buffer, player, capsula, modoJefe, blockX);
					break;
				case 5: // EL BICHO
					compound[i]->AIDraw(buffer, player, bicho, modoJefe, blockX);
					break;
				case 6: // ARANHA
					compound[i]->AIDraw(buffer, player, aranha, modoJefe, blockX);
					break;
				case 7: // UPC
					compound[i]->AIDraw(buffer, player, upc, modoJefe, blockX);
					break;
				case 8: // PUPPET MASTER
					compound[i]->AIDraw(buffer, player, robotin, modoJefe, blockX);
					break;
				}
			}
		}
	}
	bool interaccionEstacionJugador(bool interaccion, Character* p) {
		for (int i = 0; i < compound.size(); i++) {
			if (compound[i]->getAI_Identity() == 4 && interaccion && compound[i]->possiblyCollides(p)) {
				return true;
			}
		}
		return false;
	}
	void deleteAll() {
		while (compound.size() > 0) {
			delete compound[0];
			compound.erase(compound.begin());
		}
	}


	void solvingCollision(Character* jugador) {
		/*
		vector <Character*> colisionadores;
		for (int i = 0; i < compound.size(); i++) {
			if (player->possiblyCollides(compound[i]))
				colisionadores.push_back(compound[i]);
		}
		if (colisionadores.size() > 1) {
			player->cancelVelocity();
			for (int i = 0; i < colisionadores.size(); i++) {
				colisionadores[i]->cancelVelocity();
			}
		}
		if (colisionadores.size() == 1) {
			player->cancelVelocity();
			if (player->possiblyCollides(colisionadores[0])) {
				colisionadores[0]->cancelVelocity();
			}
		}
		*/
		for (int i = 0; i < compound.size(); i++) {
			if (compound[i]->getEnemy() && compound[i]->possiblyCollides(jugador)) {
				jugador->damaged(2);
			}
		}
	}
	void removeItem(int i) {
		delete compound[i];
		compound.erase(compound.begin() + i);
	}
	void deadAIsRemoval() {
		for (int i = 0; i < compound.size(); i++) {
			if (compound[i]->getHealth() <= 0) {
				removeItem(i);
				i--;
			}
		}
	}
	void addRobotin(int x, int y, int izquierda, int derecha) {
		compound.push_back(new Robotin(x, y, izquierda, derecha));
	}
	void addBabasin(int x, int y) {
		compound.push_back(new Babosin(x, y));
	}
	void addMedico1(int x, int y) {
		compound.push_back(new Medico1(x, y, 4, 4));
	}
	void addBumblebee(int x, int y) {
		compound.push_back(new Bumblebee(x, y));
	}
	void addStation(int x, int y) {
		compound.push_back(new HealthStation(x, y));
	}
	void addAranha(int x, int y) {
		compound.push_back(new Aranha(x, y));
	}
	void addBicho(int x, int y, int izquierda, int derecha) {
		compound.push_back(new Bicho(x, y, izquierda, derecha));
	}
	void addUPC(int x, int y) {
		compound.push_back(new UPC(x, y));
	}
	void addPuppetMaster(int x, int y) {
		compound.push_back(new PuppetMaster(x, y));
	}
	bool deadBossCheck() {
		return compound[0]->getHealth() <= 0;
	}
};