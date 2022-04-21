
#include <iostream>
#include <conio.h>
#include "windows.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

enum Status {
	OPEN,
	CLOSE,
};

enum Comand {
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	REGTH = 77,
	ESC = 27,
};

struct Sqr {
	int x = 1;
	int y = 1;
};

void createArr(int** elements, int const SIZE) {
	for (int i = 0; i < SIZE; i++) {
		*(elements + i) = new int[SIZE] {-1};
		for (int j = 0; j < SIZE; j++) {
			*(*(elements + i) + j) = OPEN;
		}
	}
}

void showArr(int** elements, int const SIZE, Sqr sqr) {
	char simvol = static_cast<char>((int) 30);
	
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (i == sqr.x && j == sqr.y) {
				cout << simvol;
				continue;
			}	
			switch (*(*(elements + i) + j)) {
				case OPEN:
					//cout << "***";
					cout << " ";
				break;
				case CLOSE:
					//cout << " | ";
					cout << "*";
				break;
			}			
		}
		cout << endl;
	}
}

void keyKOmand(bool& gameTrue, int& step) {
	// обрабатываем нажатую клавишу
	if (_kbhit()) {
		int key = _getch();
		switch (key) {
		case ESC:
			gameTrue = false;
			break;
		case UP:
			step = UP;
			break;
		case DOWN:
			step = DOWN;
			break;
		case LEFT:
			step = LEFT;
			break;
		case REGTH:
			step = REGTH;
			break;
		default:
			break;
		}
	}
};

void processKomand(int** elements, int const SIZE, int step, Sqr &sqr) {

	int stepX = 0;
	int stepY = 0;
	switch (step) {
		case UP:
			stepX = -1;
			stepY = 0;
		break;
		case DOWN:
			stepX = 1;
			stepY = 0;
		break;
		case LEFT:
			stepX = 0;
			stepY = -1;
		break;
		case REGTH:
			stepX = 0;
			stepY = 1;
		break;
	}
	if (((sqr.x + stepX) >= 0) && ((sqr.x + stepX) < SIZE) &&
		((sqr.y + stepY) >= 0) && ((sqr.y + stepY) < SIZE)) {
		if (elements[sqr.x + stepX][sqr.y + stepY] != CLOSE) {
			sqr.x = sqr.x + stepX;
			sqr.y = sqr.y + stepY;
		}
	}
}

void wallGame(int **walls, int const SIZE) {
	
	createArr(walls, SIZE);
	for (int j = 0; j < SIZE; j++) {
		walls[j][0] = CLOSE;
		walls[j][SIZE - 1] = CLOSE;
	}
	for (int j = 0; j < SIZE; j++) {
		walls[0][j] = CLOSE;
		walls[SIZE - 1][j] = CLOSE;
	}
	int vertikal = SIZE / 2;
	int horizont = SIZE / 2;
	for (int j = 0; j < SIZE; j++) {
		if (j > SIZE / 4) {
			walls[vertikal][j] = CLOSE;
		}
	}
	for (int j = 0; j < SIZE; j++) {
		if (j < SIZE / 4) {
			walls[j][horizont] = CLOSE;
		}		
	}
}

int main() {
	srand(time(0));
	int const SIZE = 25;
	
	// Рабочее поле
	int** elements = new int* [SIZE];
	
	// Точка квадрат
	Sqr sqr;

	createArr(elements, SIZE);
	wallGame(elements, SIZE);
	showArr(elements, SIZE, sqr);
		
	bool gameTrue = 1;
	int step = 0;
	while (gameTrue) {
		keyKOmand(gameTrue, step);
		//Sleep(10);
		if (step != 0) {
			processKomand(elements, SIZE, step, sqr);
			system("cls");
			showArr(elements, SIZE, sqr);
		}
		
		//showArr(elements, SIZE, eater);
		//step = 0;
	}

	return 0;
}

