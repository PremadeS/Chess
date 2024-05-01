#include "Knight.h"
Knight::Knight(){}
Knight::Knight(Color _clr) 
{
	if (_clr == Black)
		sym = 'n';
	else
		sym = 'N';
	clr = _clr;
}
char Knight::getSym() { return sym; }
bool Knight::isLegalMove(int sr, int sc, int dr, int dc, Piece* board[][cols])
{
	return (abs(sr - dr) == 2 && abs(sc - dc) == 1) || (abs(sr - dr) == 1 && abs(sc - dc) == 2);
}
