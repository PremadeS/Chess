#pragma once
#include "Piece.h"
class Queen : public Piece
{
public:
	Queen();
	Queen(Color _clr);
	char getSym() override;
	bool isLegalMove(int sr, int sc, int dr, int dc, Piece* _bs[][cols])override;
};
