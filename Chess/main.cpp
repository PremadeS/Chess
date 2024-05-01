/*
	+-----------------------+
	|	Terminal Size  :)	|
	|	Rows (Height) 40	|
	|	Cols (Width) 140	|
	+-----------------------+
*/
#include <fstream>
#include <iostream>
#include <windows.h>
#include "Chess.h"

using namespace std;

int main()
{
	int choice;
	Chess chess;
	choice = chess.initial();
	system("cls");
	if (choice == 1)
		chess.start(false);
	else if (choice == 2)
		chess.start(true);
	else
		chess.replay();
	return 0;

}