#include "..\include\Rook.h"

Rook::Rook(char name, int row, int column, string player,Board* board) : Piece(name, row, column, player,board)
{

}

Rook::~Rook()
{
}

int Rook::isValidMove(Location start, Location end)
{
	
	//int code = isValid(start, end);
	//if (!code) {
// Check if the move is valid for a rook
	if (start.row == end.row) {
		// Moving horizontally
		int step = (end.column - start.column > 0) ? 1 : -1;
		for (int i = start.column + step; i != end.column; i += step) {
			if (b_board->board[start.row][i] != nullptr) {
				return 21;
			}
		}
		return 42;
	}
	else if (start.column == end.column) {
		// Moving vertically
		int step = (end.row - start.row > 0) ? 1 : -1;
		for (int i = start.row + step; i != end.row; i += step) {
			if (b_board->board[i][start.column] != nullptr) {
				return 21;
			}
		}
		return 42;
	}

	return 21;
	//}
	//return code;
	
}
