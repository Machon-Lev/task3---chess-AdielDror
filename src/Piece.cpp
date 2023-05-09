#include "..\include\Piece.h"



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
