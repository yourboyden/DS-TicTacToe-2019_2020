#include "Game.h"

void Game::beginGame()
{
	cout << "TIC - TAC - TOE\n";
	while (true)
	{
		char gamemode_str[STRING_CAP];
		int gamemode;
		cout << "Pick a game-mode:\n1) Single-player\n2) Multi-player\nYour input: ";
		cin.getline(gamemode_str, STRING_CAP);
		gamemode = determineGamemode(gamemode_str);				// 1 = singleplayer, 2 = multiplayer
		while (gamemode <= 0 || gamemode > 2)
		{
			cout << "Invalid input! Pick a game-mode:\n1) Single-player\n2) Multi-player\nYour input: ";
			cin.getline(gamemode_str, STRING_CAP);
			gamemode = determineGamemode(gamemode_str);
		}

		if (gamemode == 1)
			gamemode_single();
		else if (gamemode == 2)
			gamemode_multi();

		char willPlay_str[STRING_CAP];
		cout << "Another game? ";
		cin.ignore();
		cin.getline(willPlay_str, STRING_CAP);
		if(strcmp(willPlay_str, "yes") && strcmp(willPlay_str, "Yes") && strcmp(willPlay_str, "y") && strcmp(willPlay_str, "Y"))
			break;
		cout << endl;
		board.clearBoard();
	}
}

int Game::determineGamemode(const char* string) const
{
	if (compareStrGamemode(string, SINGLE_PLAYER_GAMEMODE))
		return 1;
	else if (compareStrGamemode(string, MULTI_PLAYER_GAMEMODE))
		return 2;
	return 0;
}

void Game::writeInFile(const int state)			// if state is 1, then P1 won against P2. if state is -1, then P2 won against P1. if state is 0, then it's a draw
{
	ofstream oResultsFile("Results.txt", ios::out | ios::app);
	if (!oResultsFile)
	{
		cerr << "Error! Results file couldn't be opened for writing.\n";
		return;
	}
	if (state == 1)
		oResultsFile << player1.getPlayerName() << " won against " << player2.getPlayerName() << endl;
	else if (state == - 1)
		oResultsFile << player2.getPlayerName() << " won against " << player1.getPlayerName() << endl;
	else if (state == 0)
		oResultsFile << player1.getPlayerName() << " and " << player2.getPlayerName() << " meet at a draw!\n";
	oResultsFile.close();
}

void Game::gamemode_single()
{
	char input_name[STRING_CAP];
	cout << "Input Player 1's name: ";
	cin.getline(input_name, STRING_CAP);
	player1.setPlayerName(input_name);
	player2.setPlayerName("Computer");
	cout << player1.getPlayerName() << " versus " << player2.getPlayerName() << endl << endl;
	char mark;

	cout << player1.getPlayerName() << ", select a symbol - X or O: ";
	cin >> mark;
	if (mark == 'x' || mark == 'X')
	{
		player1.setPlayerSymbol(mark);
		player2.setPlayerSymbol('O');
	}
	else if (mark == 'o' || mark == 'O')
	{
		player1.setPlayerSymbol(mark);
		player2.setPlayerSymbol('X');
	}
	else
	{
		cout << "Symbols have been automatically assigned due to " << player1.getPlayerName() << "'s inability to comply with simple rules.\n";
		player1.setPlayerSymbol('X');
		player2.setPlayerSymbol('O');
	}

	int counter = generateRandom();			// When counter is odd, it's Player 1's turn. When the counter is even, it's the AI's turn.
	while (true)
	{
		int x, y;
		cout << endl;
		board.printBoard();
		if (counter % 2 != 0)
		{
			cout << player1.getPlayerName() << "'s turn. Input position (x, y): ";
			cin >> x >> y;
			while (incorrectInputNum(x) || incorrectInputNum(y) || board.positionIsMarked(x, y))
			{
				cout << "Invalid input. Try again: ";
				cin >> x >> y;
			}
			board.setMark(x, y, player1.getPlayerSymbol());
		}
		else
		{
			cout << player2.getPlayerName() << "'s turn.";
			board.findBestMove(x, y, player2.getPlayerSymbol(), player1.getPlayerSymbol());
			board.setMark(x, y, player2.getPlayerSymbol());
		}

		if (board.winningBoard())
		{
			cout << endl;
			board.printBoard();
			if (counter % 2 != 0)
			{
				cout << player1.getPlayerName() << " won against " << player2.getPlayerName() << endl << endl;
				writeInFile(1);
				break;
			}

			else
			{
				cout << player2.getPlayerName() << " won against " << player1.getPlayerName() << endl << endl;
				writeInFile(-1);
				break;
			}
		}
		else if (board.isFullyMarked())
		{
			cout << endl;
			board.printBoard();
			cout << player1.getPlayerName() << " and " << player2.getPlayerName() << " meet at a draw!\n\n";
			writeInFile(0);
			break;
		}
		++counter;
	}
}

void Game::gamemode_multi()
{
	char input_name[STRING_CAP];
	cout << "Input Player 1's name: ";
	cin.getline(input_name, STRING_CAP);
	player1.setPlayerName(input_name);
	cout << "Input Player 2's name: ";
	cin.getline(input_name, STRING_CAP);
	player2.setPlayerName(input_name);
	cout << player1.getPlayerName() << " versus " << player2.getPlayerName() << endl << endl;
	char mark;

	cout << player1.getPlayerName() << ", select a symbol - X or O: ";
	cin >> mark;
	if (mark == 'x' || mark == 'X')
	{
		player1.setPlayerSymbol(mark);
		player2.setPlayerSymbol('O');
	}
	else if (mark == 'o' || mark == 'O')
	{
		player1.setPlayerSymbol(mark);
		player2.setPlayerSymbol('X');
	}
	else
	{
		cout << "Symbols have been automatically assigned due to " << player1.getPlayerName() << "'s inability to comply with simple rules.\n";
		player1.setPlayerSymbol('X');
		player2.setPlayerSymbol('O');
	}

	int counter = 1;			// When counter is odd, it's Player 1's turn. When the counter is even, it's Player 2's turn.
	while (true)
	{
		int x, y;
		cout << endl;
		board.printBoard();
		if (counter % 2 != 0)
			cout << player1.getPlayerName() << "'s turn. Input position (x, y): ";
		else
			cout << player2.getPlayerName() << "'s turn. Input position (x, y): ";
		cin >> x >> y;
		while (incorrectInputNum(x) || incorrectInputNum(y) || board.positionIsMarked(x, y))
		{
			cout << "Invalid input. Try again: ";
			cin >> x >> y;
		}
		if (counter % 2 != 0)
			board.setMark(x, y, player1.getPlayerSymbol());
		else
			board.setMark(x, y, player2.getPlayerSymbol());
		if (board.winningBoard())
		{
			cout << endl;
			board.printBoard();
			if (counter % 2 != 0)
			{
				cout << player1.getPlayerName() << " won against " << player2.getPlayerName() << endl << endl;
				writeInFile(1);
				break;
			}

			else
			{
				cout << player2.getPlayerName() << " won against " << player1.getPlayerName() << endl << endl;
				writeInFile(-1);
				break;
			}
		}
		else if (board.isFullyMarked())
		{
			cout << endl;
			board.printBoard();
			cout << player1.getPlayerName() << " and " << player2.getPlayerName() << " meet at a draw!\n\n";
			writeInFile(0);
			break;
		}
		++counter;
	}
}

void Game::copyData(const Game& other)
{
	player1 = other.player1;
	player2 = other.player2;
	board = board;
}

bool Game::incorrectInputNum(const int num) const
{
	return (num < 0 || num >= BOARD_SIZE);
}

bool Game::compareStrGamemode(const char* string, const char gamemode[][STRING_CAP]) const
{
	for (int i = 0; i < GAMEMODE_OPTIONS; ++i)
		if (!strcmp(string, gamemode[i]))
			return true;
	return false;
}
