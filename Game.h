#ifndef GAME_H
#define	GAME_H

enum class CellType {Empty, Cross, Circle};
enum class WinType {None, Vertical, Horizontal, MainDiagonal, MinorDiagonal};

struct Win {
	CellType symbol;
	int count;
	int startRow, startCol;
	WinType type;
	
	Win();
};

class Game {
public:	
	Game(int count, int minRequired);
	~Game();
	
	void reset();	
	bool step(int row, int col);	
	CellType get(int row, int col);	
	int getCount();	
	int setMinRequired(int minRequired);
	bool isWin();	
	Win getWin();
	CellType getNextType();
	
protected:
	bool check();	
	bool checkCell(int x, int y, Win &record);
	
private:
	/* count of rows/cols */
	int count;
	
	/* table of cells */
	CellType **cells;
	
	/* CellType in next step */
	CellType nextType;
	
	/* count of connected cells for win */
	int minRequired;
	
	/* How somebody win */
	Win win;
};

#endif	/* GAME_H */

