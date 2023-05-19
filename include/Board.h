#ifndef BOARD_H
#define BOARD_H
#pragma once

#include "Piece.h"
#include <vector>

const int SIZE_BOARD = 8;
const string PLAYER_1 = "white";
const string PLAYER_2 = "black";

//struct Location;
//class Piece;

class Board
{
	
	string player = "white";
	bool turn = true;
public:
	Board();
	~Board();

	Location convertToValidLocation(string);
	int isValidMove(Location start, Location end);
	
	int setPiece(string locations);
	void turnPlayer();
	
	int isValid(Location start, Location end);
	Piece* board[SIZE_BOARD][SIZE_BOARD] = { nullptr };

	bool isCheckmate(string player);
	Location findKing(string player) const;
	bool isInCheck(string player, Location king_loc) const;
	void movePiece(Location old_loc, Location new_loc);
	std::vector<Location> getAttackingPieces(string player);
	std::vector<Location> getPath(Location start, Location end);
	bool isInCheckForThisMove(string player, Location king_loc) const;
};
#endif