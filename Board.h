#pragma once
#include "HelpFunc.h"

const int BOARD_SIZE = 3;

class Board
{
public:
	Board();
	void printBoard();
	void clearBoard();
	void setMark(const int, const int, const char);
	bool positionIsMarked(const int, const int) const;
	char getSymbolAtPosition(const int, const int) const;
	bool isFullyMarked() const;
	bool winningBoard() const;
	int evaluateAI(const char);
	void findBestMove(int&, int&, const char, const char);
private:
	char board[BOARD_SIZE][BOARD_SIZE];
	int minimax(int, int, int, const char, const char, const char);			// Minimax with Alpha-Beta pruning
};