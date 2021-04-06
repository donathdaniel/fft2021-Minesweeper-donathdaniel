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
#include "flagcounter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Minesweeper; }
QT_END_NAMESPACE

class Minesweeper : public QWidget
{
    Q_OBJECT

public:
    Minesweeper(QWidget *parent = nullptr, int width=228, int height=250, int row=9, int col=9, int bombNumber=10);
    ~Minesweeper();

private slots:
    void resetGame();
    void gameContinue();
    void makeFlag();
    void endGame(int, int);
    void winner();

signals:
    void gameOver(int, int);
    void weHaveTheWinner();
    void minusBomb(int);
    void plusBomb(int);

private:
    Ui::Minesweeper *ui;
    int ROW, COL, totalBombs;
    QVector<QVector<int>> matrix;
    QVector<QVector<bool>> visited;
    int flagedPositions;
    int rowNum[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int colNum[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    bool firstMove=false;

    QHBoxLayout* hLayout;
    QVBoxLayout* vLayout;
    QGridLayout* gLayout;
    QPushButton* smileyButton;
    FlagCounter* flagCounter;
    Clock* clock;

    bool isValid(int row, int col);
    int remainedPositions();
    void discovery(int, int);

    //design
    QString buttonStyle="font: bold; background-color: #3e432e;";
    QString buttonStyleDisabled="font: bold; background-color: #616f39;";
    QVector<QString> colorsOfNumbers={"color:blue;",
                                      "color:green;",
                                      "color:red;",
                                      "color:purple;",
                                      "color:black;",
                                      "color:gray;",
                                      "color:maroon;",
                                      "color:turquise;"};
};
#endif // MINESWEEPER_H
