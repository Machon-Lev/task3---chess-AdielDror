#include "Piece.h"


Piece::Piece(char name, int row, int column, string player,Board* board)
{
	this->_name = name;
	this->_row = row;
	this->_column = column;
	this->_player = player;
	this->_board = board;
}


string Piece::getPlayer() const
{
	return _player;
}

char Piece::getName() const
{
	return _name;
}

void Piece::setLocation(int row, int column)
{
	this->_row = row;
	this->_column = column;
	
}

