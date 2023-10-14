#include "GameObject.h"

GameObject::GameObject(string sh, short x, short y) {
	shape = sh;
	pos = { x, y };
}

GameObject::GameObject(COORD newPos) {
	shape = "!";
	pos = newPos;
}

void GameObject::printObject(ScreenBuffer& screenBuffer) {
	int x = pos.X;
	int y = pos.Y;

	for (int index = 0; shape[index] != 0; index++)
		screenBuffer.drawToBackBuffer(x + index, y, shape[index]);
}

void GameObject::moveObject(int dir) {
	if (dir == 1) pos.X--;
	else if (dir == 2) pos.Y++;
	else if (dir == 3) pos.X++;
	else pos.Y--;
}

void GameObject::resetPos(short x, short y) {
	pos.X = x;
	pos.Y = y;
}

COORD GameObject::returnPos() const {
	COORD newPos = { pos.X, pos.Y };
	return newPos;
}