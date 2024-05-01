#pragma once
#include "Piece.h"
//class Piece;
class Pawn : public Piece 
{
	bool isFirst;

public:
	Pawn();
	Pawn(Color _clr);
	char getSym() override;
	bool isLegalMove(int sr, int sc, int dr, int dc, Piece* _bs[][cols]);
	void setIsFirst(bool val) override;
	bool getIsFirst() override;
};
