#include "Piece.h"
#include "Board.h"

class Bishop : public Piece
{
public:
	Bishop(char, int, int, string, Board*);
	~Bishop();

	int isValidMove(Location start, Location end) override;
};