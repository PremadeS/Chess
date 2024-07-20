#include "Rook.h"
Rook::Rook() :isFirst{ true } {}
Rook::Rook(Color _clr) : isFirst {true}
{
	if (_clr == Black)
		sym = 'r';
	else
		sym = 'R';
	clr = _clr;
}
char Rook::getSym() { return sym; }
bool Rook::isLegalMove(int sr, int sc, int dr, int dc, Piece* _bs[][cols])
{
	return isHorizontal(sr, dr) && isHPathClear(sr, sc, dr, dc, _bs)|| isVertical(sc, dc) && isVPathClear(sr, sc, dr, dc, _bs);
}
void Rook::setIsFirst(bool val) { isFirst = val; }
bool Rook::getIsFirst() { return isFirst; }