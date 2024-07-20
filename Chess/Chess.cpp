#include "Chess.h"
bool Chess::isValidSelect(int sr, int sc, int turn)
{
	if (sr >= rows || sc >= cols)
		return false;
	if (turn == board.bs[sr][sc]->getColor()&&board.bs[sr][sc]->getSym()!='-')
		return true;
	return false;
}
bool Chess::isValidPlacement(int dr, int dc, int turn)
{
	if (dr >= rows || dc >= cols)
		return false;
	if (board.bs[dr][dc]->getColor() == turn&&board.bs[dr][dc]->getSym()!='-')
		return false;
	return true;
}
void Chess::changeTurn(int &turn)
{
	turn == 0 ? turn = 1 : turn = 0;
}
void Chess::highLightPos(int sr, int sc, int turn)
{

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
			HPs[i][j] = (((isValidPlacement(i, j, turn) && board.bs[sr][sc]->isLegalMove(sr, sc, i, j, board.bs)&&removesCheck(sr,sc,i,j,turn))||(isValidCastle(sr,sc,i,j,turn)&&removesCheck(sr,sc,i,j,turn))));
	}
	HPs[sr][sc] = true; // Aesthetic :)

}
void Chess::findKing(int &kr , int &kc , int turn)
{
	bool found = false;
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if ((turn == 0 && board.bs[i][j]->getSym() == 'K')||(turn == 1 && board.bs[i][j]->getSym() == 'k'))
			{
				kr = i, kc = j;
				found = true;
				break;
			}
		}
		if (found)
			break;
	}
}
bool Chess::isCheck(int turn)
{
	int kr, kc;
	changeTurn(turn);
	findKing(kr, kc, turn);
	changeTurn(turn);
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (isValidSelect(i, j, turn) && board.bs[i][j]->isLegalMove(i, j, kr, kc, board.bs))
				return true;
		}
	}
	return false;
}

bool Chess::removesCheck(int sr, int sc, int dr, int dc,int turn)
{
	bool val = true;
	Piece* temp = board.bs[dr][dc];		//Temporarily make move :)
	board.bs[dr][dc] = board.bs[sr][sc];
	board.bs[sr][sc] = new Piece;
	changeTurn(turn);
	if (isCheck(turn))
		val = false;

	delete board.bs[sr][sc];
	board.bs[sr][sc] = board.bs[dr][dc];	// Reverse temp move :D
	board.bs[dr][dc] = temp;				
	
	return val;
}
bool Chess::NoLegalMoves(int turn)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (isValidSelect(i, j, turn))
			{
				for (int k = 0; k < rows; ++k)
				{
					for (int l = 0; l < cols; ++l)
					{
						if (isValidPlacement(k, l, turn) && board.bs[i][j]->isLegalMove(i, j, k, l, board.bs)&&removesCheck(i,j,k,l,turn))
							return false;
					}
				}
			}
		}
	}
	return true;
}
char Chess::getPromote()
{
	int ri=0, ci=0;
	Board::gotoRowCol(15, 90);
	cout << "Promote to?";
	Board::gotoRowCol(16, 90);
	cout << "Q   N   B   R";
	while (true)
	{
		Board::getRowColbyLeftClick(ri, ci);
		if (ri == 16 && ci == 90)
			return 'Q';
		if (ri == 16 && ci == 94)
			return 'N';
		if (ri == 16 && ci == 98)
			return 'B';
		if (ri == 16 && ci == 102)
			return 'R';
	}
	
}
void Chess::promote(int dr , int dc,char sym,int turn)
{
	delete board.bs[dr][dc];
	switch (sym)
	{
	case'Q':
		if (turn == 0)
			board.bs[dr][dc] = new Queen(White);
		else
			board.bs[dr][dc] = new Queen(Black);
		break;
	case'N':
		if (turn == 0)
			board.bs[dr][dc] = new Knight(White);
		else
			board.bs[dr][dc] = new Knight(Black);
		break;
	case'B':
		if (turn == 0)
			board.bs[dr][dc] = new Bishop(White);
		else
			board.bs[dr][dc] = new Bishop(Black);
		break;
	case'R':
		if (turn == 0)
			board.bs[dr][dc] = new Rook(White);
		else
			board.bs[dr][dc] = new Rook(Black);
		break;
	}
}
void Chess::clearPromoteMsg()
{
	Board::gotoRowCol(15, 90);
	cout << "           ";
	Board::gotoRowCol(16, 90);		//Aesthetic :)
	cout << "             ";
}
bool Chess::checkPromotion(int dr, int dc)
{
	if (board.bs[dr][dc]->getSym() == 'P' && dr == 0)	// Pawn Reached End
	{
		char sym;
		sym = getPromote();
		promote(dr, dc, sym, 0);	//White Pawn so turn == 0
		clearPromoteMsg();
		return true;
	}
	else if(board.bs[dr][dc]->getSym() == 'p' && dr == 7)
	{
		char sym;
		sym = getPromote();
		promote(dr, dc, sym, 1);	//Black Pawn so turn == 1
		clearPromoteMsg();
		return true;
	}
	return false;
}
bool Chess::isFreeSpace(int sr, int sc, int dr, int dc)
{
	int mini = min(sc,dc), maxi = max(sc, dc);
	if (sc > dc)
		mini -= 2;			// Long Castle
	else
		maxi++;				// Short Castle
	for (int i = mini+1; i < maxi; ++i)
	{
		if (board.bs[sr][i]->getSym() != '-')
			return false;
	}
	return true;
}

bool Chess::noCheckWhileCastle(int sr, int sc, int dr, int dc, int turn)
{
	int mini = min(sc, dc),maxi = max(sc,dc);
	changeTurn(turn);
	for (int i = mini + 1; i < maxi; ++i)
	{
		if (!removesCheck(sr, sc, dr, i, turn))
			return false;
	}
	return true;
}
bool Chess::isValidCastle(int sr,int sc,int dr,int dc,int turn)
{
	changeTurn(turn);
	if (isCheck(turn))
		return false;
	if (board.bs[sr][sc]->getSym() != 'k' && board.bs[sr][sc]->getSym() != 'K')
		return false;
	if (!board.bs[sr][sc]->getIsFirst())
		return false;
	if (sr != dr || abs(sc - dc) != 2)
		return false;
	if (sc < dc)
	{
		if ((board.bs[sr][dc + 1]->getSym() != 'r' && board.bs[sr][dc + 1]->getSym() != 'R') || !board.bs[sr][dc + 1]->getIsFirst())
			return false;
	}
	if (sc > dc)
	{
		if ((board.bs[sr][dc - 2]->getSym() != 'r' && board.bs[sr][dc - 2]->getSym() != 'R') || !board.bs[sr][dc - 2]->getIsFirst())
			return false;
	}
	return isFreeSpace(sr,sc,dr,dc)&&noCheckWhileCastle(sr,sc,dr,dc,turn);
}
void Chess::checkWin(int turn)
{
	Board::gotoRowCol(18, 100);
	int kr, kc;
	changeTurn(turn);
	if (isCheck(turn))
	{
		changeTurn(turn);
		findKing(kr, kc, turn);
		changeTurn(turn);
		board.printCheck(kr, kc, turn);
		Board::gotoRowCol(18, 98);

		if (turn == 0)
			cout << "CheckMate White Won";
		else
			cout << "CheckMate Black Won";
	}
	else
		cout << "StaleMate Draw";
	Board::gotoRowCol(39, 80);	// Aesthetic :)

}
bool Chess::undoClicked(int sr,int sc)
{
	return (sr >= 6 && sr <= 7 && sc >= 13 && sc <= 15);
}
void Chess::printMyMsg()
{
	Board::gotoRowCol(1, 110);
	cout << white<<"Developed By Baingain Studios"<<reset;
}
void Chess::printMsg(int turn)
{
	Board::gotoRowCol(18, 100);
	if (turn == 0)
		cout << "Whites Turn";
	else
		cout << "Blacks Turn";
}
int Chess::initial()
{
	printMyMsg();
	cout << blink<<green;
	cout << "\n\n\n\n\n";
	cout << R"(
					   _   _                  _____                      
					  | \ | |                / ____|                     
					  |  \| | _____      __ | |  __  __ _ _ __ ___   ___ 
					  | . ` |/ _ \ \ /\ / / | | |_ |/ _` | '_ ` _ \ / _ \
					  | |\  |  __/\ V  V /  | |__| | (_| | | | | | |  __/
					  |_| \_|\___| \_/\_/    \_____|\__,_|_| |_| |_|\___|
                                                    
)";
	cout<< orange<< endl << endl;
	cout << R"(
			     _____                                  _____                _                 
			    |  __ \                                |  __ \              (_)                
			    | |__) |___  ___ _   _ _ __ ___   ___  | |__) | __ _____   ___  ___  _   _ ___ 
			    |  _  // _ \/ __| | | | '_ ` _ \ / _ \ |  ___/ '__/ _ \ \ / / |/ _ \| | | / __|
			    | | \ \  __/\__ \ |_| | | | | | |  __/ | |   | | |  __/\ V /| | (_) | |_| \__ \
			    |_|  \_\___||___/\__,_|_| |_| |_|\___| |_|   |_|  \___| \_/ |_|\___/ \__,_|___/
)";


	cout <<red<< endl << endl;

	cout << R"(
						   _____            _             
						  |  __ \          | |            
						  | |__) |___ _ __ | | __ _ _   _ 
						  |  _  // _ \ '_ \| |/ _` | | | |
						  | | \ \  __/ |_) | | (_| | |_| |
						  |_|  \_\___| .__/|_|\__,_|\__, |
						             | |             __/ |
						             |_|            |___/ 
)";
	cout << reset;
	while (true)
	{
		int ri, ci;
		Board::getRowColbyLeftClick(ri, ci);
		if (ri >= 6 && ri <= 11 && ci >= 42 && ci <= 92)
			return 1;
		else if (ri >= 16 && ri <= 21 && ci >= 28 && ci <= 106)
			return 2;
		else if (ri >= 25 && ri <= 32 && ci >= 50 && ci <= 81)
			return 3;
	}
}
void Chess::start(bool continueFromPrev)
{
	printMyMsg();
	int undo = 0;
	int turn = 0;
	char end = '.';
	ifstream rdr("game.txt");
	Game game(&board);
	board.init();

	if (continueFromPrev)
	{
		rdr.seekg(0, ios::end);
		int size = rdr.tellg();
		if ((size / 80) % 2 == 0)
			turn = 1;

		rdr.seekg(-83, ios::end);
		game.load(rdr);

	}
	ofstream wtr("game.txt");
	board.printBoard();
	board.printUndo();
	game.save(wtr,end);
	int sr, sc, dr, dc;
	bool checked = false;
		do {
			printMsg(turn);
			do {
				do {
					do {
						do
						{
							rdr.seekg(ios::beg);
							if (NoLegalMoves(turn))
							{
								checkWin(turn);
								return;
							}
							if (isCheck(!turn))
							{
								int kr, kc;							//Prints Check :)
								findKing(kr, kc, turn);
								board.printCheck(kr, kc, !turn);
								checked = true;
							}
							else if(checked)
							{
								int kr, kc;							//UnChecks :)
								findKing(kr, kc, !turn);
								board.unCheck(kr, kc, !turn);
								checked = false;
							}

							Board::getRowColbyLeftClick(sr, sc);
							sr /= boxRows, sc /= boxCols;
							Board::gotoRowCol(39, 74);
							cout << sr << " " << sc << " ";
							if (undoClicked(sr, sc)&&undo > 0)
							{
								rdr.seekg((80 * (undo - 1)));		//Move 80*number of undos Bytes Ahead
								game.undo(rdr);
								board.printBoard();
								board.printUndo();
								changeTurn(turn);
								printMsg(turn);
								wtr.seekp(80 * undo, ios::beg);	//Clear the undoed moves so it doesnt show in replay :)
							
								--undo;
							}

						} while (!isValidSelect(sr, sc, turn));

						highLightPos(sr, sc, turn);		// HighLighting ..
						board.highLightBoard(HPs,turn);

						Board::getRowColbyLeftClick(dr, dc);
						dr /= boxRows, dc /= boxCols;

						board.unHighLightBoard(sr, sc, HPs);		// Reset ..

					} while (!isValidPlacement(dr, dc, turn));

				} while (!board.bs[sr][sc]->isLegalMove(sr, sc, dr, dc, board.bs)&&!isValidCastle(sr,sc,dr,dc,turn));
			} while (!removesCheck(sr, sc, dr, dc, turn));

			bool isMoveCastle = isValidCastle(sr, sc, dr, dc, turn);
			board.moveToPos(sr, sc, dr, dc,isMoveCastle);
			board.updateBoard(sr, sc, dr, dc, isMoveCastle);
			if (checkPromotion(dr, dc))
				board.updateBoard(dr, dc, dr, dc,0); //Only need to update one box so same parameters :)
			
			changeTurn(turn);
			++undo;
			game.save(wtr, end);

	} while (true);
	
}
void Chess::replay()
{
	board.init();
	char check;
	printMyMsg();
	int turn = 0;
	ifstream rdr("game.txt");
	Game game(&board);
	while (rdr)
	{
		if (!game.load(rdr))
			break;
		printMsg(turn);
		board.printBoard();
		if (isCheck(!turn))
		{
			int kr, kc;							//Prints Check :)
			findKing(kr, kc, turn);
			board.printCheck(kr, kc, !turn);
		}
		
		changeTurn(turn);
		Board::gotoRowCol(30, 80);
		if(rdr)
			system("pause");
	}
	Board::gotoRowCol(39, 80);	// Aesthetic :)

}