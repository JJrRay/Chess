#include "King.h"


int King::instanceCounter = 0;


King::King():Piece(pieceCouleur::Couleur::EMPTY, "King", nullPosition)
{
	instanceCounter++;
	if (instanceCounter >= 2) {
		throw kingInstanceError("Erreur: Seulement 2 instances de King permises");
	}
	
}


King::King(pieceCouleur::Couleur couleur_, Position position_) : Piece(couleur_, "King", position_) {
	
	if (instanceCounter >= 2) {
		throw kingInstanceError("Erreur: Seulement 2 instances de King permises");
	}
	instanceCounter++;
}


bool King::deplacementValide(const Position& autrePosition) const
{
	return isInBoard(autrePosition) && (abs(position.first - autrePosition.first) <= 1 && abs(position.second - autrePosition.second) <= 1);
}