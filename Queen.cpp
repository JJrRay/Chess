#include "Queen.h"


Queen::Queen() :Piece(pieceCouleur::Couleur::EMPTY, "Queen", nullPosition) {}


Queen::Queen(pieceCouleur::Couleur couleur_, Position position_) : Piece(couleur_, "Queen", position_){}


bool Queen::enDiagonale(const Position &autrePosition) const 
{
	return(abs(autrePosition.first - position.first) == abs(autrePosition.second - position.second));
}


bool Queen::deplacementValide(const Position& autrePosition) const
{
	return isInBoard(autrePosition) && (Piece::position.first == autrePosition.first || Piece::position.second == autrePosition.second || enDiagonale(autrePosition));
}

