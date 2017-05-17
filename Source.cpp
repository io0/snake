#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <deque>

const int W = 25;
const int H = 25;
int x = 1;
int y = 0;
char grid[W*H];

class Snake {
public:
	std::deque<int> sequence;
	int delay;
	bool alive;
	int getHead() {
		return sequence.front();
	}
	int getTail() {
		return sequence.back();
	}
}snek;

void initGrid()
{
	for (int i = 0; i < W; i++) {
		grid[i] = 'L';
		grid[i*W] = 'L';
		grid[i*W - 1 + W] = 'L';
		grid[W*H - 1 - i] = 'L';
	}

}

void initSnake() {
	int midpoint = W*H / 2;
	snek.sequence.push_front(midpoint);
	grid[midpoint] = 'O';
	snek.alive = true;
}

void move(int x, int y){
	int newHead = snek.getHead() + x + y*W;
	if (grid[newHead] == 'L' || grid[newHead] == 'O') snek.alive = false;
	else {
		if (grid[newHead] == 'X') snek.delay++;
		snek.sequence.push_front(newHead);
		grid[newHead] = 'O';
		if (snek.delay == 0) {
			grid[snek.getTail()] = ' ';
			snek.sequence.pop_back();
		}
		else {
			snek.delay--;
		}
	}
}

void changeDirection(char k) {
	switch (k) {

	case 'd':	//right
		if (x != -1) {
			x = 1;
			y = 0;
		}
		//std::cout << "right";
		break;

	case 'a':	//left
		if (x != 1) {
			x = -1;
			y = 0;
			//std::cout << "left";
		}
		break;
	case 'w':	//up
		if (y != 1) {
			x = 0;
			y = -1;
			//std::cout << "up";
		}
		break;

	case 's':	//down
		if (y != -1) {
			x = 0;
			y = 1;
		}
		//std::cout << "down";
		break;
	}
}
void printGrid()
{
	for (int i = 0; i < W; i++) {
		for (int j = 0; j < H; j++) {
			std::cout << grid[i*W + j] << " ";
		}
		std::cout << "\n";
	}
}

int main()
{
	initGrid();
	initSnake();
	while (snek.alive) {
		if (_kbhit()) {
			changeDirection(_getch());
		}

		move(x, y);
		system("cls");
		printGrid();
		std::cout << "X is " << x << " Y is " << y << std::endl;
		Sleep(500);
	}
	
}