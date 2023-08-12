#include "Bishop.h"

Bishop::Bishop(char name, int row, int column, string player, Board* board) : Piece(name, row, column, player, board)
{

}

Bishop::~Bishop()
{
}

int Bishop::isValidMove(Location start, Location end)
{
	// Check if the start and end positions are different
	if (start.row == end.row && start.column == end.column)
	{
		return 21;
	}

	// Check if the move is diagonal
	int rowDistance = std::abs(end.row - start.row);
	int colDistance = std::abs(end.column - start.column);
	if (rowDistance != colDistance) {
		return 21;
	}

	return 42;

}