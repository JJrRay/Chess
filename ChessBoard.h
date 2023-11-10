#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Board.h"

class ChessBoard : public QWidget {
    Q_OBJECT

signals:
    void currentPlayerChanged(pieceCouleur::Couleur newPlayer);

public:

    explicit ChessBoard(Board& board, QWidget* parent = nullptr);

    QIcon loadPieceIcon(const std::string& pieceName, pieceCouleur::Couleur couleur);
    
    void updatePlayerTurnLabel();

    void highlightKingInCheck(pieceCouleur::Couleur kingColor, const Position& selectedPiecePosition);

private slots:
    void onCellClicked();

private:
    QGridLayout* gridLayout;
    QLabel* playerTurnLabel;
    //bool isCurrentPlayerPiece(Piece* piece);

    void createBoard();
    void setupPieces();
    void connectCells();
    void updateCurrentPlayerText(pieceCouleur::Couleur newPlayer);

    int findRow(QPushButton* cell) const;
    int findCol(QPushButton* cell) const;

    static const int boardSize = 8;
    QPushButton* buttonBoard[boardSize][boardSize];
    Piece* pieces[boardSize][boardSize] = {};
    QString originalColors[boardSize][boardSize];

    Board& board;
};

#endif // CHESSBOARD_H
