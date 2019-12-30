#include "Board.h"

Board::Board()
{
	clearBoard();
}

void Board::printBoard()			// for 3 x 3 board:
{
	cout << endl << "     0   1   2";
	cout << endl << "   +---+---+---+";
	cout << endl << "0  | " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << " |";
	cout << endl << "   +---+---+---+";
	cout << endl << "1  | " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << " |";
	cout << endl << "   +---+---+---+";
	cout << endl << "2  | " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << " |";
	cout << endl << "   +---+---+---+" << endl;
}

void Board::clearBoard()
{
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			board[i][j] = ' ';
}

void Board::setMark(const int x, const int y, const char s)
{
	board[x][y] = s;
}

bool Board::positionIsMarked(const int x, const int y) const
{
	return (board[x][y] != ' ');
}

char Board::getSymbolAtPosition(const int x, const int y) const
{
	return board[x][y];
}

bool Board::isFullyMarked() const
{
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
			if (board[i][j] == ' ')
				return false;
	return true;
}

bool Board::winningBoard() const
{
	if (board[0][0] == board[0][1] && board[0][0] == board[0][2] && board[0][0] != ' ') return true;
	else if (board[1][0] == board[1][1] && board[1][0] == board[1][2] && board[1][0] != ' ') return true;
	else if (board[2][0] == board[2][1] && board[2][0] == board[2][2] && board[2][0] != ' ') return true;
	else if (board[0][0] == board[1][0] && board[0][0] == board[2][0] && board[0][0] != ' ') return true;
	else if (board[0][1] == board[1][1] && board[0][1] == board[2][1] && board[0][1] != ' ') return true;
	else if (board[0][2] == board[1][2] && board[0][2] == board[2][2] && board[0][2] != ' ') return true;
	else if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ') return true;
	else if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ') return true;
	else return false;
}

int Board::evaluateAI(const char mark)
{
	for (int i = 0; i < BOARD_SIZE; ++i)
		if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != ' ')
		{
			if (board[i][0] == mark)
				return 10;
			else return -10;
		}

	for (int j = 0; j < BOARD_SIZE; ++j)
		if (board[0][j] == board[1][j] && board[0][j] == board[2][j] && board[0][j] != ' ')
		{
			if (board[0][j] == mark)
				return 10;
			else return -10;
		}

	if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ')
	{
		if (board[0][0] == mark)
			return 10;
		else return -10;
	}

	else if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ')
	{
		if (board[0][2] == mark)
			return 10;
		else return -10;
	}

	return 0;
}

void Board::findBestMove(int& x, int& y, const char mark_ai, const char mark_player)
{
	int best_x = -1, best_y = -1, bestValue = NEG_CAP;
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			if (!positionIsMarked(i, j))
			{
				setMark(i, j, mark_ai);
				int currValue = minimax(0, NEG_CAP, POS_CAP, mark_player, mark_ai, mark_player);
				setMark(i, j, ' ');
				if (currValue > bestValue)
				{
					best_x = i;
					best_y = j;
					bestValue = currValue;
				}
			}
		}
	x = best_x;
	y = best_y;
}

int Board::minimax(int depth, int alpha, int beta, const char mark, const char mark_ai, const char mark_player)
{
	int score = evaluateAI(mark_ai);
	if (score == 10 || score == -10) return score - depth;
	else if (isFullyMarked()) return 0 - depth;

	if (mark == mark_ai)
	{
		int best = NEG_CAP;
		for (int i = 0; i < BOARD_SIZE; ++i)
		{
			for (int j = 0; j < BOARD_SIZE; ++j)
			{
				if (!positionIsMarked(i, j))
				{
					setMark(i, j, mark);
					best = max(best, minimax(depth + 1, alpha, beta, mark_player, mark_ai, mark_player));
					alpha = max(alpha, best);
					setMark(i, j, ' ');
					if (beta <= alpha) break;
				}
			}
			if (beta <= alpha) break;
		}
		return best;
	}

	else		// mark == mark player
	{
		int best = POS_CAP;
		for (int i = 0; i < BOARD_SIZE; ++i)
		{
			for (int j = 0; j < BOARD_SIZE; ++j)
			{
				if (!positionIsMarked(i, j))
				{
					setMark(i, j, mark);
					best = min(best, minimax(depth + 1, alpha, beta, mark_ai, mark_ai, mark_player));
					beta = min(beta, best);
					setMark(i, j, ' ');

					if (beta <= alpha) break;
				}
			}
			if (beta <= alpha) break;
		}
		return best;
	}
}
