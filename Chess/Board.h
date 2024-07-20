#pragma once
#include <iostream>
#include <fstream>
#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "King.h"
#include "Queen.h"
#include <Windows.h>
using namespace std;

#define rows 8
#define cols 8

#define space char(-37)
#define boxRows 5
#define boxCols 9
#define white "\033[97;1m"
#define black "\033[30m"
#define bgblue "\033[44m"					//Colors bro 
#define bgdbrown "\033[48;2;139;69;19m"
#define bglbrown "\033[48;2;255;192;128m"
#define bgred "\033[41m"
#define red "\033[31m"
#define dbrown "\033[38;2;139;69;19m"
#define lbrown "\033[38;2;255;192;128m"
#define grey "\033[38;2;128;128;128m"
#define bggreen "\033[48;2;0;200;0m"
#define green "\033[38;2;0;200;0m"
#define bgorange "\033[48;5;208m"
#define orange "\033[38;5;208m"
#define dullwhite "\033[2; 37m"
#define blink "\033[5m"
#define resetbg "\033[40m"
#define reset "\033[0m"
#define HLSymbol char(249)   // Symbol to Show Highlighted Moves (Legal Moves)

class Board
{
private:
	

	void printBox(int r , int c,char _sym);
	void printPiece(int r, int c, char _sym);
	void printPawn(int r, int c);
	void printBishop(int r, int c);
	void printKnight(int r, int c);
	void printQueen(int r, int c);
	void printRook(int r, int c);
	void printKing(int r, int c);
	void printHighLightSymbol(int r, int c, char _sym);
	bool enemiesPiece(int turn, int ri, int ci);

public:
	Piece* bs[rows][cols];
	bool HPs[rows][cols];

	void moveToPos(int sr, int sc, int dr, int dc, bool castle);
	static void getRowColbyLeftClick(int& rpos, int& cpos);
	static void gotoRowCol(int rpos, int cpos);
	void init();
	void printBoard();
	void updateBoard(int sr, int sc, int dr, int dc,bool castle);
	void highLightBoard(bool HPs[][cols],int turn);
	void unHighLightBoard(int sr , int sc,bool HPs[][cols]);
	void printCheck(int kr, int kc, int turn);
	void unCheck(int kr, int kc,int turn);
	void printUndo();


	
};
