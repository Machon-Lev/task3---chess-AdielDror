#include "Piece.h"
#include "Board.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Rook, public Bishop
{
public:
	Queen(char, int, int, string, Board*);
	~Queen();

	int isValidMove(Location start, Location end) override;
};