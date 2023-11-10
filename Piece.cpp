#include"Piece.h"

Piece::Piece() : couleur(pieceCouleur::Couleur::EMPTY), nom("?"), position(nullPosition) {}


Piece::Piece(pieceCouleur::Couleur couleur_, std::string nom_, Position position_) {
	couleur = couleur_;
	nom = nom_;
	position = position_;

}

std::string Piece::couleurToString() {
	if (static_cast<int>(couleur))
	{
		return "White";
	}
	else {
		return "Black";
	}
}


void Piece::setColorW() { couleur = pieceCouleur::Couleur::WHITE; }


Position Piece::getPosition() const { return position; }

pieceCouleur::Couleur Piece::getCouleur() const { return couleur; }

std::string Piece::getNom() const { return nom; }

void Piece::setColorB() { couleur = pieceCouleur::Couleur::BLACK; }



void Piece::setPosition(short int row, short int col) {
	position.first = row;
	position.second = col;
}