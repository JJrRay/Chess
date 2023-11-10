#include <QtCore/QCoreApplication>
#include<iostream>
#include <QApplication>
#include <QMainWindow>
#include "ChessBoard.h"
#include "Board.h"
#include "configurationwindow.h"

using namespace std;
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    ConfigurationWindow configWindow;
    configWindow.show();

    QObject::connect(&configWindow, &ConfigurationWindow::configurationSelected, [configWindowPtr = &configWindow](int config) {
        configWindowPtr->hide(); // Hide the configuration window

        // Create the main window with the selected configuration
        QMainWindow* mainWindow = new QMainWindow();
        mainWindow->setAttribute(Qt::WA_DeleteOnClose);
        Board* board = new Board(config);
        ChessBoard* chessBoard = new ChessBoard(*board, mainWindow);
        QWidget* centralWidget = new QWidget();
        QVBoxLayout* layout = new QVBoxLayout(centralWidget);

        QWidget* chessBoardContainer = new QWidget(centralWidget);
        QVBoxLayout* chessBoardLayout = new QVBoxLayout(chessBoardContainer);
        chessBoardLayout->addWidget(chessBoard);
        chessBoardContainer->setLayout(chessBoardLayout);
        chessBoardContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        layout->addWidget(chessBoardContainer);

        mainWindow->setCentralWidget(centralWidget);
        mainWindow->show();
        });

    int result = app.exec();

    return result;
}