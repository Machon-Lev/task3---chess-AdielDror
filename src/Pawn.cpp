#include "Pawn.h"

Pawn::Pawn(char name, int row, int column, string player, Board* board) : Piece(name, row, column, player, board)
{

}

Pawn::~Pawn()
{
}

int Pawn::isValidMove(Location start, Location end)
{
	return 0;
}