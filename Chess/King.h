#pragma once
#include "Piece.h"
class King : public Piece
{
	bool isFirst;
public:
	King();
	King(Color _clr);
	char getSym() override;
	bool isLegalMove(int sr, int sc, int dr, int dc,Piece* _bs[][cols]) override;
	void setIsFirst(bool val) override;
	bool getIsFirst() override;
};
