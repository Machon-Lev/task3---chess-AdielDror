#include "Pawn.h"

Pawn::Pawn(char name, int row, int column, string player, Board* board) : Piece(name, row, column, player, board)
{

}

Pawn::~Pawn()
{
}

int Pawn::isValidMove(Location start, Location end)
{
	// Calculate the change in position
	int row = end.row - start.row;
	int col = end.column - start.column;

	// White pawns can only move forward
	if (_player == "white" && row <= 0)
		return 21;

	// Black pawns can only move backward
	if (_player == "black" && row >= 0)
		return 21;

	// Pawns can only move one step forward (or two steps if it's their first move)
	if (abs(row) > 2 || abs(col) > 2) {
		return 21;
	}

	// Pawns can move one step diagonally forward to capture an opponent's piece
	if (abs(row) == 1 && abs(col) == 1 && _board->board[end.row][end.column] != nullptr) {
		return 42;
	}

	// Pawns can move one or two steps forward on their first move
	if ((start.row == 1 || start.row == 6) && start.column == end.column) {
		return 42;
	}

	// Pawns can move one step forward in the other steps
	if (start.column == end.column && abs(row) == 1 && _board->board[end.row][end.column] == nullptr) {
		return 42;
	}

	// Invalid move for the pawn
	return 21;
}