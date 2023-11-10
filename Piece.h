#pragma once
#include<iostream>
#include"multiFunctions.h"
#include"Position.h"

namespace pieceCouleur {
	enum class Couleur { BLACK, WHITE, EMPTY };
}

class Piece 
{
public:

	Piece();
	Piece(pieceCouleur::Couleur couleur_, std::string nom_,Position position_);
	virtual bool deplacementValide(const Position& position) const = 0;
	void setColorB();
	void setColorW();
	Position getPosition() const;
	void setPosition(short int lettre, short int chiffre);
	pieceCouleur::Couleur getCouleur() const;
	std::string getNom() const;
	std::string couleurToString();

protected:
	//changer attribut protected pour private et mettre des getter protected
	Position position;
	std::string nom;
	pieceCouleur::Couleur couleur;
};

