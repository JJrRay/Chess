#pragma once
#include"Piece.h"

class Queen :public Piece {
public:
	Queen();
	Queen(pieceCouleur::Couleur couleur_, Position position_);
	bool enDiagonale(const Position& autrePosition) const;
	bool deplacementValide(const Position& position) const override;
private:
};