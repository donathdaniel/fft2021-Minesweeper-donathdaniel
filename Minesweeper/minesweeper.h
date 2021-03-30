#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QWidget>
#include <QVector>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRandomGenerator>
#include <QPixmap>
#include "clock.h"
#include "bombcounter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Minesweeper; }
QT_END_NAMESPACE

class Minesweeper : public QWidget
{
    Q_OBJECT

public:
    Minesweeper(QWidget *parent = nullptr);
    ~Minesweeper();

private slots:
    void resetGame();
    bool isValid(int row, int col);
    void gameContinue();
    void makeFlag();
    void discovery(int, int);
    void endGame();
    int remainedPositions();
    void winner();

signals:
    void gameOver();
    void weHaveTheWinner();
    void minusBomb(int);
    void plusBomb(int);

private:
    Ui::Minesweeper *ui;
    int ROW=16, COL=16, totalBombs=40;
    QVector<QVector<int>> matrix;
    QVector<QVector<bool>> visited;
    int flagedPositions;
    int rowNum[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int colNum[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    QVector<QString> colorsOfNumbers={"color:blue;",
                                      "color:green;",
                                      "color:red;",
                                      "color:purple;",
                                      "color:black;",
                                      "color:gray;",
                                      "color:maroon;",
                                      "color:turquise;"};


    QHBoxLayout* hLayout;
    QVBoxLayout* vLayout;
    QGridLayout* gLayout;
    QPushButton* smileyButton;
    BombCounter* bombCounter;
    Clock* clock;
};
#endif // MINESWEEPER_H
