#pragma once
#include"Piece.h"

namespace caseCouleur {
	enum class Couleur {RED,BLACK,WHITE,EMPTY};
}

class Case {
public:
	Case();

	Piece* operator*();

	Case(short int chiffre, short int);

	std::unique_ptr<Piece>& getPtrPiece();

	void setPtrPiece(std::unique_ptr<Piece>&& piece);

	Piece* getPtrPieceBrute() const;

	void movePtrPiece(std::unique_ptr<Piece>& piece);

	void setCaseColor(caseCouleur::Couleur couleur_);

	Position getPosition();
	void movePtrPiece2(std::unique_ptr<Piece>& ptrPiece_);
private:
	Position position;
	caseCouleur::Couleur couleur;
	std::unique_ptr<Piece> ptrPiece;
};
