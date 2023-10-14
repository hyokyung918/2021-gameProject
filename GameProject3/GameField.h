#pragma once
#include <iostream>
#include <Windows.h>
#include <synchapi.h>
#include "GameObject.h"
#include "ScreenBuffer.h"
using namespace std;

class GameField {
	char field[SCR_HEIGHT][SCR_WIDTH];
	ScreenBuffer screenBuffer;

public:
	GameField();
	void gameTiming();
	void drawField(int& score, GameObject& player, vector<GameObject>& vBullets, vector<GameObject>& vEnemies);
	void newStart();
};