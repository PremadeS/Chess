#include "Queen.h"
Queen::Queen() {}
Queen::Queen(Color _clr)
{
	if (_clr == Black)
		sym = 'q';
	else
		sym = 'Q';
	clr = _clr;
}
char Queen::getSym() { return sym; }
bool Queen::isLegalMove(int sr,int sc,int dr,int dc,Piece* _bs[][cols]) 
{
	return (isHorizontal(sr, dr) && isHPathClear(sr, sc, dr, dc, _bs)) ||( isVertical(sc, dc) && isVPathClear(sr, sc, dr, dc, _bs)) || (isDiagonal(sr, sc, dr, dc) && isDPathClear(sr, sc, dr, dc, _bs));
}