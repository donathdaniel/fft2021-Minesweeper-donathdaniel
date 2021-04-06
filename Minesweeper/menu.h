#ifndef MENU_H
#define MENU_H

#include "minesweeper.h"

#include <QMainWindow>

class Menu : public QMainWindow
{
    Q_OBJECT
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
};

#endif // MENU_H
