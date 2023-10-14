#include "GameField.h"

GameField::GameField() {
	for (int y = 0; y < SCR_HEIGHT; y++) {
		for (int x = 0; x < SCR_WIDTH; x++) {
			if (x == 0 || x == SCR_WIDTH - 1)
				field[y][x] = '|';
			else if (y == 0 || y == 2 || y == SCR_HEIGHT - 1)
				field[y][x] = '-';
			else
				field[y][x] = 9;
		}
	}

	char printScore[] = "score:";
	for (int index = 0; printScore[index] != 0; index++) {
		field[1][25 + index] = printScore[index];
	}
}

void GameField::gameTiming() {
	Sleep(30);
}

void GameField::drawField(int& score, GameObject& player, vector<GameObject>& vBullets, vector<GameObject>& vEnemies) {
	for (int y = 0; y < SCR_HEIGHT; y++) {
		for (int x = 0; x < SCR_WIDTH; x++) {
			screenBuffer.drawToBackBuffer(x, y, field[y][x]);
		}
	}

	screenBuffer.drawToBackBuffer(31, 1, score);
	player.printObject(screenBuffer);
	for (auto& i : vBullets)   i.printObject(screenBuffer);
	for (auto& i : vEnemies)   i.printObject(screenBuffer);
	screenBuffer.render();
}

void GameField::newStart() {
	ScreenBuffer newScreen;
	screenBuffer = newScreen;
}