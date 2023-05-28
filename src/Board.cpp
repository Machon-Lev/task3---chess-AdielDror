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
	// initialize pawns
	for (int col = 0; col < SIZE_BOARD; ++col) {
		board[1][col] = new Pawn('P', 1, col, PLAYER_1, this);
		board[6][col] = new Pawn('p', 6, col, PLAYER_2, this);
	}

	// Initialize White pieces
	board[0][0] = new Rook('R', 0, 0, PLAYER_1, this);
	board[0][1] = new Knight('N', 0, 1, PLAYER_1, this);
	board[0][2] = new Bishop('B', 0, 2, PLAYER_1, this);
	board[0][3] = new Queen('Q', 0, 3, PLAYER_1, this);
	board[0][4] = new King('K', 0, 4, PLAYER_1, this);
	board[0][5] = new Bishop('B', 0, 5, PLAYER_1, this);
	board[0][6] = new Knight('N', 0, 6, PLAYER_1, this);
	board[0][7] = new Rook('R', 0, 7, PLAYER_1, this);


	// Initialize Black Pieces
	board[7][0] = new Rook('r', 7, 0, PLAYER_2, this);
	board[7][1] = new Knight('n', 7, 1, PLAYER_2, this);
	board[7][2] = new Bishop('b', 7, 2, PLAYER_2, this);
	board[7][3] = new Queen('q', 7, 3, PLAYER_2, this);
	board[7][4] = new King('k', 7, 4, PLAYER_2, this);
	board[7][5] = new Bishop('b', 7, 5, PLAYER_2, this);
	board[7][6] = new Knight('n', 7, 6, PLAYER_2, this);
	board[7][7] = new Rook('r', 7, 7, PLAYER_2, this);
}

Board::~Board()
{
}

/**
 * Converts a string representation of a location to a valid Location object.
 *
 * @param location The string representation of the location, e.g., "A1", "B3", etc.
 * @return A valid Location object if the input is valid, otherwise an invalid Location object with row and column set to INVALID_INDEX.
 */
Location Board::convertToValidLocation(string location) const
{
	Location validLocation;

	// Convert the first character of the input to uppercase
	location[0] = toupper(location[0]);

	// Check if the first character is a valid row letter
	if (location[0] >= 'A' && location[0] <= 'H')
	{
		// Convert the row letter to a row index
		validLocation.row = location[0] - 'A';

		// Check if the second character is a valid column digit
		if (location.length() == 2 && isdigit(location[1]))
		{
			// Convert the column digit to a column index
			validLocation.column = location[1] - '1';

			// Check if the location is within the board's bounds
			if (validLocation.row >= 0 && validLocation.row < SIZE_BOARD && validLocation.column >= 0 && validLocation.column < SIZE_BOARD)
			{
				return validLocation;
			}
		}
	}

	// Return an invalid location if the input is not valid
	return { INVALID_INDEX, INVALID_INDEX };
}

/**
 * Checks if a move from the start location to the end location is a valid move.
 *
 * @param start The starting location of the move.
 * @param end The ending location of the move.
 * @return 0 if the move is valid, a non-zero error code otherwise.
 *         If the move is valid, it also checks the piece-specific validity using Piece::isValidMove.
 */
int Board::isValidMove(Location start, Location end) const
{
	// Check if the move is valid based on general board rules
	int code = isValid(start, end);

	if (!code) {
		// Check if the specific piece allows the move
		code = board[start.row][start.column]->isValidMove(start, end);
	}

	return code;
}

/**
 * Sets the piece on the board based on the specified move.
 *
 * @param locations A string representing the source and destination locations of the move.
 *                  The string should be in the format "source destination".
 * @return          An integer representing the result of the move:
 *                  - VALID_MOVE: The move is valid and successfully executed.
 *                  - INVALID_MOVE: The move is invalid.
 *                  - KING_IN_CHECK: The move puts the player's opponent king in check.
 *                  - CHECKMATE: The move results in a checkmate.
 */
int Board::setPiece(string locations)
{
	Piece* current_piece = nullptr;
	Piece* taken_piece = nullptr;
	Location start;
	Location end;
	int isValid;

	string source;
	source = locations[0];
	source += locations[1];
	
	string destination;
	destination = locations[2];
	destination += locations[3];

	start = convertToValidLocation(source);
	end = convertToValidLocation(destination);
	
	// Check if the move is valid
	isValid = isValidMove(start, end);
	if (isValid != VALID_MOVE)
		return isValid;

	current_piece = board[start.row][start.column];
	current_piece->setLocation(end.row, end.column);

	// Check if there is a piece at the destination location
	if (board[end.row][end.column] != nullptr)
		taken_piece = board[end.row][end.column];

	board[end.row][end.column] = current_piece;
	board[start.row][start.column] = nullptr;

	// Check if the move puts the player's opponent king in check
	string opponent = (player == "white") ? "black" : "white";
	Location kingLocation = findKing(opponent);
	bool isCheck = isInCheck(player, kingLocation);
	if (isCheck)
		return KING_IN_CHECK;


	// Check if the move results in a checkmate 
	Location currentKingLocation = findKing(player);
	bool checkmate = isInCheckForThisMove(player, currentKingLocation);
	if (checkmate) {
		current_piece->setLocation(start.row, start.column);
		board[start.row][start.column] = current_piece;
		board[end.row][end.column] = taken_piece;
		return CHECKMATE;
	}

	return VALID_MOVE;

}

/**
 * Updates the player turn.
 * If it's currently white player's turn, it switches to black player's turn, and vice versa.
 */
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

/**
 * Checks if the move from the start location to the end location is valid based on general board rules.
 *
 * @param start The starting location of the move.
 * @param end The end location of the move.
 * @return 0 if the move is valid, a non-zero error code otherwise.
 *         Error codes:
 *         - 11: No piece exists at the start position.
 *         - 12: The player is not allowed to move the piece at the start position.
 *         - 13: The destination is occupied by a friendly piece.
 */
int Board::isValid(Location start, Location end) const
{

	// Check if there is a piece at the start position
	if (!board[start.row][start.column]) {
		return NO_PIECE_AT_START;
	}

	// Check if the end position is occupied by a friendly piece
	if (board[end.row][end.column] && board[start.row][start.column]->getPlayer() == board[end.row][end.column]->getPlayer()) {
		return DESTINATION_OCCUPIED_BY_FRIENDLY_PIECE;
	}

	// Check if the player moves his piece
	if (board[start.row][start.column]->getPlayer() != player) {
		return NOT_PLAYER_PIECE;
	}
	return 0;
}

/**
 * Checks if the specified player is in checkmate.
 *
 * @param player The player to check for checkmate.
 * @return True if the player is in checkmate, false otherwise.
 */
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

/**
 * Returns a vector of locations representing the path from the start location to the end location.
 *
 * @param start The starting location.
 * @param end The end location.
 * @return A vector of locations representing the path from the start to the end.
 */
std::vector<Location> Board::getPath(Location start, Location end) const
{
	std::vector<Location> path;

	int col_direction = (end.column > start.column) ? 1 : ((end.column < start.column) ? -1 : 0);
	int row_direction = (end.row > start.row) ? 1 : ((end.row < start.row) ? -1 : 0);

	int current_column = start.column + col_direction;
	int current_row = start.row + row_direction;

	while (current_column != end.column || current_row != end.row) {
		path.push_back(Location(current_row, current_column));
		current_column += col_direction;
		current_row += row_direction;
	}

	return path;
}

/**
 * Retrieves the locations of all attacking pieces for the specified player.
 *
 * @param player The player to check for attacking pieces.
 * @return A vector containing the locations of attacking pieces.
 */
std::vector<Location> Board::getAttackingPieces(string player) const
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

/**
 * Moves a piece from the old location to the new location on the board.
 *
 * @param old_loc The current location of the piece.
 * @param new_loc The new location where the piece will be moved.
 */
void Board::movePiece(Location old_loc, Location new_loc)
{
	Piece* piece = board[old_loc.row][old_loc.column];
	board[old_loc.row][old_loc.column] = nullptr;
	board[new_loc.row][new_loc.column] = piece;
	piece->setLocation(new_loc.row, new_loc.column);
}

/**
 * Checks if the specified player's king is in check at the given location.
 *
 * @param player   The player whose king is being checked for check.
 * @param king_loc The location of the player's king.
 * @return         `true` if the player's king is in check, `false` otherwise.
 */
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
			if (piece != nullptr && piece->getPlayer() == player && (piece->getName() == 'n' || piece->getName() == 'N')) {
				return true; // King is under attack by a knight
			}
		}
	}

	// Check for attacks by rook, queen or pawn in horizontal and vertical directions
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
				if ((piece->getPlayer() == player && (piece->getName() == 'r' || piece->getName() == 'R' || piece->getName() == 'q' || piece->getName() == 'Q'))
					|| (std::abs(x - king_loc.row) == 1 && std::abs(y - king_loc.column) == 1
						&& piece->getPlayer() == player && (piece->getName() == 'p' || piece->getName() == 'P'))) {
					return true; // King is under attack by a rook, queen or pawn
				}
				else {
					break;
				}
			}
			x += dx;
			y += dy;
		}
	}

	// Check for attacks by bishop, queen or pawn in diagonal directions
	int bishop_directions[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };
	for (int i = 0; i < 4; i++) {
		int dx = bishop_directions[i][0];
		int dy = bishop_directions[i][1];

		int x = king_loc.row + dx;
		int y = king_loc.column + dy;
		while (x >= 0 && x < SIZE_BOARD && y >= 0 && y < SIZE_BOARD) {
			Piece* piece = board[x][y];
			if (piece != nullptr) {
				if ((piece->getPlayer() == player && (piece->getName() == 'b' || piece->getName() == 'B' || piece->getName() == 'q' || piece->getName() == 'Q'))
					|| (std::abs(x - king_loc.row) == 1 && std::abs(y - king_loc.column) == 1
						&& piece->getPlayer() == player && (piece->getName() == 'p' || piece->getName() == 'P'))) {
					return true; // King is under attack by a bishop, queen or pawn
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

/**
 * Finds the location of the king belonging to the specified player.
 *
 * @param player The player whose king's location is to be found.
 * @return The location of the king as a `Location` object. If the king is not found, an invalid location is returned.
 */
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
	return Location(INVALID_INDEX, INVALID_INDEX);
}

/**
 * Checks if the specified player's king is in check after making a move.
 *
 * @param player   The player whose king is being checked for check.
 * @param king_loc The current location of the player's king.
 * @return         `true` if the player's king is in check after making a move, `false` otherwise.
 */
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
				if ((piece->getPlayer() != player && (piece->getName() == 'r' || piece->getName() == 'R' || piece->getName() == 'q' || piece->getName() == 'Q'))
					|| (std::abs(x - king_loc.row) == 1 && std::abs(y - king_loc.column) == 1
						&& piece->getPlayer() != player && (piece->getName() == 'p' || piece->getName() == 'P'))) {
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
				if ((piece->getPlayer() != player && (piece->getName() == 'b' || piece->getName() == 'B' || piece->getName() == 'q' || piece->getName() == 'Q'))
					|| (std::abs(x - king_loc.row) == 1 && std::abs(y - king_loc.column) == 1
						&& piece->getPlayer() != player && (piece->getName() == 'p' || piece->getName() == 'P'))) {
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
