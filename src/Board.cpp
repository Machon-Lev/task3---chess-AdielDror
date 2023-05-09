#include "Board.h"
#include "Rook.h"

Board::Board()
{
	// Initialize White pieces
	Rook white_rook_1('R', 0, 0, PLAYER_1);
	Rook white_rook_2('R', 0, 7, PLAYER_1);

	// Initialize Black Pieces
	Rook black_rook_1('r', 7, 0,PLAYER_2);
	Rook black_rook_2('r', 7, 7, PLAYER_2);
}

Board::~Board()
{
}

void Board::setPiece(Piece* current_piece, int row, int column)
{
	board[row][column] = current_piece;
}
