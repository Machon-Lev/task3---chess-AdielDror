#include "Piece.h"
#include "Board.h"

class Knight : public Piece
{
public:
	Knight(char, int, int, string, Board*);
	~Knight();

	int isValidMove(Location start, Location end) override;

};
