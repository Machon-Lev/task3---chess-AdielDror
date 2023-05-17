#include "Bishop.h"

Bishop::Bishop(char name, int row, int column, string player, Board* board) : Piece(name, row, column, player, board)
{

}

Bishop::~Bishop()
{
}

int Bishop::isValidMove(Location start, Location end)
{
	return 0;
}