#pragma once
#include <string>
//#include <Location.h>
using std::string;

class Piece
{
protected:
	char name;
	int row;
	int column;
	string player;
	//Location location;
public:
	Piece(char,int,int,string);
	~Piece();

	string getPlayer();
	void setLocation(int row, int column);
	
};

