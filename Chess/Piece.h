#pragma once
//#include "Board.h"
#include <iostream>
using namespace std;
#define rows 8
#define cols 8
enum Color{
	White,
	Black
};
class Piece
{
protected:
	Color clr;
	char sym;
	static bool isHorizontal(int sr, int dr);
	static bool isVertical(int sc, int dc);
	static bool isDiagonal(int sr,int sc,int dr, int dc);
	static bool isHPathClear(int sr,int sc, int dr,int dc,Piece* _bs[][cols]);
	static bool isVPathClear(int sr,int sc, int dr,int dc, Piece* _bs[][cols]);
	static bool isDPathClear(int sr, int sc, int dr, int dc, Piece* _bs[][cols]);
public:
	Piece();
	Piece(char _sym,Color _clr);
	virtual char getSym();
	virtual bool isLegalMove(int sr, int sc, int br, int bc,Piece* _bs[][cols]);
	int getColor();
	virtual void setIsFirst(bool val);
	virtual bool getIsFirst();
};
