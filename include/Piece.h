#ifndef PIECE_H
#define PIECE_H
#pragma once

#include <string>
#include "Location.h"

using std::string;

class Board;

class Piece
{
protected:
	char _name;
	int _row;
	int _column;
	string _player;
	Board* _board;
public:
	Piece(char, int, int, string, Board*);
	virtual ~Piece() = default;

	string getPlayer() const;
	char getName() const;
	void setLocation(int row, int column);

	inline virtual int isValidMove(Location start, Location end) = 0;

};
#endif

