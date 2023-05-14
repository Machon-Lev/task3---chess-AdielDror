#include "Board.h"
#include "Rook.h"
#include "Location.h"
#include <iostream>

Board::Board()
{
	// Initialize White pieces
	board[0][0] = new Rook('R', 0, 0, PLAYER_1);
	board[0][7]=new Rook('R', 0, 7, PLAYER_1);

	// Initialize Black Pieces
	board[7][0]=new Rook('r', 7, 0, PLAYER_2);
	board[7][7]=new Rook('r', 7, 7, PLAYER_2);
}

Board::~Board()
{
}


Location Board::convertToValidLocation(string location)
{
	Location loc;

	// Convert the first character of the input to uppercase
	location[0] = toupper(location[0]);

	// Check if the first character is a valid row letter
	if (location[0] >= 'A' && location[0] <= 'H')
	{
		// Convert the row letter to a row index
		loc.row = location[0] - 'A';

		// Check if the second character is a valid column digit
		if (location.length() == 2 && isdigit(location[1]))
		{
			// Convert the column digit to a column index
			loc.column = location[1] - '1';

			// Check if the location is within the board's bounds
			if (loc.row >= 0 && loc.row < SIZE_BOARD && loc.column >= 0 && loc.column < SIZE_BOARD)
			{
				return loc;
			}
		}
	}

	// Return an invalid location if the input is not valid
	return { -1, -1 };
}

int Board::isValidMove(Location start, Location end)
{
	
	// Check if there is a piece at the start position
	if (board[start.row][start.column] == nullptr) {
		return 11;
	}

	// Check if the end position is occupied by a friendly piece
	if (board[end.row][end.column] != nullptr && board[start.row][start.column]->getPlayer() == board[end.row][end.column]->getPlayer()) {
		return 13;
	}

	// Check if the player moves his piece
	if (board[start.row][start.column]->getPlayer() != player) {
		return 12;
	}
	// Check if the move is valid for a rook
	if (start.row == end.row) {
		// Moving horizontally
		int step = (end.column - start.column > 0) ? 1 : -1;
		for (int i = start.column + step; i != end.column; i += step) {
			if (board[start.row][i] != nullptr) {
				return 21;
			}
		}
		return 42;
	}
	else if (start.column == end.column) {
		// Moving vertically
		int step = (end.row - start.row > 0) ? 1 : -1;
		for (int i = start.row + step; i != end.row; i += step) {
			if (board[i][start.column] != nullptr) {
				return 21;
			}
		}
		return 42;
	}

	return 21;
}


int Board::setPiece(string locations)
{
	Piece* current_piece;
	Location end;
	string des;
	des = locations[2];
	des += locations[3];
	std::cout << des;
	Location start;
	int isValid;
	string src;
	src = locations[0];
	src += locations[1];
	
	start = convertToValidLocation(src);
	end = convertToValidLocation(des);
	isValid = isValidMove(start, end);
	if (isValid==41 || isValid == 42)
	{
		current_piece = board[start.row][start.column];
		current_piece->setLocation(end.row,end.column);
		board[end.row][end.column] = current_piece;
		board[start.row][start.column] = nullptr;
		
	}

	return isValid;
}

void Board::turnPlayer()
{
	if (turn) {
		player = "black";
		turn = false;
	}
	else
	{
		player = "white";
		turn = true;
	}
}
