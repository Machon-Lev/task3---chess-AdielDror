#ifndef PIECE_H
#define PIECE_H
#pragma once
#include <string>
#include "Location.h"
//#include "Board.h"
using std::string;

class Board;

class Piece
{
protected:
	char name;
	int row;
	int column;
	string player;
	//Location location;
	Board* b_board;
public:
	Piece(char, int, int, string, Board*);
	~Piece();

	string getPlayer();
	char getName();
	void setLocation(int row, int column);

	inline virtual int isValidMove(Location start, Location end) = 0;

};
#endif

