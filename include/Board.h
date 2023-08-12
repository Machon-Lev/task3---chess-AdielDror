#ifndef BOARD_H
#define BOARD_H
#pragma once

#include "Piece.h"
#include <vector>

const int SIZE_BOARD = 8;
const string PLAYER_1 = "white";
const string PLAYER_2 = "black";
const int INVALID_INDEX = -1;
const int VALID_MOVE = 42;
const int KING_IN_CHECK = 41;
const int CHECKMATE = 31;
const int NO_PIECE_AT_START = 11;
const int DESTINATION_OCCUPIED_BY_FRIENDLY_PIECE = 13;
const int NOT_PLAYER_PIECE = 12;


class Board
{
	
	string player = "white";
	bool turn = true;

public:
	Piece* board[SIZE_BOARD][SIZE_BOARD] = { nullptr };
	Board();
	~Board();

	Location convertToValidLocation(string) const;
	int isValidMove(Location start, Location end) const;
	int setPiece(string locations);
	void turnPlayer();
	int isValid(Location start, Location end) const;
	bool isCheckmate(string player);
	Location findKing(string player) const;
	bool isInCheck(string player, Location king_loc) const;
	void movePiece(Location old_loc, Location new_loc) ;
	std::vector<Location> getAttackingPieces(string player) const;
	std::vector<Location> getPath(Location start, Location end) const;
	bool isInCheckForThisMove(string player, Location king_loc) const;
};
#endif