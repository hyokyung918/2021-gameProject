#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include "ScreenBuffer.h"
class ScreenBuffer;

using namespace std;

class GameObject {
	string shape;
	COORD pos;

public:
	GameObject(string sh, short x, short y);
	GameObject(COORD newPos);
	void printObject(ScreenBuffer& screenBuffer);
	void moveObject(int dir);
	void resetPos(short x, short y);
	COORD returnPos() const;
};