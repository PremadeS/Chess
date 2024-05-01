#pragma once
#include "Piece.h"
class Rook : public Piece
{
	bool isFirst;
public:
	Rook();
	Rook(Color _clr);
	char getSym() override;
	bool isLegalMove(int sr, int sc, int dr, int dc, Piece* _bs[][cols]) override;
	void setIsFirst(bool val)override;
	bool getIsFirst()override;
};
