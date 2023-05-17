#include "Piece.h"


Piece::Piece(char name, int row, int column, string player,Board* board)
{
	this->name = name;
	this->row = row;
	this->column = column;
	this->player = player;
	this->b_board = board;
}

Piece::~Piece()
{
}

string Piece::getPlayer()
{
	return player;
}

char Piece::getName()
{
	return name;
}

void Piece::setLocation(int row, int column)
{
	this->row = row;
	this->column = column;
	
}

