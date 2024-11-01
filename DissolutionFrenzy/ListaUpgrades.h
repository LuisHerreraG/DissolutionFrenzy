#pragma once

#include "Player.h"
#include "Upgrades.h"
#include <vector>

using namespace std;
using namespace System;
using namespace Drawing;

class ListaUpgrades {
public:
	vector <Upgrade*> teamUpgrades;

	ListaUpgrades() {}
	~ListaUpgrades() {
		for (int i = 0; i < teamUpgrades.size(); i++) {
			delete teamUpgrades[i];
		}
	}

	void collisionPlayer(Player* player) {
		for (int i = 0; i < teamUpgrades.size(); i++) {
			if (teamUpgrades[i]->possiblyCollides(player)) {
				
				// (1) Upgrade Player
				switch (teamUpgrades[i]->getType()) {
				case HealthBoost:
					player->upgrade_Health();
					break;
				case AttackBoost:
					player->upgrade_Attack();
					break;
				case ResistanceBoost:
					player->upgrade_Resistance();
					break;
				}
				
				// (2) Delete Upgrade
				deleteItem(i);
				i--;
			}
		}
	}
	void deleteItem(int i) {
		delete teamUpgrades[i];
		teamUpgrades.erase(teamUpgrades.begin() + i);
	}
	void addItem(int x, int y, UpgradeType type) {
		teamUpgrades.push_back(new Upgrade(x * 20, y * 20, type));
	}
	void todosDraw(BufferedGraphics^ buffer, Player* player, Bitmap^ healthUpgrade, Bitmap^ resistanceUpgrade, Bitmap^ attackUpgrade) {
		for (int i = 0; i < teamUpgrades.size(); i++) {
			switch (teamUpgrades[i]->getType()) {
			case HealthBoost:
				teamUpgrades[i]->draw(buffer, player, healthUpgrade); // Sprite ?x?
				break;
			case AttackBoost:
				teamUpgrades[i]->draw(buffer, player, attackUpgrade);
				break;
			case ResistanceBoost:
				teamUpgrades[i]->draw(buffer, player, resistanceUpgrade);
				break;
			}
		}
	}
};