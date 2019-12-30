#pragma once
#include "HelpFunc.h"

class Player
{
public:
	Player(const char* = "", char = ' ');
	Player(const Player&);
	Player& operator=(const Player&);
	~Player();

	void setPlayerName(const char*);
	void setPlayerSymbol(const char);
	const char* getPlayerName() const;
	char getPlayerSymbol() const;
private:
	char* name;
	char sign;
	void copyData(const Player&);
	void deleteData();
};