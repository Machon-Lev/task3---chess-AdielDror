#pragma once

#include "Piece.h"

const int SIZE_BOARD = 8;
const string PLAYER_1 = "white";
const string PLAYER_2 = "black";

struct Location;


class Board
{
	Piece* board[SIZE_BOARD][SIZE_BOARD] = { nullptr };
	string player = "white";
	bool turn = true;
public:
	Board();
	~Board();

	Location convertToValidLocation(string);
	int isValidMove(Location start, Location end);
	
	int setPiece(string locations);
	void turnPlayer();
	

};