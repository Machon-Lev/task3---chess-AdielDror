#include "Knight.h"

Knight::Knight(char name, int row, int column, string player, Board* board) : Piece(name, row, column, player, board)
{

}

Knight::~Knight()
{
}

int Knight::isValidMove(Location start, Location end)
{
	int rowDifference = abs(start.row - end.row);
	int colDifference = abs(start.column - end.column);

	if ((rowDifference == 1 && colDifference == 2) || (rowDifference == 2 && colDifference == 1))
		return 42;

	return 21;
}