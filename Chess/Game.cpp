#include "Game.h"
Game::Game(): board{nullptr}{}
Game::Game(Board* _board) { board = _board; }
void Game::save(ofstream&wtr,char _end)
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
			wtr << board->bs[i][j]->getSym();
		wtr << endl;				//Aesthetic
	}
	wtr << _end <<endl;
	wtr.seekp(-3, ios::end);
}

void Game::deleteBoard()
{
	for (int i = 0; i < rows; ++i)
	{
		for(int j = 0 ; j < cols;++j)		// Only the individual pieces are allocated dynamically :)
		delete board->bs[i][j];
	}
}
void Game::undo(ifstream& rdr)
{
	load(rdr);
}
bool Game::load(ifstream& rdr)
{
	deleteBoard();		// Free memory
	char sym;
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			rdr >> sym;
			if (sym == '.')
				return false;
			switch (sym)
			{
			case 'p':
				board->bs[i][j] = new Pawn(Black);
				if (i != 1)
					board->bs[i][j]->setIsFirst(false);
				break;
			case 'P':
				board->bs[i][j] = new Pawn(White);
				if (i != 6)
					board->bs[i][j]->setIsFirst(false);
				break;
			case 'b':
				board->bs[i][j] = new Bishop(Black);
				break;
			case 'B':
				board->bs[i][j] = new Bishop(White);

				break;
			case 'n':
				board->bs[i][j] = new Knight(Black);

				break;
			case 'N':
				board->bs[i][j] = new Knight(White);
				break;
			case 'r':
				board->bs[i][j] = new Rook(Black);

				break;
			case 'R':
				board->bs[i][j] = new Rook(White);

				break;
			case 'k':
				board->bs[i][j] = new King(Black);
				if (!(i == 0 && j == 4))
					board->bs[i][j]->setIsFirst(false);
				break;
			case 'K':
				board->bs[i][j] = new King(White);
				if (!(i == 7 && j == 4))
					board->bs[i][j]->setIsFirst(false);
				break;
			case 'q':
				board->bs[i][j] = new Queen(Black);

				break;
			case 'Q':
				board->bs[i][j] = new Queen(White);

				break;
			case '-':
				board->bs[i][j] = new Piece('-', White);
				break;
			}

		}
	}
	return true;
}
