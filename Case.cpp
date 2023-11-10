#include "Case.h"


Case::Case() :ptrPiece(nullptr), couleur(caseCouleur::Couleur::EMPTY), position(nullPosition) {}


Case::Case(short int row, short int col) :
	ptrPiece(nullptr),
	position({ row,col }),
	couleur(isEven(position.first + position.second) ? caseCouleur::Couleur::WHITE : caseCouleur::Couleur::BLACK)
{}



void Case::setPtrPiece(std::unique_ptr<Piece>&& piece)
{
	ptrPiece = std::move(piece);
}

Piece* Case::operator*()
{
	return getPtrPieceBrute();
}

void Case::movePtrPiece(std::unique_ptr<Piece>& ptrPiece_) {
	ptrPiece = std::move(ptrPiece_);
	ptrPiece_ = nullptr;
}

void Case::movePtrPiece2(std::unique_ptr<Piece>& ptrPiece_) {
	ptrPiece = std::move(ptrPiece_);
	ptrPiece_ = nullptr;
}


std::unique_ptr<Piece>& Case::getPtrPiece() {
	return ptrPiece;
}


void Case::setCaseColor(caseCouleur::Couleur couleur_)
{
	couleur = couleur_;
}

Piece* Case::getPtrPieceBrute() const {
	return ptrPiece.get();
}

Position Case::getPosition() { return position; }
