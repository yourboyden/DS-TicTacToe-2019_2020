#pragma once
#include "Player.h"
#include "Board.h"

const char SINGLE_PLAYER_GAMEMODE[][STRING_CAP] = { "1", "single", "single-player", "singleplayer", "Single-player", "Singleplayer" };
const char MULTI_PLAYER_GAMEMODE[STRING_CAP][STRING_CAP] = { "2", "multi", "multi-player", "multiplayer", "Multi-player", "Multiplayer" };
const int GAMEMODE_OPTIONS = 6;

class Game
{
public:
	void beginGame();
private:
	Player player1, player2;
	Board board;

	void gamemode_single();
	void gamemode_multi();

	void copyData(const Game&);
	bool incorrectInputNum(const int) const;
	bool compareStrGamemode(const char*, const char[][STRING_CAP]) const;
	int determineGamemode(const char*) const;
	void writeInFile(const int);
};