#include "Piece.h"



Piece::Piece(char name, int row, int column, string player)
{
	this->name = name;
	this->row = row;
	this->column = column;
	this->player = player;
}

Piece::~Piece()
{
}

string Piece::getPlayer()
{
	return player;
}

void Piece::setLocation(int row, int column)
{
	this->row = row;
	this->column = column;
	
}
