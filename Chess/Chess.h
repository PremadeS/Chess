#pragma once
//#include "Board.h"
#include "Game.h"
class Board;
class Chess
{
	Board board;
	bool HPs[rows][cols];
	bool isValidSelect(int sr, int sc, int turn);
	bool isValidPlacement(int dr, int dc, int turn);
	void changeTurn(int& turn);
	void highLightPos(int sr, int sc, int turn);
	bool isCheck(int turn);
	void findKing(int &kr , int &kc ,int turn);
	bool removesCheck(int sr, int sc, int dr, int dc, int turn);
	bool NoLegalMoves(int turn);
	bool checkPromotion(int dr, int dc);
	char getPromote();
	void promote(int dr , int dc, char sym,int turn);
	void clearPromoteMsg();
	bool isValidCastle(int sr,int sc,int dr,int dc,int turn);
	bool isFreeSpace(int sr, int sc, int dr, int dc);
	bool noCheckWhileCastle(int sr, int sc, int dr, int dc, int turn);
	void checkWin(int turn);
	bool undoClicked(int sr, int sc);
	void clearOtherMoves(ofstream& wtr, int undo);
	void printMsg(int turn);
	void printMyMsg();

public:
	int initial();
	void start(bool continueFromPrev);
	void replay();
};
