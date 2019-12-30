#include "Player.h"

Player::Player(const char* name, char sign) : sign(sign)
{
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

Player::Player(const Player& other)
{
	copyData(other);
}

Player& Player::operator=(const Player& other)
{
	if (this != &other)
	{
		deleteData();
		copyData(other);
	}
	return *this;
}

Player::~Player()
{
	deleteData();
}

void Player::setPlayerName(const char* str)
{
	name = new char[strlen(str) + 1];
	strcpy(name, str);
}

void Player::setPlayerSymbol(const char c)
{
	sign = c;
}

const char* Player::getPlayerName() const
{
	return name;
}

char Player::getPlayerSymbol() const
{
	return sign;
}

void Player::copyData(const Player& other)
{
	sign = other.sign;
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
}

void Player::deleteData()
{
	delete[] name;
}
