#include"Board.h"

#include"Queen.h"

#include"King.h"

#include"Rook.h"

#include<QMessageBox>

#include <algorithm>

#include "Case.h"



void checkmateMessage(Piece* piece)
{
	QMessageBox messageBox;
	QString winMessage = QString::fromStdString(piece->couleurToString());
	messageBox.information(0, winMessage + " won", "Checkmate");
	std::exit(0);
}

void stalemateMessage()
{
	QMessageBox messageBox;
	messageBox.information(0, "It's a tie", "Stalemate");
	std::exit(0);
}




pieceCouleur::Couleur switchColor(pieceCouleur::Couleur couleur) {

	if (static_cast<int>(couleur))
	{
		return pieceCouleur::Couleur::BLACK;
	}
	else
	{
		return pieceCouleur::Couleur::WHITE;
	}
}





void Board::colorBoard() {
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = Case(i, j);
		}
	}
}


void Board::putPieceOnBoard(std::unique_ptr<Piece> piece) {
	board[piece->getPosition().first][piece->getPosition().second].setPtrPiece(std::move(piece));
}


Board::Board(int configuration) {
	colorBoard();
	currentPlayer = pieceCouleur::Couleur::WHITE;
	switch (configuration)
	{
	case 1:
		initializeConfiguration1();
		break;
	case 2:
		initializeConfiguration2();
		break;
	case 3:
		initializeConfiguration3();
		break;
	default:
		initializeConfiguration1();
		break;
	}
	
	

}

void Board::initializeConfiguration1() {
	//Place Queens
	putPieceOnBoard(std::make_unique<Queen>(Queen(pieceCouleur::Couleur::WHITE, { 0, 3 })));
	putPieceOnBoard(std::make_unique<Queen>(Queen(pieceCouleur::Couleur::BLACK, { 7, 3 })));

	// Place kings
	try {
		putPieceOnBoard(std::make_unique<King>(King(pieceCouleur::Couleur::WHITE, { 0, 4 })));
		putPieceOnBoard(std::make_unique<King>(King(pieceCouleur::Couleur::BLACK, { 7, 4 })));
		//putPieceOnBoard(std::make_unique<King>(King(pieceCouleur::Couleur::BLACK, { 4, 4 })));

	}
	catch (kingInstanceError& run_error) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error when creating king", run_error.what());
		return;

	}
	//Place Rooks
	putPieceOnBoard(std::make_unique<Rook>(Rook(pieceCouleur::Couleur::WHITE, { 0, 0 })));
	putPieceOnBoard(std::make_unique<Rook>(Rook(pieceCouleur::Couleur::WHITE, { 0, 7 })));
	putPieceOnBoard(std::make_unique<Rook>(Rook(pieceCouleur::Couleur::BLACK, { 7, 0 })));
	putPieceOnBoard(std::make_unique<Rook>(Rook(pieceCouleur::Couleur::BLACK, { 7, 7 })));
}

void Board::initializeConfiguration2() {
	//Place Queens
	putPieceOnBoard(std::make_unique<Queen>(Queen(pieceCouleur::Couleur::WHITE, { 0, 1 })));
	putPieceOnBoard(std::make_unique<Queen>(Queen(pieceCouleur::Couleur::BLACK, { 7, 1 })));

	// Place kings
	try {
		putPieceOnBoard(std::make_unique<King>(King(pieceCouleur::Couleur::WHITE, { 0, 6 })));
		putPieceOnBoard(std::make_unique<King>(King(pieceCouleur::Couleur::BLACK, { 7, 6 })));
		//putPieceOnBoard(std::make_unique<King>(King(pieceCouleur::Couleur::BLACK, { 4, 4 })));

	}
	catch (kingInstanceError& run_error) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error when creating king", run_error.what());
		return;

	}
}

void Board::initializeConfiguration3() {

	putPieceOnBoard(std::make_unique<Rook>(Rook(pieceCouleur::Couleur::BLACK, { 0, 0 })));
	putPieceOnBoard(std::make_unique<Rook>(Rook(pieceCouleur::Couleur::WHITE, { 7, 7 })));

	try {
		putPieceOnBoard(std::make_unique<King>(King(pieceCouleur::Couleur::WHITE, { 3, 3 })));
		putPieceOnBoard(std::make_unique<King>(King(pieceCouleur::Couleur::BLACK, { 5, 5 })));
		//putPieceOnBoard(std::make_unique<King>(King(pieceCouleur::Couleur::BLACK, { 4, 4 })));

	}
	catch (kingInstanceError& run_error) {
		QMessageBox messageBox;
		messageBox.critical(0, "Error when creating king", run_error.what());
		return;

	}
}

bool Board::PathIsClear(const Position& start, const Position& end) {
	Position direction = { (end.first - start.first), (end.second - start.second) };
	Position unitDirection = { direction.first / pgcm(direction.first,direction.second),direction.second / pgcm(direction.first,direction.second) };
	Position movingPosition = start;
	int steps = std::max(abs(int(direction.first)), abs(int(direction.second)));

	for (int i = 0; i < steps - 1; i++)
	{
		movingPosition = { movingPosition.first + unitDirection.first,movingPosition.second + unitDirection.second };
		if (board[movingPosition.first][movingPosition.second].getPtrPiece())
		{
			return false;
		}
	}
	return true;
}




bool Board::pieceExiste(Position position) {
	return(board[position.first][position.second].getPtrPiece().get());
}




void Board::bougerPiece(Piece& piece, const Position& position) {
	Stalemate(&piece, position);
	if (bougerPieceValide(piece, position))
	{
		Stalemate(&piece, position);
		board[position.first][position.second].movePtrPiece(board[piece.getPosition().first][piece.getPosition().second].getPtrPiece());
		piece.setPosition(position.first, position.second);
		
	}
	Stalemate(&piece, position);
	if (kingIsInCheck(switchColor(piece.getCouleur())) && otherPieceCannotMove(piece.getCouleur())) {
		checkmateMessage(&piece);
	}
	
}

bool Board::bougerPieceValide(Piece& piece, const Position& position) {

	return(piece.deplacementValide(position) && PathIsClear(piece.getPosition(), position) && piece.getPosition() != position && !positionPutsKingInCheck(&piece, position)
		&& position != findKing(switchColor(piece.getCouleur()))->getPosition());
}

Piece* Board::getPiece(const Position& position) const {
	return board[position.first][position.second].getPtrPieceBrute();
}


void Board::changeCurrentPlayer() {
	currentPlayer = (currentPlayer == pieceCouleur::Couleur::WHITE) ? pieceCouleur::Couleur::BLACK : pieceCouleur::Couleur::WHITE;
}

bool Board::isCurrentPlayerPiece(int row, int col) const {
	if (getPiece({ row, col })) {
		return getPiece({ row, col })->getCouleur() == currentPlayer;
	}
	return false;
}

std::unique_ptr<Piece> Board::saveAndRemovePiece(const Position& position) {
	std::unique_ptr<Piece> savedPiece = nullptr;
	if (*board[position.first][position.second]) {
		savedPiece = std::move(board[position.first][position.second].getPtrPiece());
	}
	return savedPiece;
}


bool Board::positionPutsKingInCheck(Piece* piece, const Position& position) {
	Position pieceOriginalPosition = piece->getPosition();
	Piece* myKing = findKing(piece->getCouleur());
	std::unique_ptr<Piece> savedPiece = saveAndRemovePiece(position);
	movePiece(piece, position);
	bool kingIsInCheck = false;
	for (auto& row : board) {
		for (auto& case_ : row) {
			if ((*case_) != nullptr && (*case_)->getCouleur() != piece->getCouleur()) {
				if (myKing != nullptr)
				{
					if (((*case_)->deplacementValide(myKing->getPosition()) && PathIsClear((*case_)->getPosition(), myKing->getPosition()) && myKing->getCouleur() != (*case_)->getCouleur())) {
						kingIsInCheck = true;
					}
				}
			}
		}
	}


	movePiece(piece, pieceOriginalPosition);

	if (savedPiece) {
		putPieceOnBoard(std::move(savedPiece));
	}
	
	
	return kingIsInCheck;
}


bool Board::kingIsInCheck(pieceCouleur::Couleur couleur) {
	Piece* myKing = findKing(couleur);
	bool kingIsInCheck = false;
	for (auto& row : board) {
		for (auto& case_ : row) {
			if ((*case_) != nullptr && (*case_)->getCouleur() != couleur) {
				if (myKing != nullptr)
				{
					if (((*case_)->deplacementValide(myKing->getPosition()) && PathIsClear((*case_)->getPosition(), myKing->getPosition()) && myKing->getCouleur() != (*case_)->getCouleur())) {
						kingIsInCheck = true;
					}
				}
			}
		}
	}
	return kingIsInCheck;

}

bool Board::kingWasKilled(Piece* piece, const Position& position) {
	bool killedKing = false;
	Piece* piecess = (*board[position.first][position.second]);
	if ((*board[position.first][position.second])) {
		if ((*board[position.first][position.second])->getNom() == "King" && (*board[position.first][position.second])->getCouleur() != piece->getCouleur()) {
			killedKing=true;
		}
	}
	return killedKing;
}






bool Board::otherPieceCannotMove(pieceCouleur::Couleur couleur) {
	std::vector<Piece*> myPieces = findPieces(switchColor(couleur));

	for (auto&& myPiece : myPieces) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				Position targetPosition = { i, j };
				Piece* targetPiece = getPiece(targetPosition);

				if (targetPiece && targetPiece->getCouleur() != couleur) {
					continue;
				}

				if (bougerPieceValide(*myPiece, targetPosition)) {
					return false;
				}
			}
		}
	}
	return true;
}

std::vector<Piece*> Board::findPieces(pieceCouleur::Couleur couleur) {
	std::vector<Piece*> Pieces = {};
	for (auto& row : board) {
		for (auto& case_ : row) {
			if ((*case_) != nullptr) {
				if ((*case_)->getCouleur() == couleur) {
					Pieces.push_back(*case_);
				}
			}
		}
	}
	return Pieces;
}

Piece* Board::findKing(pieceCouleur::Couleur couleur) {
	for (auto& row : board) {
		for (auto& case_ : row) {
			if ((*case_) != nullptr) {
				if ((*case_)->getNom() == "King" && (*case_)->getCouleur() == couleur) {
					return (*case_);
				}
			}
		}
	}
	return nullptr;
}

void Board::movePiece(Piece* piece, const Position& position)
{
	board[position.first][position.second].movePtrPiece(board[piece->getPosition().first][piece->getPosition().second].getPtrPiece());
	piece->setPosition(position.first, position.second);

}


bool Board::areOnlyKingsLeft()
{
	std::vector<Piece*> blackPieces = findPieces(pieceCouleur::Couleur::BLACK);
	std::vector<Piece*> whitePieces = findPieces(pieceCouleur::Couleur::WHITE);
	if (blackPieces.size() == 1 && whitePieces.size() == 1) {
		if (blackPieces[0] == findKing(pieceCouleur::Couleur::BLACK) && whitePieces[0] == findKing(pieceCouleur::Couleur::WHITE)) {
			return true;
		}
	}
	return false;
}

	
void Board::Stalemate(Piece* piece, const Position& position) {
	if (areOnlyKingsLeft()) {
		stalemateMessage();
	}
	else if (otherPieceCannotMove(piece->getCouleur()) && !kingIsInCheck(switchColor(piece->getCouleur()))) {

		stalemateMessage();
	}
	else if (PieceCannotMove(piece->getCouleur()) && kingIsInCheck(piece->getCouleur()))
	{
		stalemateMessage();
	}

}