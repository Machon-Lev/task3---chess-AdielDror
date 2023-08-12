#include "Piece.h"
#include "Board.h"

class King : public Piece
{
public:
	King(char, int, int, string, Board*);
	~King();

	int isValidMove(Location start, Location end) override;
};
