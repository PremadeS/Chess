#pragma once
#include <fstream>
#include <string>
#include "Board.h"
using namespace std;
class Board;
class Game 
{
	Board* board;
public:
	Game();
	Game(Board* _board);
	void deleteBoard();
	void save(ofstream& wtr,char _end);
	void undo(ifstream &rdr);
	bool load(ifstream& rdr);
	
};
