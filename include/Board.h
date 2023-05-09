#pragma once

#include "Piece.h"


const int SIZE_BOARD = 8;
const string PLAYER_1 = "white";
const string PLAYER_2 = "black";


class Board
{
	Piece* board[SIZE_BOARD][SIZE_BOARD] = { nullptr };
public:
	Board();
	~Board();

	void setPiece(Piece*,int,int);
};