#include "ScreenBuffer.h"

ScreenBuffer::ScreenBuffer() {
	system("cls");

	for (int y = 0; y < SCR_HEIGHT; y++) {
		for (int x = 0; x < SCR_WIDTH; x++) {
			if (x == 0 || x == SCR_WIDTH - 1) {
				front_buffer[y][x] = '|';
				back_buffer[y][x] = '|';
			}
			else if (y == 0 || y == 2 || y == SCR_HEIGHT - 1) {
				front_buffer[y][x] = '-';
				back_buffer[y][x] = '-';
			}
			else {
				front_buffer[y][x] = 9;
				back_buffer[y][x] = 9;
			}
		}
	}

	//Ŀ���� �Ⱥ��̵��� ����
	CONSOLE_CURSOR_INFO cur_info;
	cur_info.dwSize = 1;
	cur_info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);

	// ó�� ȭ�� �׸���
	for (int y = 0; y < SCR_HEIGHT; y++) {
		for (int x = 0; x < SCR_WIDTH; x++) {
			if (back_buffer[y][x] > 9)
				cout << back_buffer[y][x];
			else
				cout << ' ';
		}
		cout << endl;
	}
}

void ScreenBuffer::render() {
	// �ٲ� �κи� �ٽñ׸���
	for (int y = 0; y < SCR_HEIGHT; y++) {
		for (int x = 0; x < SCR_WIDTH; x++) {
			if (back_buffer[y][x] != front_buffer[y][x]) {
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ (short)x, (short)y });
				if (back_buffer[y][x] == 9)
					cout << ' ';
				else
					cout << back_buffer[y][x];
			}
		}
	}

	// front_buffer�� �ٲ� ���� ����, back_buffer �ʱ�ȭ
	for (int y = 0; y < SCR_HEIGHT; y++) {
		for (int x = 0; x < SCR_WIDTH; x++) {
			front_buffer[y][x] = back_buffer[y][x];
			back_buffer[y][x] = 9;
		}
	}
}

void ScreenBuffer::drawToBackBuffer(const int x, const int y, const char image) {
	back_buffer[y][x] = image;
}

void ScreenBuffer::drawToBackBuffer(const int x, const int y, int& score) {
	back_buffer[y][x] = score + 48;
}