#include "normalFunc.h"

void initEnemies(vector<GameObject>& v) {
	for (int i = 0; i < 8; i++) {
		if (i % 2 == 0)
			v.push_back(GameObject("[XUX]", (i + 2) * 3.5, 4));
		else
			v.push_back(GameObject("[XUX]", (i + 2.5) * 3.5, 6));
	}
}

void InputAndLogic(int& count, GameObject& player, vector<GameObject>& vEnemies, vector<GameObject>& vBullets, bool& spacePressed) {
	// player 움직임 - enemy와 부딪히지 않도록
	if (GetAsyncKeyState(VK_LEFT) & (1 << 15)) player.moveObject(1);
	if (GetAsyncKeyState(VK_DOWN) & (1 << 15)) player.moveObject(2);
	if (GetAsyncKeyState(VK_RIGHT) & (1 << 15)) player.moveObject(3);
	if (GetAsyncKeyState(VK_UP) & (1 << 15)) player.moveObject(4);

	if (ifOverlap(player, vEnemies)) {
		if (GetAsyncKeyState(VK_RIGHT) & (1 << 15)) player.moveObject(1);
		else if (GetAsyncKeyState(VK_UP) & (1 << 15)) player.moveObject(2);
		else if (GetAsyncKeyState(VK_LEFT) & (1 << 15)) player.moveObject(3);
		else if (GetAsyncKeyState(VK_DOWN) & (1 << 15)) player.moveObject(4);
		else if (player.returnPos().Y < 19) player.moveObject(2);
		else player.moveObject(4);
	}

	// 박스 밖으로 나가지 않도록
	if (player.returnPos().X >= SCR_WIDTH - 5) player.moveObject(1);
	if (player.returnPos().Y < 3) player.moveObject(2);
	if (player.returnPos().X < 1) player.moveObject(3);
	if (player.returnPos().Y >= SCR_HEIGHT - 1) player.moveObject(4);

	// space 눌러 bullet 발사
	if (GetAsyncKeyState(VK_SPACE)) {
		if (!spacePressed) {
			COORD newPos = player.returnPos();
			newPos.X += 2;
			newPos.Y--;
			vBullets.push_back(GameObject(newPos));
			spacePressed = true;
		}
	}
	else
		spacePressed = false;

	// bullets 움직이기 (점점 위로)
	for (auto& i : vBullets)
		i.moveObject(4);

	// bullets 맨 위로 올라가면 사라짐
	auto it = vBullets.begin();
	for (auto i : vBullets) {
		bool ifDelete = i.returnPos().Y < 2;
		if (ifDelete) {
			it = vBullets.erase(it);
		}
		else it++;
		if (it == vBullets.end())
			break;
	}

	// enemy 움직이기 - player보다 느리게
	if (count != 0) {
		if (count % 72 == 0) {
			for (auto& i : vEnemies)
				i.moveObject(2);
		}
		else if (count % 6 == 0 && count / 72 % 2 == 0) {
			for (auto& i : vEnemies)
				i.moveObject(3);
		}
		else if (count % 6 == 0 && count / 72 % 2 != 0) {
			for (auto& i : vEnemies)
				i.moveObject(1);
		}
	}
	count++;
}

bool ifOverlap(GameObject& player, vector<GameObject>& vEnemies) {
	for (auto i : vEnemies) {
		COORD playerPos = player.returnPos();
		COORD enemyPos = i.returnPos();
		if (playerPos.Y == enemyPos.Y) {
			for (int ip = 0; ip < 5; ip++) {
				if ((playerPos.X >= enemyPos.X && playerPos.X <= (enemyPos.X + ip))
					|| ((playerPos.X + 5) >= enemyPos.X && (playerPos.X + 5) <= (enemyPos.X + ip))) {
					return true;
				}
			}
		}
	}
	return false;
}

void getScore(int& score, vector<GameObject>& vBullets, vector<GameObject>& vEnemies) {
	int bulletIndex = 0;
	for (auto i : vBullets) {
		int enemyIndex = 0;
		for (auto j : vEnemies) {
			COORD iPos = i.returnPos();
			COORD jPos = j.returnPos();
			if (iPos.Y == jPos.Y) {
				if (iPos.X >= jPos.X && iPos.X < (jPos.X + 5)) {
					vector<GameObject>::iterator its = vEnemies.begin();
					advance(its, enemyIndex);
					its = vEnemies.erase(its);
					score++;
					vector<GameObject>::iterator itb = vBullets.begin();
					advance(itb, bulletIndex);
					itb = vBullets.erase(itb);
					break;
				}
			}
			enemyIndex++;
		}
		bulletIndex++;
	}
}

int ifEnd(vector<GameObject>& vEnemies) {
	if (vEnemies.empty()) {
		return 1;
	}
	for (auto& i : vEnemies) {
		if (i.returnPos().Y == 19)
			return 2;
	}
	return 0;
}

char ifContinue(int ifWin, int& score, int& count) {
	char ifCon;
	system("cls");

	if (ifWin == 1)
		cout << "YOU WIN!!" << endl;
	else
		cout << "YOU LOOSE!!" << endl;

	cout << "Score: " << score << endl;

	do {
		cout << "Play Again? (y/n): ";
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		cin >> ifCon;
	} while (ifCon != 'y' && ifCon != 'Y' && ifCon != 'n' && ifCon != 'N');

	score = count = 0;
	return ifCon;
}