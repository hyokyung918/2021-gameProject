#include "GameField.h"
#include "GameObject.h"
#include "normalFunc.h"

int main() {
	GameField field;
	GameObject player(">-0-<", 24, 15);
	vector<GameObject> vBullets;
	vector<GameObject> vEnemies;
	initEnemies(vEnemies);

	int count = 0;
	int score = 0;
	bool spacePressed = false;

	while (1) {
		// Game Timing
		field.gameTiming();

		// Input & Logic
		InputAndLogic(count, player, vEnemies, vBullets, spacePressed);

		// Logic
		getScore(score, vBullets, vEnemies);
		int end = ifEnd(vEnemies);
		if (end != 0) {
			char ifCon = ifContinue(end, score, count);
			if (ifCon == 'y' || ifCon == 'Y') {
				player.resetPos(24, 15);
				vEnemies.clear();
				vBullets.clear();
				initEnemies(vEnemies);
				field.newStart();
				continue;
			}
			else
				return 0;
		}

		// Render Output (Print)
		field.drawField(score, player, vBullets, vEnemies);
	}
}