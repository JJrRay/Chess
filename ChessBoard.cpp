  #include "chessboard.h"


#include<QMessageBox>


ChessBoard::ChessBoard(Board& board, QWidget* parent)
    : QWidget(parent), board(board)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);

    playerTurnLabel = new QLabel();
    updatePlayerTurnLabel();

    createBoard();
    connectCells();

    mainLayout->addLayout(gridLayout);
    mainLayout->addWidget(playerTurnLabel); 

    connect(this, &ChessBoard::currentPlayerChanged, this, &ChessBoard::updateCurrentPlayerText);
}


    int ChessBoard::findRow(QPushButton* cell) const {
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                if (buttonBoard[row][col] == cell) {
                    return row;
                }
            }
        }
        return -1;
    }

    int ChessBoard::findCol(QPushButton* cell) const {
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                if (buttonBoard[row][col] == cell) {
                    return col;
                }
            }
        }
        return -1;
    }


   /* bool ChessBoard::isCurrentPlayerPiece(Piece* piece) {
        return piece && piece->getCouleur() == currentPlayer;
    }*/

    void ChessBoard::createBoard() {
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                buttonBoard[row][col] = new QPushButton();
                buttonBoard[row][col]->setFixedSize(50, 50); // Taille de la case (modifiable)

                // Alternance des couleurs de l'échiquier
                QString backgroundColor = (row + col) % 2 == 0 ? "#09763F" : "#f8e4bc";
                buttonBoard[row][col]->setStyleSheet("background-color: " + backgroundColor);
                originalColors[row][col] = backgroundColor;

                // Ajout des boutons à la grille
                gridLayout->addWidget(buttonBoard[row][col], row, col, 1, 1);
            }
        }
        setupPieces();
    }

    QIcon ChessBoard:: loadPieceIcon(const std::string& pieceName, pieceCouleur::Couleur couleur) {
        QString fileName = QString::fromStdString(pieceName) + (couleur == pieceCouleur::Couleur::WHITE ? "_white" : "_black") + ".png";
        return QIcon(fileName);
    }

    void ChessBoard::connectCells() {
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                connect(buttonBoard[row][col], &QPushButton::clicked, this, &ChessBoard::onCellClicked);
            }
        }
    }

    void ChessBoard::updatePlayerTurnLabel() {
        QString playerName = board.getCurrentPlayer() == pieceCouleur::Couleur::WHITE ? "Blanc" : "Noir";
        playerTurnLabel->setText("Tour du joueur : " + playerName);
    }

    void ChessBoard::highlightKingInCheck(pieceCouleur::Couleur kingColor, const Position& selectedPiecePosition) {
        Position kingPosition = board.findKing(kingColor)->getPosition();
        Piece* selectedPiece = board.getPiece(selectedPiecePosition);

        if (selectedPiece && board.positionPutsKingInCheck(selectedPiece, selectedPiece->getPosition())) {
            buttonBoard[kingPosition.first][kingPosition.second]->setStyleSheet("background-color: #0854fc;");

            // If the selected piece can move to the king's position, set the king's background color to red
            if (board.bougerPieceValide(*selectedPiece, kingPosition)) {
                buttonBoard[kingPosition.first][kingPosition.second]->setStyleSheet("background-color: #e80424;");
            }
        }
        else {
            buttonBoard[kingPosition.first][kingPosition.second]->setStyleSheet("background-color: " + originalColors[kingPosition.first][kingPosition.second]);
        }
    }


    void ChessBoard::onCellClicked() {
        QPushButton* clickedCell = qobject_cast<QPushButton*>(sender());
        if (!clickedCell) {
            return;
        }

        static QPushButton* selectedCell = nullptr;

        if (!selectedCell) {
            int row = findRow(clickedCell);
            int col = findCol(clickedCell);
            if (board.getPiece({ row, col })) {
                if (board.getPiece({ row, col }) && board.getPiece({ row, col })->getCouleur() == board.getCurrentPlayer()) {
                    selectedCell = clickedCell;
                    selectedCell->setStyleSheet("background-color: yellow;");

                    for (int row = 0; row < boardSize; ++row) {
                        for (int col = 0; col < boardSize; ++col) {
                            Piece* test = board.getPiece({ findRow(selectedCell), findCol(selectedCell) });
                            if (board.bougerPieceValide(*test, { row, col }) && (!board.pieceExiste({ row, col }) || board.getPiece({ row, col })->getCouleur() != test->getCouleur())) {
                                buttonBoard[row][col]->setStyleSheet("background-color: #e80424;");
                            }
                        }
                    }
                }
                
            }
        }
        else {
            int newRow = findRow(clickedCell);
            int newCol = findCol(clickedCell);
            Piece* newPiece = board.getPiece({ newRow, newCol });

            if (newPiece && newPiece->getCouleur() == board.getPiece({ findRow(selectedCell), findCol(selectedCell) })->getCouleur()) {
                selectedCell->setStyleSheet("background-color: " + originalColors[findRow(selectedCell)][findCol(selectedCell)]);

                selectedCell = clickedCell;
                selectedCell->setStyleSheet("background-color: yellow;");

                for (int row = 0; row < boardSize; ++row) {
                    for (int col = 0; col < boardSize; ++col) {
                        Piece* test = board.getPiece({ findRow(selectedCell), findCol(selectedCell) });
                        if (board.bougerPieceValide(*test, { row, col }) && (!board.pieceExiste({ row, col }) || board.getPiece({ row, col })->getCouleur() != test->getCouleur())) {
                            buttonBoard[row][col]->setStyleSheet("background-color: #e80424;");
                            selectedCell->setStyleSheet("background-color: yellow;");

                        }
                        else {
                            buttonBoard[row][col]->setStyleSheet("background-color: " + originalColors[row][col]);
                            selectedCell->setStyleSheet("background-color: yellow;");
                        }
                    }
                }

                Position whiteKingPos = board.findKing(pieceCouleur::Couleur::WHITE)->getPosition();
                Position blackKingPos = board.findKing(pieceCouleur::Couleur::BLACK)->getPosition();
                highlightKingInCheck(pieceCouleur::Couleur::WHITE, whiteKingPos);
                highlightKingInCheck(pieceCouleur::Couleur::BLACK, blackKingPos);
                if (selectedCell == clickedCell) {
                    Piece* selectedPiece = board.getPiece({ findRow(selectedCell), findCol(selectedCell) });
                    if (selectedPiece->getCouleur() != pieceCouleur::Couleur::WHITE && board.bougerPieceValide(*selectedPiece, whiteKingPos)) {
                        buttonBoard[whiteKingPos.first][whiteKingPos.second]->setStyleSheet("background-color: #e80424;");
                    }
                    if (selectedPiece->getCouleur() != pieceCouleur::Couleur::BLACK && board.bougerPieceValide(*selectedPiece, blackKingPos)) {
                        buttonBoard[blackKingPos.first][blackKingPos.second]->setStyleSheet("background-color: #e80424;");
                    }
                    if (Position({ findRow(selectedCell),findCol(selectedCell) }) == blackKingPos || Position({ findRow(selectedCell),findCol(selectedCell) }) == whiteKingPos)
                    {
                        selectedCell->setStyleSheet("background-color: yellow;");
                    }
                }

            }
            else {
                // Récupère les indices de la case sélectionnée et de la case cliquée
                int selectedRow, selectedCol, clickedRow, clickedCol;
                for (int row = 0; row < boardSize; ++row) {
                    for (int col = 0; col < boardSize; ++col) {
                        if (buttonBoard[row][col] == selectedCell) {
                            selectedRow = row;
                            selectedCol = col;
                        }
                        if (buttonBoard[row][col] == clickedCell) {
                            clickedRow = row;
                            clickedCol = col;
                        }
                    }
                }

                // Obtient les pièces à partir des positions
                Piece* selectedPiece = board.getPiece({ selectedRow, selectedCol });

                Position targetPosition = { clickedRow, clickedCol };
                Position PiecePosition = selectedPiece->getPosition();

                // Copie des conditions de bougerPiece()
                if (board.bougerPieceValide(*selectedPiece,targetPosition)) {

                    // Vérifie si le déplacement est valide, puis déplace la pièce
                    if (board.pieceExiste(targetPosition) && selectedPiece->getCouleur() != board.getPiece(targetPosition)->getCouleur() || !board.pieceExiste(targetPosition)) {

                        // Déplace la pièce sur le tableau Board
                        board.bougerPiece(*selectedPiece, targetPosition);
                        board.changeCurrentPlayer();
                        emit currentPlayerChanged(board.getCurrentPlayer());

                        // Met à jour les icônes des boutons
                        QIcon movedPieceIcon = selectedCell->icon();
                        clickedCell->setIcon(movedPieceIcon);
                        clickedCell->setIconSize(QSize(40, 40));
                        selectedCell->setIcon(QIcon());

                        // Réinitialise la cellule où la pièce a été déplacée et la cellule sélectionnée
                        buttonBoard[clickedRow][clickedCol]->setStyleSheet("background-color: " + originalColors[clickedRow][clickedCol] );
                        selectedCell->setStyleSheet("background-color: " + originalColors[selectedRow][selectedCol]);

                        // Reset les couleurs de la grille
                        for (int row = 0; row < boardSize; ++row) {
                            for (int col = 0; col < boardSize; ++col) {
                                if (buttonBoard[row][col] != clickedCell) {
                                    QString backgroundColor = originalColors[row][col];
                                    buttonBoard[row][col]->setStyleSheet("background-color: " + originalColors[row][col]);
                                    selectedCell = nullptr;
                                }
                            }
                        }
                        Position whiteKingPos = board.findKing(pieceCouleur::Couleur::WHITE)->getPosition();
                        Position blackKingPos = board.findKing(pieceCouleur::Couleur::BLACK)->getPosition();
                        highlightKingInCheck(pieceCouleur::Couleur::WHITE, whiteKingPos);
                        highlightKingInCheck(pieceCouleur::Couleur::BLACK, blackKingPos);

                    }

                }
            }
        }
    }


    bool Board::PieceCannotMove(pieceCouleur::Couleur couleur) {
        std::vector<Piece*> myPieces = findPieces((couleur));

        for (auto&& myPiece : myPieces) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    Position targetPosition = { i, j };
                    Piece* targetPiece = getPiece(targetPosition);

                    if (targetPiece && targetPiece->getCouleur() != couleur) {
                        continue;
                    }

                    if (bougerPieceValide(*myPiece, targetPosition)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }


    void ChessBoard::setupPieces() {
        for (int row = 0; row < boardSize; ++row) {
            for (int col = 0; col < boardSize; ++col) {
                Piece* piece = board.getPiece({ row, col });
                if (piece) {
                    buttonBoard[row][col]->setIcon(loadPieceIcon(piece->getNom(), piece->getCouleur()));
                    buttonBoard[row][col]->setIconSize(QSize(40, 40));
                }
            }
        }
    }

    void ChessBoard::updateCurrentPlayerText(pieceCouleur::Couleur newPlayer)
    {
        QString playerColor = (newPlayer == pieceCouleur::Couleur::WHITE) ? "Blanc" : "Noir";
        playerTurnLabel->setText("Tour du joueur : " + playerColor);
    }



