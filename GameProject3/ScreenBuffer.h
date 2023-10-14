#pragma once
#include <iostream>
#include <Windows.h>
#include <string>

#define SCR_WIDTH 55
#define SCR_HEIGHT 20

using namespace std;

class ScreenBuffer {
	char front_buffer[SCR_HEIGHT][SCR_WIDTH];
	char back_buffer[SCR_HEIGHT][SCR_WIDTH];

public:
	ScreenBuffer();
	void render();
	void drawToBackBuffer(const int x, const int y, const char image);
	void drawToBackBuffer(const int x, const int y, int& score);
};