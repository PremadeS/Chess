#include "Piece.h"
Piece::Piece() :sym{ '-' }, clr{ White }{}
Piece::Piece(char _sym, Color _clr) :sym{ _sym }, clr{ _clr }{}
char Piece::getSym() { return sym; }
int Piece::getColor() { return clr; }
bool Piece::isHorizontal(int sr, int dr) { return sr == dr; }
bool Piece::isVertical(int sc, int dc) { return sc == dc; }
bool Piece::isDiagonal(int sr, int sc, int dr, int dc) 
{
	int dx = dr - sr;
	int dy = dc - sc;
	return abs(dx) == abs(dy);
}
bool Piece::isHPathClear(int sr,int sc,int dr, int dc, Piece* _bs[][cols])
{
	for (int i = min(sc, dc)+1; i < max(sc, dc); ++i)
	{
		if (_bs[sr][i]->getSym() != '-')
			return false;
	}
	return true;
}
bool Piece::isVPathClear(int sr, int sc, int dr, int dc, Piece* _bs[][cols])
{
	for (int i = min(sr, dr) + 1; i < max(sr, dr); ++i)
	{
		if (_bs[i][sc]->getSym() != '-')
			return false;
	}
	return true;
}
bool Piece::isDPathClear(int sr, int sc, int dr, int dc, Piece* _bs[][cols])
{
	int dx = abs(dr - sr);
	int rowDir = (dr > sr) ? 1 : -1;	//Decrease row if sr is bigger :)
	int colDir = (dc > sc) ? 1 : -1;	// ^^^^^ col

	for (int i = 1; i < dx; ++i) {
		if (_bs[sr + (i * rowDir)][sc + (i * colDir)]->getSym() != '-') {
			return false;
		}
	}

	return true;
}
bool Piece::isLegalMove(int sr, int sc, int dr, int dc, Piece* _bs[][cols]) { return false; }
void Piece::setIsFirst(bool val) {}
bool Piece::getIsFirst() { return false; }
