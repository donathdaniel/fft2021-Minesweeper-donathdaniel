#include "menu.h"
#include "minesweeper.h"
#include <QMenuBar>

Menu::Menu(QWidget *parent) : QMainWindow(parent)
{
    mainLayout = new QVBoxLayout();

    menuBar = new QMenuBar();
    fileMenu = new QMenu("Difficulty");
    menuBar->addMenu(fileMenu);

    widget=new QWidget();
    w=new Minesweeper();

    widget->setLayout(mainLayout);
    mainLayout->addWidget(w);

    QAction *beginner = new QAction("Beginner", this);
    connect(beginner, &QAction::triggered,this,&Menu::beginnerGame);
    fileMenu->addAction(beginner);

    QAction *intermediate = new QAction("Intermediate", this);
    connect(intermediate, &QAction::triggered,this,&Menu::intermediateGame);
    fileMenu->addAction(intermediate);

    QAction *expert = new QAction("Expert", this);
    connect(expert, &QAction::triggered,this,&Menu::expertGame);
    fileMenu->addAction(expert);

    mainLayout->setMenuBar(menuBar);
    setCentralWidget(widget);

}

void Menu::beginnerGame()
{
    mainLayout->removeWidget(w);
    delete w;
    w=new Minesweeper;
    mainLayout->addWidget(w);//228,250 - 18, 40
    setFixedSize(246,290);
}

void Menu::intermediateGame()
{
    mainLayout->removeWidget(w);
    delete w;
    w=new Minesweeper(0,390,400,16,16,40);
    mainLayout->addWidget(w);
    setFixedSize(408,440);
}

void Menu::expertGame()
{
    mainLayout->removeWidget(w);
    delete w;
    w=new Minesweeper(0,700,400,16,30,99);
    mainLayout->addWidget(w);
    setFixedSize(718,440);
}
