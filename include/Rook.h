#include "Piece.h"
#include "Board.h"
class Rook : public Piece
{
public:
	Rook(char,int,int,string,Board*);
	~Rook();

	int isValidMove(Location start, Location end) override;
};