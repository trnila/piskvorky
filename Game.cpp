#include "Game.h"
#include <math.h>

Win::Win() {
	symbol = CellType::Empty;
	count = 0;
}

Game::Game(int count, int minRequired) {
	this->count = count;
	this->minRequired = minRequired;
	nextType = CellType::Circle;

	cells = new CellType*[count];
	for(int row = 0; row < count; row++) {
		cells[row] = new CellType[count];
	}

	reset();
};

Game::~Game() {
	for(int row = 0; row < count; row++) {
		delete[] cells[row];
	}
	delete[] cells;
}

void Game::reset() {
	win = Win();

	for(int row = 0; row < count; row++) {
		for(int col = 0; col < count; col++) {
			cells[row][col] = CellType::Empty;
		}
	}
}

bool Game::step(int row, int col) {
	if(get(row, col) == CellType::Empty) {
		cells[row][col] = nextType;

		nextType = nextType == CellType::Circle ? CellType::Cross : CellType::Circle;

		check();

		return true;
	}
	return false;
}

CellType Game::get(int row, int col) {
	return cells[row][col];
}

int Game::getCount() {
	return count;
}

int Game::setMinRequired(int minRequired) {
	this->minRequired = minRequired;
}

bool Game::isWin() {
	return win.symbol != CellType::Empty;
}

Win Game::getWin() {
	return win;
}

bool Game::check() {
	// check horizontal and vertical
	for(int row = 0; row < getCount(); row++) {
		Win vertical;
		vertical.type = WinType::Vertical;

		Win horizontal;
		horizontal.type = WinType::Horizontal;			

		for(int col = 0; col < getCount(); col++) {
			if(checkCell(row, col, vertical)) {
				win = vertical;
				return true;
			}

			if(checkCell(col, row, horizontal)) {
				win = horizontal;
				return true;
			}	
		}
	}

	// check diagonals
	int start = ceil(minRequired / sqrt(2));
	for(int i = start; i <= count; i++) {
		Win main1, main2, minor1, minor2;
		main1.type = main2.type = WinType::MainDiagonal;
		minor1.type = minor2.type = WinType::MinorDiagonal;

		for(int member = 0; member < i; member++) {
			int y = member;

			// main diagonal
			int x = count - i + member;
			if(checkCell(x, y, main1)) {
				win = main1;
				return true;
			}

			if(x != y && checkCell(y, x, main2)) {
				win = main2;
				return true;
			}

			// check minor diagonal
			x = i - member - 1;
			if(checkCell(x, y, minor1)) {
				win = minor1;
				return true;
			}

			x = count - member - 1;
			y = count - i + member;
			if(checkCell(x, y, minor2)) {
				win = minor2;
				return true;
			}
		}			
	}

	return false;
}

bool Game::checkCell(int x, int y, Win &record) {
	if(cells[x][y] == CellType::Empty) {
		record.count = 0;
	} else if(cells[x][y] == record.symbol) {
		record.count++;

		if(record.count >= minRequired) {
			return true;
		}
	} else {
		record.symbol = cells[x][y];
		record.count = 1;
		record.startRow = x;
		record.startCol = y;
	}

	return false;
}