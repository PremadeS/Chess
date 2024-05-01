#pragma once
#include "Piece.h"
class Piece;
class Knight : public Piece
{
public:
	Knight();
	Knight(Color _clr);
	char getSym() override;
	bool isLegalMove(int sr, int sc, int dr, int dc, Piece* board[][cols])override;
};
