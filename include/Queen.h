#include "Piece.h"
#include "Board.h"

class Queen : public Piece
{
public:
	Queen(char, int, int, string, Board*);
	~Queen();

	int isValidMove(Location start, Location end) override;
};