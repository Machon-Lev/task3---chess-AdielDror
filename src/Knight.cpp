#include "Knight.h"

Knight::Knight(char name, int row, int column, string player, Board* board) : Piece(name, row, column, player, board)
{

}

Knight::~Knight()
{
}

int Knight::isValidMove(Location start, Location end)
{
	return 0;
}