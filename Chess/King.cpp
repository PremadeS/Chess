#include "King.h"
King::King() :isFirst{ true } {}
King::King(Color _clr):isFirst{true}
{
	if (_clr == Black)
		sym = 'k';
	else
		sym = 'K';
	clr = _clr;
}
char King::getSym() { return sym; }
bool King::isLegalMove(int sr, int sc, int dr, int dc,Piece * _bs[][cols])
{
	return (((isHorizontal(sr, dr) && isHPathClear(sr, sc, dr, dc, _bs)) || (isVertical(sc, dc) && isVPathClear(sr, sc, dr, dc, _bs))) || (isDiagonal(sr, sc, dr, dc) && isDPathClear(sr, sc, dr, dc, _bs))) && abs(sr - dr) <= 1 && abs(sc - dc) <= 1;

}
void King::setIsFirst(bool val) { isFirst = val; }
bool King::getIsFirst() { return isFirst; }