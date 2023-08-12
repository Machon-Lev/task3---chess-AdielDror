#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"
#include "Board.h"
class Rook : virtual public Piece
{
public:
	Rook(char,int,int,string,Board*);
	~Rook();

	int isValidMove(Location start, Location end) override;
};
#endif