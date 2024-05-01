#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop();
	Bishop(Color _clr);
	char getSym() override;
	bool isLegalMove(int sr, int sc, int dr, int dc,Piece* _bs[][cols])override;
};
