#include "Queen.h"

Queen::Queen(char name, int row, int column, string player, Board* board) : Piece(name, row, column, player, board)
{

}

Queen::~Queen()
{
}

int Queen::isValidMove(Location start, Location end)
{
	return 0;
}