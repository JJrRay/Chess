#pragma once
#include<cassert>
#include"Piece.h"
#include"kingInstanceError.h"


class King : public Piece {
public:
	King();
	King(pieceCouleur::Couleur couleur_, Position position_);
	bool deplacementValide(const Position& position) const override;
private:
	static int instanceCounter;
};

