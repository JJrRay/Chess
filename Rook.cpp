#include "Rook.h"

Rook::Rook() :Piece(pieceCouleur::Couleur::EMPTY, "Rook", nullPosition) {}


Rook::Rook(pieceCouleur::Couleur couleur_, Position position_) : Piece(couleur_, "Rook", position_) {}


bool Rook::deplacementValide(const Position& autrePosition) const
{
	return  isInBoard(autrePosition) && (Piece::position.first == autrePosition.first || Piece::position.second == autrePosition.second);
}

