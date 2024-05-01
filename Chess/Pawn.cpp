#include "Pawn.h"
Pawn::Pawn() {}
Pawn::Pawn(Color _clr) : isFirst{true}
{
	if (_clr == Black)
		sym = 'p';
	else
		sym = 'P';
	clr = _clr;
}
char Pawn::getSym() { return sym; }
bool Pawn::isLegalMove(int sr, int sc, int dr, int dc, Piece* _bs[][cols])
{
	if (sym == 'p')
	{
		if (isFirst && isVertical(sc, dc) && dr - sr == 2 && _bs[dr][dc]->getSym() == '-')
			return true;
		else if (isVertical(sc, dc) && dr - sr == 1 && _bs[dr][dc]->getSym() == '-')
			return true;
		else if (isDiagonal(sr, sc, dr, dc) && dr - sr <= 1 && _bs[dr][dc]->getColor() == 0&&_bs[dr][dc]->getSym()!='-'&&sr<dr)
			return true;
		
	}
	else
	{
		if (isFirst && isVertical(sc, dc) && sr - dr == 2 && _bs[dr][dc]->getSym() == '-')
			return true;
		else if (isVertical(sc, dc) && sr - dr == 1 && _bs[dr][dc]->getSym() == '-')
			return true;
		else if (isDiagonal(sr, sc, dr, dc) && sr - dr <= 1 && _bs[dr][dc]->getColor() == 1 && _bs[dr][dc]->getSym() != '-' &&dr<sr)
			return true;
	}
	return false;
}
void Pawn::setIsFirst(bool val) { isFirst = val; }
bool Pawn::getIsFirst() { return isFirst; }