#include "minesweeper.h"
#include "menu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Menu w;
    //Minesweeper w;
    //Minesweeper w(0,390,400,16,16,40);
    //Minesweeper w(0,700,400,16,30,99);
    w.show();
    return a.exec();
}
