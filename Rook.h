#pragma once
#include "Piece.h"
class Rook:public Piece {
public:
	Rook();
	Rook(pieceCouleur::Couleur couleur_, Position position_);
	bool deplacementValide(const Position& position) const override;
private:
};

