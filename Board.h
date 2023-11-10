#pragma once
#include<vector>
#include"Case.h"
#include "gsl/span" 
#include"Piece.h"


class Board {
public:
	void colorBoard();
	bool pieceExiste(Position position); //v�rifie si une pi�ce est d�j� sur la case

	Board(int configuration);
	bool PathIsClear(const Position& start, const Position& end); //v�rifier si case libre 
	Board(const std::vector<std::unique_ptr<Piece>>& pieces);
	void putPieceOnBoard(std::unique_ptr<Piece> piece); //initialise position pi�ces sur le board
	void bougerPiece(Piece &piece,const Position &position); // d�place les pi�ces sur le board, utilise pieceExiste et PathIsClear
	Piece* getPiece(const Position& position) const;
	pieceCouleur::Couleur getCurrentPlayer() const { return currentPlayer; }

	void changeCurrentPlayer();
	bool isCurrentPlayerPiece(int col, int row) const;
	//bool checkIsTreated(Piece* piece, const Position& position);
	void Stalemate(Piece *piece, const Position& position);

	Piece* findKing(pieceCouleur::Couleur couleur);

	bool kingIsInCheck(pieceCouleur::Couleur couleur);

	bool kingWasKilled(Piece* piece, const Position& position);
	
	bool otherPieceCannotMove(pieceCouleur::Couleur couleur);

	std::vector<Piece*> findPieces(pieceCouleur::Couleur couleur);

	bool bougerPieceValide(Piece& piece, const Position& position);

	bool positionPutsKingInCheck(Piece* piece, const Position& position);

	void movePiece(Piece* piece, const Position& position);

	bool PieceCannotMove(pieceCouleur::Couleur couleur);

	std::unique_ptr<Piece> saveAndRemovePiece(const Position& position);

	bool areOnlyKingsLeft();


	void initializeConfiguration1();
	void initializeConfiguration2();
	void initializeConfiguration3();


private:

	pieceCouleur::Couleur currentPlayer;
	Case board[8][8];
};

extern pieceCouleur::Couleur switchColor(pieceCouleur::Couleur couleur);