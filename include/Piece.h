#include <string>
using std::string;

class Piece
{
protected:
	char name;
	int row;
	int column;
	string player;
public:
	Piece(char,int,int,string);
	~Piece();

};

