#include "King.h"

King::King(char name, int row, int column, string player, Board* board) : Piece(name, row, column, player, board)
{

}

King::~King()
{
}

int King::isValidMove(Location start, Location end)
{
    // Check if the move is within one square in any direction
    int row = abs(start.row - end.row);
    int column = abs(start.column - end.column);
    if ((row <= 1) && (column <= 1)) {
        return 42;
    }
    return 21;
}
