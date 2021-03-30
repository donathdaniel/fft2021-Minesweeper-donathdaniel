#include "minesweeper.h"
#include "ui_minesweeper.h"
#include "specialbutton.h"

Minesweeper::Minesweeper(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Minesweeper)
{
    ui->setupUi(this);

    //    design
    //    szintek



    setFixedSize(400,400);
    flagedPositions=totalBombs;
    hLayout=new QHBoxLayout;

    bombCounter= new BombCounter(flagedPositions);
    connect(this,&Minesweeper::plusBomb,bombCounter,&BombCounter::showBombs);
    connect(this,&Minesweeper::minusBomb,bombCounter,&BombCounter::showBombs);

    smileyButton= new QPushButton();
    connect(smileyButton,&SpecialButton::clicked,this,&Minesweeper::resetGame);

    clock=new Clock();

    hLayout->addWidget(bombCounter);
    hLayout->addWidget(smileyButton);
    hLayout->addWidget(clock);

    gLayout=new QGridLayout;
    gLayout->setSpacing(0);
    matrix.resize(ROW,QVector<int>(COL));
    visited.resize(ROW,QVector<bool>(COL));

    for(int i=0;i<ROW;++i){
        for(int j=0;j<COL;++j){
            SpecialButton* specialButton=new SpecialButton();

            specialButton->setFixedSize(25,25);
            gLayout->addWidget(specialButton,i,j);

            connect(specialButton,&SpecialButton::leftMouseButton,this,&Minesweeper::gameContinue);
            connect(specialButton,&SpecialButton::rightMouseButton,this,&Minesweeper::makeFlag);
        }
    }
    resetGame();
    connect(this,&Minesweeper::weHaveTheWinner,this,&Minesweeper::winner);
    connect(this,&Minesweeper::gameOver,this,&Minesweeper::endGame);

    vLayout=new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addLayout(gLayout);

    setLayout(vLayout);
}

void Minesweeper::resetGame()
{
    for(int i=0;i<ROW;++i){
        for(int j=0;j<COL;++j){
            matrix[i][j]=0;
            visited[i][j]=false;
        }
    }

    int n,m ;
    for(int i=0;i<totalBombs;++i){
        n=QRandomGenerator::global()->bounded(0,ROW);
        m=QRandomGenerator::global()->bounded(0,COL);
        while(matrix[n][m]==9){
            n=QRandomGenerator::global()->bounded(0,ROW);
            m=QRandomGenerator::global()->bounded(0,COL);
        }
        matrix[n][m]=9;
    }

    int bombCounter;
    for(int i=0;i<ROW;++i){
        for(int j=0;j<COL;++j){
            if(!matrix[i][j]){
                bombCounter=0;
                for (int k = 0; k < 8; ++k){
                    if(isValid(i+rowNum[k],j+colNum[k]) && matrix[i+rowNum[k]][j+colNum[k]]==9) bombCounter++;
                }
                matrix[i][j]=bombCounter;
            }
        }
    }
    QDebug dbg(QtDebugMsg);
    for(int i=0;i<ROW;++i){
        for(int j=0;j<COL;++j){
            dbg << matrix[i][j];
        }
        dbg<<"\n";
    }

    for(int idx = 0; idx < gLayout->count(); idx++)
      {
        QWidget *item = gLayout->itemAt(idx)->widget();
        if(item !=NULL){
            item->setEnabled(true);
            SpecialButton* button=dynamic_cast<SpecialButton*>(item);
            button->setIcon(QIcon());
            button->setText("");
        }
      }

    QPixmap pixmap(":/Resources/img/smiley1.ico");
    QIcon ButtonIcon(pixmap);
    smileyButton->setIcon(ButtonIcon);

    clock->restart();
}



bool Minesweeper::isValid(int row, int col)
{
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

void Minesweeper::gameContinue()
{
    SpecialButton *button = (SpecialButton *)sender();
    if (button != NULL){
        if(!button->icon().isNull()){
            return;
        }
        int index=gLayout->indexOf(button);
        int a,b,c;
        gLayout->getItemPosition(index,&a,&b,&c,&c);

        discovery(a,b);

        int remained=remainedPositions();
        //qDebug()<<remained;
        if(remained==totalBombs){
            emit weHaveTheWinner();
        }
    }
    gLayout->indexOf(button);
}

void Minesweeper::makeFlag()
{
    SpecialButton *specialButton = (SpecialButton *)sender();
    if(specialButton->text()==""){
        if(specialButton->icon().isNull()){
            QPixmap pixmap(":/Resources/img/flag.ico");
            QIcon ButtonIcon(pixmap);
            specialButton->setIcon(ButtonIcon);
            flagedPositions--;
            emit minusBomb(flagedPositions);
        }
        else{
            specialButton->setIcon(QIcon());
            flagedPositions++;
            emit plusBomb(flagedPositions);
        }
    }
}

void Minesweeper::discovery(int i, int j)
{
    if(matrix[i][j]==9){
        emit gameOver();
        return;
    }
    else{
        QLayoutItem* item =gLayout->itemAtPosition(i,j);
        QWidget* widget=item->widget();
        SpecialButton* button=dynamic_cast<SpecialButton*>(widget);

        if(matrix[i][j]!=0){
            button->setText(QString::number(matrix[i][j]));
            button->setStyleSheet(colorsOfNumbers[matrix[i][j]-1]);
            return;
        }
        visited[i][j]=true;
        button->setDisabled(true);

        for(int k=0;k<8;++k){
            if(isValid(i+rowNum[k],j+colNum[k]) && !visited[i+rowNum[k]][j+colNum[k]]){
                    discovery(i+rowNum[k],j+colNum[k]);
            }
        }
    }
}

void Minesweeper::endGame()
{
    QPixmap pixmap(":/Resources/img/smiley3.ico");
    QIcon ButtonIcon(pixmap);
    smileyButton->setIcon(ButtonIcon);
    clock->getTimer()->stop();

    for(int idx = 0; idx < gLayout->count(); idx++)
      {
        QWidget *item = gLayout->itemAt(idx)->widget();
        if(item !=NULL){
            item->setDisabled(true);

            SpecialButton* button=dynamic_cast<SpecialButton*>(item);
            int index=gLayout->indexOf(button);
            int a,b,c;
            gLayout->getItemPosition(index,&a,&b,&c,&c);

            if(matrix[a][b]==9){
                QPixmap pixmap(":/Resources/img/bomb.png");
                QIcon ButtonIcon(pixmap);
                button->setIcon(ButtonIcon);
            }
        }
    }
}

int Minesweeper::remainedPositions()
{
    int remained=0;
    for(int idx = 0; idx < gLayout->count(); idx++)
      {
        QWidget *item = gLayout->itemAt(idx)->widget();
        if(item !=NULL){
            if(item->isEnabled()){
                SpecialButton* button=dynamic_cast<SpecialButton*>(item);
                if(button->text()=="") remained++;
            }
        }
    }
    return remained;
}

void Minesweeper::winner()
{
    QPixmap pixmap(":/Resources/img/smiley.ico");
    QIcon ButtonIcon(pixmap);
    smileyButton->setIcon(ButtonIcon);
    clock->getTimer()->stop();
    bombCounter->display(0);

    for(int idx = 0; idx < gLayout->count(); idx++)
      {
        QWidget *item = gLayout->itemAt(idx)->widget();
        if(item !=NULL){
            item->setDisabled(true);
        }
    }
}

Minesweeper::~Minesweeper()
{
    delete ui;
}

