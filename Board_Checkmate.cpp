

bool Board::positionPutsKingInCheck(Piece* piece, const Position& position) {
	Position pieceOriginalPosition = piece->getPosition();
	Piece* myKing = findKing(piece->getCouleur());
	movePiece(piece, position);
	bool kingIsInCheck = false;
	for (auto& row : board) {
		for (auto& case_ : row) {
			if ((*case_) != nullptr && (*case_)->getCouleur()!=piece->getCouleur()) {
				if (myKing != nullptr)
				{
					if (((*case_)->deplacementValide(myKing->getPosition()) && PathIsClear((*case_)->getPosition(), myKing->getPosition()) && myKing->getCouleur() != (*case_)->getCouleur())) {
						kingIsInCheck = true;
					}
				}
			}
		}
	}
	movePiece(piece, pieceOriginalPosition);
	return kingIsInCheck;
}

Checkmate Board::kingWasKilled(Piece* piece, const Position& position) {
	if ((*board[position.first][position.second])) {
		if ((*board[position.first][position.second])->getNom() == "King" && (*board[position.first][position.second])->getCouleur() != piece->getCouleur()) {
			return Checkmate::KING_KILLED;
		}
	}
	return Checkmate::NONE;
}

Checkmate Board::pieceCannotMove(Piece* piece, const Position& position)
{
	Position pieceOriginalPosition = piece->getPosition();
	Piece* myKing = findKing(piece->getCouleur());
	
	std::vector<Piece*> myPieces = findPieces(piece->getCouleur());
	if (kingIsInCheck(piece, position) == Checkmate::CHECK) 
	{
		for (auto&& myPiece : myPieces) 
		{
			for (auto& row : board) {
				for (auto& case_ : row) {
					Position pieceOriginalPosition = myPiece->getPosition();
					movePiece(piece, position);

				}
			}
		}
	}
}

std::vector<Piece*> Board::findPieces(pieceCouleur::Couleur couleur) {
	std::vector<Piece*> Pieces = {};
	for (auto& row : board) {
		for (auto& case_ : row) {
			if ((*case_) != nullptr) {
				if ( (*case_)->getCouleur() == couleur) {
					Pieces.push_back(*case_);
				}
			}
		}
	}
	return Pieces;
}

Piece* Board::findKing(pieceCouleur::Couleur couleur) {
	for (auto& row : board) {
		for (auto& case_ : row) {
			if ((*case_) != nullptr) {
				if ((*case_)->getNom() == "King" && (*case_)->getCouleur() == couleur) {
					return (*case_);
				}
			}
			else {
				return nullptr;
			}
		}
	}
}

void Board::movePiece(Piece* piece, const Position& position)
{
	board[position.first][position.second].movePtrPiece(board[piece->getPosition().first][piece->getPosition().second].getPtrPiece());
	piece->setPosition(position.first, position.second);

}

bool Board::checkIsTreated(Piece* piece, const Position& position) {
	Position pieceOriginalPosition = piece->getPosition();
	bool checkTreated = true;

	bool checkmate = true;

	if (board[position.first][position.second].getPtrPieceBrute())
	{
		if (board[position.first][position.second].getPtrPieceBrute()->getCouleur() == piece->getCouleur()) {
			return false;
		}
	}

	if (Checkmate(*piece, position))
	{
		QMessageBox messageBox;
		QString winMessage = QString::fromStdString(piece->couleurToString());
		messageBox.information(0, winMessage + " Won", "Checkmate");
		std::exit(0);
	}

	board[position.first][position.second].movePtrPiece(board[piece->getPosition().first][piece->getPosition().second].getPtrPiece());
	piece->setPosition(position.first, position.second);

	std::vector<Piece*> PieceAdverse;
	Piece* myKing = nullptr;
	Piece* kingAdverse = nullptr;
	for (auto& row : board) {
		for (auto& case_ : row) {
			if ((*case_) != nullptr) {
				if ((*case_)->getNom() == "King" && (*case_)->getCouleur() == piece->getCouleur()) {
					myKing = (*case_);
				}
				if ((*case_)->getNom() == "King" && (*case_)->getCouleur() != piece->getCouleur()) {
					kingAdverse = (*case_);
				}
				if ((*case_)->getCouleur() != piece->getCouleur()) {
					PieceAdverse.push_back(*case_);
					std::cout << " ";
				}
			}
		}
	}

	for (auto& row : board) {
		for (auto& case_ : row) {
			if ((*case_) != nullptr) {
				if (myKing != nullptr)
				{
					if (((*case_)->deplacementValide(myKing->getPosition()) && PathIsClear((*case_)->getPosition(), myKing->getPosition()) && myKing->getCouleur() != (*case_)->getCouleur())) {
						checkTreated = false;
					}
				}
			}
		}
	}

	if (checkTreated == false)
	{
		Checkmate2(piece);
	}

	board[pieceOriginalPosition.first][pieceOriginalPosition.second].movePtrPiece(board[piece->getPosition().first][piece->getPosition().second].getPtrPiece());
	piece->setPosition(pieceOriginalPosition.first, pieceOriginalPosition.second);

	return checkTreated;
}

bool Board::Checkmate2(Piece* piece)
{
	bool checkmate = true;
	std::vector<Piece*> mesPieces;

	for (auto& row : board) {
		for (auto& case_ : row) {
			Piece* casePiece = *case_;
			if (casePiece != nullptr) {
				if (casePiece->getCouleur() == piece->getCouleur()) {
					mesPieces.push_back(casePiece);
				}
			}
		}
	}

	for (auto&& piece_ : mesPieces) {
		for (auto& row : board) {
			for (auto& case_ : row) {
				Position targetPosition = case_.getPosition();
				if (piece_->deplacementValide(targetPosition) && PathIsClear(piece_->getPosition(), targetPosition) && piece_->getPosition() != targetPosition) {
					// Save the original positions
					Position originalPiecePosition = piece_->getPosition();

					// Simulate the move
					board[targetPosition.first][targetPosition.second].movePtrPiece(board[originalPiecePosition.first][originalPiecePosition.second].getPtrPiece());
					piece_->setPosition(targetPosition.first, targetPosition.second);

					// Check if the king is still in check after the move
					bool isInCheck = checkIsTreated(piece, targetPosition);
					if (!isInCheck) {
						checkmate = false;
					}

					// Revert the move
					board[originalPiecePosition.first][originalPiecePosition.second].movePtrPiece(board[targetPosition.first][targetPosition.second].getPtrPiece());
					piece_->setPosition(originalPiecePosition.first, originalPiecePosition.second);

					if (!checkmate) {
						break;
					}
				}
			}
			if (!checkmate) {
				break;
			}
		}
		if (!checkmate) {
			break;
		}
	}

	if (checkmate) {
		QMessageBox messageBox;
		QString winMessage = QString::fromStdString(piece->couleurToString());
		messageBox.information(0, winMessage + " Lost", "Checkmate2");
		std::exit(0);
	}

	return checkmate;
}

bool Board::Checkmate(Piece& piece, const Position& position) {
	if ((*board[position.first][position.second])) {
		return ((*board[position.first][position.second])->getNom() == "King" && (*board[position.first][position.second])->getCouleur() != piece.getCouleur());
	}
	return 0;
}