#pragma once
#include"Board.h"
#include"Piece.h"

class mouvementTemp {
	mouvementTemp();
	mouvementTemp(Board board);
	~mouvementTemp();

	void faireMovement();


private:
	Board board;
};
