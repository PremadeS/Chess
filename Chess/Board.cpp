#include "Board.h"

void Board::getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void Board::gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void Board::printPiece(int r , int c , char _sym)
{
	switch (_sym)
	{
	case 'p':
	case 'P':
		printPawn(r, c);
		break;
	case 'b':
	case 'B':
		printBishop(r, c);
		break;
	case 'n':
	case 'N':
		printKnight(r, c);
		break;
	case 'r':
	case 'R':
		printRook(r, c);
		break;
	case 'k':
	case 'K':
		printKing(r, c);
		break;
	case 'q':
	case 'Q':
		printQueen(r, c);
		break;
	case HLSymbol:
		printHighLightSymbol(r, c, _sym);
		break;
	}
	

}
void Board::printHighLightSymbol(int r, int c, char _sym)
{
	gotoRowCol(r + (boxRows) / 2, c + (boxCols / 2));
	cout << _sym;
}

void Board::printPawn(int r, int c)
{
	gotoRowCol(r + 1, c + 4);
	cout << space;
	gotoRowCol(r + 2, c + 3);
	cout << space<<space<<space;
	gotoRowCol(r + 3, c + 2);
	cout << space << space << space<<space<<space;
	
}	   //Print Shapes of Pieces
void Board::printBishop(int r, int c)
{
	gotoRowCol(r + 1, c + 2);
	cout << "| " <<char(209)<<" |";
	gotoRowCol(r + 2, c + 2);
	cout << space << space << space<<space<<space;
	gotoRowCol(r + 3, c + 3);
	cout << space << space << space;

}
void Board::printRook(int r, int c)
{
	gotoRowCol(r + 1, c + 2);
	cout << space <<" "<< space<<" " << space;
	gotoRowCol(r + 2, c + 2);
	cout << space << space << space << space << space;
	gotoRowCol(r + 3, c + 3);
	cout << space << space << space;
}
void Board::printKnight(int r, int c)
{
	gotoRowCol(r + 1, c + 1);
	cout << "/"<<space << space << space << space<<"\\";
	gotoRowCol(r + 2, c + 1);
	cout << space << "   " << space<<space;
	gotoRowCol(r + 3, c + 3);
	cout << space << space << space << space;


}

void Board::printKing(int r, int c)
{
	gotoRowCol(r + 1, c + 2);
	cout << space << " + " << space;
	gotoRowCol(r + 2, c + 3);
	cout << space << space << space;
	gotoRowCol(r + 3, c + 2);
	cout << space << space << space << space << space;

}
void Board::printQueen(int r, int c)
{
	gotoRowCol(r + 1, c + 2);
	cout << space << " " << space << " " << space;
	gotoRowCol(r + 2, c + 3);
	cout << space << space << space;
	gotoRowCol(r + 3, c + 2);
	cout << space << space << space << space << space;
}

bool Board::enemiesPiece(int turn,int ri,int ci)
{
	char sym = bs[ri][ci]->getSym();
	if (turn == 0 && sym >= 'a' && sym <= 'z')
		return true;
	else if (turn == 1 && sym >= 'A' && sym <= 'Z')
		return true;
	return false;
}
void Board::init()
{
	
	ifstream rdr("data.txt");
	char sym;
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			rdr >> sym;
			switch (sym)
			{ 
			case 'p':
				bs[i][j] = new Pawn(Black);
				break;
			case 'P':
				bs[i][j] = new Pawn(White);
				break;
			case 'b':
				bs[i][j] = new Bishop(Black);
				break; 
			case 'B':
				bs[i][j] = new Bishop(White );

					break;
			case 'n':
				bs[i][j] = new Knight(Black );

				break;
			case 'N':
				bs[i][j] = new Knight(White );
				break;
			case 'r':
				bs[i][j] = new Rook(Black );

				break;
			case 'R':
				bs[i][j] = new Rook(White );

				break;
			case 'k':
				bs[i][j] = new King(Black );

				break;
			case 'K':
				bs[i][j] = new King(White );

				break;
			case 'q':
				bs[i][j] = new Queen(Black );

				break;
			case 'Q':
				bs[i][j] = new Queen(White );

				break;
			case '-':
				bs[i][j] = new Piece('-', White );
			}

		}
	}
}
void Board::printBox(int r , int c,char _sym)
{
	if (_sym >= 'a' && _sym <= 'z')
		cout << black;
	else if (_sym != HLSymbol)
		cout << white;
	else
		cout << white <<blink;
	for (int i = 0; i < boxRows; ++i)
	{
		gotoRowCol(r+i, c);
		for (int j = 0; j < boxCols; ++j)
				cout << " ";

	}
	
	printPiece(r,c,_sym);
	gotoRowCol(39, 74); // Move the cursor away :D
	cout << reset;

}
void Board::printBoard()
{
	bool val = false;
	for (int i = 0; i < rows; ++i)
	{
		val = !val;
		for (int j = 0; j < cols; ++j)
		{
			if (val)
			{
				cout << bglbrown;
				val = !val;
			}
			else
			{
				cout << bgdbrown;
				val = !val;
			}
			printBox(i * boxRows, j * boxCols, bs[i][j]->getSym());
		}
	}
	cout << resetbg;
	

}
void Board::moveToPos(int sr, int sc, int dr, int dc,bool castle)
{
	if (bs[sr][sc]->getIsFirst())
		bs[sr][sc]->setIsFirst(false);		// First move has been made :)

	if (castle)
	{
		if (sc < dc)			// Short Castle 
		{

			delete bs[sr][sc + 1];
			bs[sr][sc + 1] = bs[sr][sc+3];

			delete bs[sr][sc + 2];
			bs[sr][sc + 2] = bs[sr][sc];

			bs[sr][sc] = new Piece;

			bs[sr][sc + 3] = new Piece;

		}
		else                   // Long Castle
		{
			delete bs[sr][sc - 1];
			bs[sr][sc - 1] = bs[sr][sc - 4];

			delete bs[sr][sc - 2];
			bs[sr][sc - 2] = bs[sr][sc];

			bs[sr][sc] = new Piece;
			
			delete bs[sr][sc - 3];
			bs[sr][sc - 3] = new Piece;
			
			bs[sr][sc - 4] = new Piece;

		}
		
	}
	else
	{
		delete bs[dr][dc];
		bs[dr][dc] = bs[sr][sc];
		bs[sr][sc] = new Piece;			//Creates blank space :)
	}
}
void Board::updateBoard(int sr,int sc,int dr,int dc,bool castle)
{
	if ((sr + sc) % 2 == 0)
		cout << bglbrown;
	else
		cout << bgdbrown;
	printBox(sr*boxRows, sc*boxCols, bs[sr][sc]->getSym());
	if ((dr + dc) % 2 == 0)
		cout << bglbrown;
	else
		cout << bgdbrown;
	printBox(dr*boxRows, dc*boxCols, bs[dr][dc]->getSym());
	if (castle)
	{
		if (sc < dc)		// Short castle
		{
			if ((sr + sc+1) % 2 == 0)
				cout << bglbrown;
			else
				cout << bgdbrown;
			printBox(sr * boxRows, (sc+1) * boxCols, bs[sr][sc+1]->getSym());
			if ((sr + sc+3) % 2 == 0)
				cout << bglbrown;
			else
				cout << bgdbrown;
			printBox(sr * boxRows, (sc+3) * boxCols, bs[sr][sc+3]->getSym());
		}
		else
		{
			if ((sr + sc - 1) % 2 == 0)
				cout << bglbrown;
			else
				cout << bgdbrown;
			printBox(sr * boxRows, (sc - 1) * boxCols, bs[sr][sc - 1]->getSym());
			if ((sr + sc - 3) % 2 == 0)
				cout << bglbrown;
			else
				cout << bgdbrown;
			printBox(sr * boxRows, (sc - 3) * boxCols, bs[sr][sc - 3]->getSym());
			if ((sr + sc - 4) % 2 == 0)
				cout << bglbrown;
			else
				cout << bgdbrown;
			printBox(sr * boxRows, (sc - 4) * boxCols, bs[sr][sc - 4]->getSym());
		}
	}
	cout << resetbg;

}
void Board::highLightBoard(bool HPs[][cols],int turn)	// Turn needed only for aesthetic purposes
{
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c)
		{
			if (bs[r][c]->getSym()!='-'&&HPs[r][c])
			{
				if (enemiesPiece(turn, r, c))
					cout << bgorange;			// Nice piece u got their buddy ;)
				else
					cout << bggreen;			// My Piece :D
					printBox(r * boxRows, c * boxCols, bs[r][c]->getSym());		
				
			}
			else if(HPs[r][c])
			{
			if ((r + c) % 2 == 0)
				cout << bglbrown;
			else
				cout << bgdbrown;
				printBox(r * boxRows, c * boxCols, HLSymbol);		// :O
			}
		}
	}
	cout << resetbg;
}
void Board::unHighLightBoard(int sr,int sc,bool HPs[][cols])
{
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < cols; ++c)
		{
			if (HPs[r][c])
			{
				if ((r + c) % 2 == 0)
					cout << bglbrown;
				else
					cout << bgdbrown;
				printBox(r * boxRows, c * boxCols, bs[r][c]->getSym());   //Back to Spaces :(
			}
		}
	}
}
void Board::printCheck(int kr, int kc,int turn)
{
	cout << bgred;
	if (turn == 0)
		printBox(kr * boxRows, kc * boxCols, 'k');
	else
		printBox(kr * boxRows, kc * boxCols, 'K');
	cout << resetbg;

}
void Board::unCheck(int kr, int kc, int turn)
{
	if ((kr + kc) % 2 == 0)
		cout << bglbrown;
	else
		cout << bgdbrown;
	if (turn == 0)
		printBox(kr * boxRows, kc * boxCols, 'K');	
	else
		printBox(kr * boxRows, kc * boxCols, 'k');
	cout << resetbg;

}
void Board::printUndo()
{
	cout << white << bgred;
	for (int i = 0; i < rows; ++i)
	{
		Board::gotoRowCol(30 + i, 122);
		for (int j = 0; j < cols * 2; ++j)
			cout << " ";
	}
	Board::gotoRowCol(30 + rows/2, 122 + cols - 2);
	cout << "UNDO";
	cout << reset << resetbg;
}

