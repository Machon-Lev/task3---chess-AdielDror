#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"
#include "Board.h"

class Bishop : virtual public Piece
{
public:
	Bishop(char, int, int, string, Board*);
	~Bishop();

	int isValidMove(Location start, Location end) override;
};

#endif