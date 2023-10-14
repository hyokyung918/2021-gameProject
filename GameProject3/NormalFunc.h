#pragma once
#include "GameObject.h"

void initEnemies(vector<GameObject>& vEnemies);
void InputAndLogic(int& count, GameObject& player, vector<GameObject>& vEnemies, vector<GameObject>& vBullets, bool& spacePressed);
bool ifOverlap(GameObject& player, vector<GameObject>& vEnemies);
void getScore(int& score, vector<GameObject>& vBullets, vector<GameObject>& vEnemies);
int ifEnd(vector<GameObject>& vEnemies);
char ifContinue(int ifWin, int& score, int& count);