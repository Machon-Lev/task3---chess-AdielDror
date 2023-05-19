#include "Board.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include <iostream>


Board::Board()
{
	//// initialize pawns
	//for (int col = 0; col < SIZE_BOARD; ++col) {
	//	board[1][col] = new Pawn('P', 1, col, PLAYER_1, this);
	//	board[6][col] = new Pawn('p', 6, col, PLAYER_2, this);
	//}

	// Initialize White pieces
	board[0][0] = new Rook('R', 0, 0, PLAYER_1, this);
	board[0][7] = new Rook('R', 0, 7, PLAYER_1, this);
	board[0][4] = new King('K', 0, 4, PLAYER_1, this);
	//board[0][3] = new Queen('Q', 0, 3, PLAYER_1, this);
	board[0][5] = new Bishop('B', 0, 5, PLAYER_1, this);
	board[0][2] = new Bishop('B', 0, 2, PLAYER_1, this);
	//board[0][1] = new Knight('N', 0, 1, PLAYER_1, this);
	//board[0][4] = new Knight('N', 0, 6, PLAYER_1, this);


	// Initialize Black Pieces
	board[7][0] = new Rook('r', 7, 0, PLAYER_2, this);
	board[7][7] = new Rook('r', 7, 7, PLAYER_2, this);
	board[7][4] = new King('k', 7, 4, PLAYER_2, this);
	//board[7][3] = new Queen('q', 7, 3, PLAYER_2, this);
	board[7][2] = new Bishop('b', 7, 2, PLAYER_2, this);
	board[7][5] = new Bishop('b', 7, 5, PLAYER_2, this);
	//board[7][1] = new Knight('n', 7, 1, PLAYER_2, this);
	//board[7][6] = new Knight('n', 7, 6, PLAYER_2, this);
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
	int code = isValid(start, end);
	//// Check if there is a piece at the start position
	//if (board[start.row][start.column] == nullptr) {
	//	return 11;
	//}

	//// Check if the end position is occupied by a friendly piece
	//if (board[end.row][end.column] != nullptr && board[start.row][start.column]->getPlayer() == board[end.row][end.column]->getPlayer()) {
	//	return 13;
	//}

	//// Check if the player moves his piece
	//if (board[start.row][start.column]->getPlayer() != player) {
	//	return 12;
	//}
	if (!code) {
		code = board[start.row][start.column]->isValidMove(start, end);
	}

	//// Check if the move is valid for a rook
	//if (start.row == end.row) {
	//	// Moving horizontally
	//	int step = (end.column - start.column > 0) ? 1 : -1;
	//	for (int i = start.column + step; i != end.column; i += step) {
	//		if (board[start.row][i] != nullptr) {
	//			return 21;
	//		}
	//	}
	//	return 42;
	//}
	//else if (start.column == end.column) {
	//	// Moving vertically
	//	int step = (end.row - start.row > 0) ? 1 : -1;
	//	for (int i = start.row + step; i != end.row; i += step) {
	//		if (board[i][start.column] != nullptr) {
	//			return 21;
	//		}
	//	}
	//	return 42;
	//}

	//return 21;
	return code;
}


int Board::setPiece(string locations)
{
	Piece* current_piece{};
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
	if (isValid == 42)
	{
		current_piece = board[start.row][start.column];
		current_piece->setLocation(end.row, end.column);
		board[end.row][end.column] = current_piece;
		board[start.row][start.column] = nullptr;

	}
	string opponent = player == "white" ? "black" : "white";
	Location kingLocation = findKing(opponent);
	bool isCheck = isInCheck(player, kingLocation);

	if (isCheck)
	{
		isValid = 41;
	}

	Location currentKingLocation = findKing(player);
	bool checkmate = isInCheckForThisMove(player, currentKingLocation);
	if (checkmate)
	{
		isValid = 31;
		board[start.row][start.column] = current_piece;
		board[end.row][end.column] = nullptr;

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


int Board::isValid(Location start, Location end)
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
	return 0;
}

bool Board::isCheckmate(string player)
{
	Location king_loc = findKing(player);
	if (!isInCheck(player, king_loc))
		return false;

	// Check if king can move to any empty square that is not under attack
	for (int row = king_loc.row - 1; row <= king_loc.row + 1; row++) {
		for (int col = king_loc.column - 1; col <= king_loc.column + 1; col++) {
			if (row >= 0 && row < SIZE_BOARD && col >= 0 && col < SIZE_BOARD && (row != king_loc.row || col != king_loc.column)) {
				Location newLoc(row, col);
				if (isValidMove(king_loc, newLoc)) {
					Board newBoard = *this;
					newBoard.movePiece(king_loc, newLoc);
					if (!newBoard.isInCheck(player, newLoc)) {
						return false;
					}
				}
			}
		}
	}


	// Check if any friendly piece can capture the attacking piece
	std::vector<Location> attackingPieces = getAttackingPieces(player);
	for (Location loc : attackingPieces) {
		Piece* attackingPiece = board[loc.row][loc.column];
		for (int row = 0; row < SIZE_BOARD; row++) {
			for (int col = 0; col < SIZE_BOARD; col++) {
				if (board[row][col] != nullptr && board[row][col]->getPlayer() == player) {
					Location friendlyLoc(row, col);
					if (isValidMove(friendlyLoc, loc)) {
						Board newBoard = *this;
						newBoard.movePiece(friendlyLoc, loc);
						if (!newBoard.isInCheck(player, king_loc)) {
							return false;
						}
					}
				}
			}
		}
	}

	// Check if any friendly piece can block the attacking piece
	for (Location loc : attackingPieces) {
		Piece* attackingPiece = board[loc.row][loc.column];
		if (attackingPiece->getName() == 'r') {
			std::vector<Location> path = getPath(king_loc, loc);
			for (Location pathLoc : path) {
				for (int row = 0; row < SIZE_BOARD; row++) {
					for (int col = 0; col < SIZE_BOARD; col++) {
						if (board[row][col] != nullptr && board[row][col]->getPlayer() == player) {
							Location friendlyLoc(row, col);
							if (isValidMove(friendlyLoc, pathLoc)) {
								Board newBoard = *this;
								newBoard.movePiece(friendlyLoc, pathLoc);
								if (!newBoard.isInCheck(player, king_loc)) {
									return false;
								}
							}
						}
					}
				}
			}
		}
	}

	return true;

}

std::vector<Location> Board::getPath(Location start, Location end)
{
	std::vector<Location> path;

	int col = (end.column > start.column) ? 1 : ((end.column < start.column) ? -1 : 0);
	int row = (end.row > start.row) ? 1 : ((end.row < start.row) ? -1 : 0);

	int x = start.column + col;
	int y = start.row + row;

	while (x != end.column || y != end.row) {
		path.push_back(Location(y, x));
		x += col;
		y += row;
	}

	return path;
}

std::vector<Location> Board::getAttackingPieces(string player)
{
	std::vector<Location> attackingPieces;

	for (int row = 0; row < SIZE_BOARD; ++row)
	{
		for (int col = 0; col < SIZE_BOARD; ++col)
		{
			Piece* piece = board[row][col];
			if (piece != nullptr && piece->getPlayer() == player)
			{
				for (int i = 0; i < SIZE_BOARD; ++i)
				{
					for (int j = 0; j < SIZE_BOARD; ++j)
					{
						if (piece->isValidMove({ row,col }, { i,j }) == 0)
						{
							Piece* targetPiece = board[i][j];
							if (targetPiece != nullptr && targetPiece->getPlayer() != player)
							{
								attackingPieces.push_back({ row,col });
							}
						}
					}
				}
			}
		}
	}

	return attackingPieces;
}

void Board::movePiece(Location old_loc, Location new_loc)
{
	Piece* piece = board[old_loc.row][old_loc.column];
	board[old_loc.row][old_loc.column] = nullptr;
	board[new_loc.row][new_loc.column] = piece;
	piece->setLocation(new_loc.row, new_loc.column);
}

bool Board::isInCheck(string player, Location king_loc) const
{
	// Check if the king is under attack by any enemy piece

   // Check for knight attacks
	int row[] = { -2, -2, -1, -1, 1, 1, 2, 2 };
	int col[] = { -1, 1, -2, 2, -2, 2, -1, 1 };
	for (int i = 0; i < SIZE_BOARD; ++i) {
		int nx = king_loc.row + row[i];
		int ny = king_loc.column + col[i];
		if (nx >= 0 && nx < SIZE_BOARD && ny >= 0 && ny < SIZE_BOARD) {
			Piece* piece = board[nx][ny];
			if (piece != nullptr && piece->getPlayer() != player && (piece->getName() == 'n' || piece->getName() == 'N')) {
				return true; // King is under attack by a knight
			}
		}
	}

	// Check for attacks by rook or queen in horizontal and vertical directions
	for (int i = 0; i < 4; i++) {
		int dx = 0, dy = 0;
		if (i == 0) dx = 1;
		else if (i == 1) dx = -1;
		else if (i == 2) dy = 1;
		else if (i == 3) dy = -1;

		int x = king_loc.row + dx;
		int y = king_loc.column + dy;
		while (x >= 0 && x < SIZE_BOARD && y >= 0 && y < SIZE_BOARD) {
			Piece* piece = board[x][y];
			if (piece != nullptr) {
				if (piece->getPlayer() == player && (piece->getName() == 'r' || piece->getName() == 'R'|| piece->getName() == 'q' || piece->getName() == 'Q')) {
					return true; // King is under attack by a rook or queen
				}
				else {
					break;
				}
			}
			x += dx;
			y += dy;
		}
	}

	// Check for attacks by bishop or queen in diagonal directions
	int bishop_directions[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (int i = 0; i < 4; i++) {
		int dx = bishop_directions[i][0];
		int dy = bishop_directions[i][1];

		int x = king_loc.row + dx;
		int y = king_loc.column + dy;
		while (x >= 0 && x < SIZE_BOARD && y >= 0 && y < SIZE_BOARD) {
			Piece* piece = board[x][y];
			if (piece != nullptr) {
				if (piece->getPlayer() == player && (piece->getName() == 'b' || piece->getName() == 'B' || piece->getName() == 'q' || piece->getName() == 'Q')) {
					return true; // King is under attack by a bishop or queen
				}
				else {
					break;
				}
			}
			x += dx;
			y += dy;
		}
	}

	return false;
}


Location Board::findKing(string player) const
{
	// Iterate through the board and find the location of the king of the specified player
	for (int row = 0; row < SIZE_BOARD; ++row) {
		for (int col = 0; col < SIZE_BOARD; ++col) {
			Piece* piece = board[row][col];
			if (piece != nullptr && piece->getPlayer() == player && (piece->getName() == 'K' || piece->getName() == 'k'))
			{
				return { row,col };
			}
		}

	}
	// Return an invalid location if the king is not found
	return Location(-1, -1);
}

bool Board::isInCheckForThisMove(string player, Location king_loc) const
{
	// Check if the king is under attack by any enemy piece

   // Check for knight attacks
	int row[] = { -2, -2, -1, -1, 1, 1, 2, 2 };
	int col[] = { -1, 1, -2, 2, -2, 2, -1, 1 };
	for (int i = 0; i < SIZE_BOARD; ++i) {
		int nx = king_loc.row + row[i];
		int ny = king_loc.column + col[i];
		if (nx >= 0 && nx < SIZE_BOARD && ny >= 0 && ny < SIZE_BOARD) {
			Piece* piece = board[nx][ny];
			if (piece != nullptr && piece->getPlayer() != player && piece->getName() == 'n') {
				return true; // King is under attack by a knight
			}
		}
	}

	// Check for attacks by rook or queen in horizontal and vertical directions
	for (int i = 0; i < 4; i++) {
		int dx = 0, dy = 0;
		if (i == 0) dx = 1;
		else if (i == 1) dx = -1;
		else if (i == 2) dy = 1;
		else if (i == 3) dy = -1;

		int x = king_loc.row + dx;
		int y = king_loc.column + dy;
		while (x >= 0 && x < SIZE_BOARD && y >= 0 && y < SIZE_BOARD) {
			Piece* piece = board[x][y];
			if (piece != nullptr) {
				if (piece->getPlayer() != player && (piece->getName() == 'r' || piece->getName()=='R' || piece->getName() == 'Q' || piece->getName() == 'q')) {
					return true; // King is under attack by a rook or queen
				}
				else {
					break;
				}
			}
			x += dx;
			y += dy;
		}
	}

	// Check for attacks by bishop or queen in diagonal directions
	int bishop_directions[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (int i = 0; i < 4; i++) {
		int dx = bishop_directions[i][0];
		int dy = bishop_directions[i][1];

		int x = king_loc.row + dx;
		int y = king_loc.column + dy;
		while (x >= 0 && x < SIZE_BOARD && y >= 0 && y < SIZE_BOARD) {
			Piece* piece = board[x][y];
			if (piece != nullptr) {
				if (piece->getPlayer() != player && (piece->getName() == 'b' || piece->getName() == 'B' || piece->getName() == 'q' || piece->getName() == 'Q')) {
					return true; // King is under attack by a bishop or queen
				}
				else {
					break;
				}
			}
			x += dx;
			y += dy;
		}
	}

	return false;
}
