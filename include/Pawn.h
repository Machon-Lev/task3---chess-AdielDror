#include "Piece.h"
#include "Board.h"

class Pawn : public Piece
{
public:
	Pawn(char, int, int, string, Board*);
	~Pawn();

	int isValidMove(Location start, Location end) override;
};