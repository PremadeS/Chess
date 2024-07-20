#include "Bishop.h"
Bishop::Bishop(){}
Bishop::Bishop(Color _clr) 
{
	
	if (_clr == Black)
		sym = 'b';
	else
		sym = 'B';
	clr = _clr;
}
char Bishop::getSym() { return sym; }
bool Bishop::isLegalMove(int sr, int sc, int dr, int dc, Piece* _bs[][cols])
{
	return isDiagonal(sr, sc, dr, dc) && isDPathClear(sr, sc, dr, dc, _bs);
}