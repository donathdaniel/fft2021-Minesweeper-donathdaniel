#ifndef MENU_H
#define MENU_H

#include "minesweeper.h"

#include <QMainWindow>

class Menu : public QMainWindow
{
    Q_OBJECT
    //making the interface of the game(actuall game and the difficulty levels)
public:
    explicit Menu(QWidget *parent = nullptr);

private slots:
    void beginnerGame();
    void intermediateGame();
    void expertGame();

signals:

private:
    Minesweeper* w;
    QWidget* widget;
    QMenuBar* menuBar;
    QMenu *fileMenu;
    QVBoxLayout *mainLayout;

    void deleteWidget();
};

#endif // MENU_H
