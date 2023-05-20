#include "Queen.h"

Queen::Queen(char name, int row, int column, string player, Board* board) : Rook(name, row, column, player, board), Bishop(name, row, column, player, board), Piece(name, row, column, player, board)
{

}

Queen::~Queen()
{
}

int Queen::isValidMove(Location start, Location end)
{
	int code_rook = Rook::isValidMove(start,end);
	int code_bishop = Bishop::isValidMove(start, end);

	if (code_rook != code_bishop)
		return 42;
	return code_rook;
}