#include "minesweeper.h"
#include "ui_minesweeper.h"
#include "specialbutton.h"

Minesweeper::Minesweeper(QWidget *parent , int width, int height, int row, int col, int bombNumber)
    : QWidget(parent)
    , ui(new Ui::Minesweeper), ROW(row), COL(col), totalBombs(bombNumber)
{
    ui->setupUi(this);

    //size setting
    setFixedSize(width,height);
    setStyleSheet("background-color: #616f39;");

    hLayout=new QHBoxLayout;

    flagCounter= new FlagCounter();
    flagedPositions=totalBombs;
    flagCounter->showBombs(flagedPositions);
    connect(this,&Minesweeper::plusBomb,flagCounter,&FlagCounter::showBombs);
    connect(this,&Minesweeper::minusBomb,flagCounter,&FlagCounter::showBombs);

    smileyButton= new QPushButton();
    connect(smileyButton,&SpecialButton::clicked,this,&Minesweeper::resetGame);

    clock=new Clock();

    hLayout->addWidget(flagCounter);
    hLayout->addWidget(smileyButton);
    hLayout->addWidget(clock);

    //grid layout
    gLayout=new QGridLayout;
    gLayout->setSpacing(0);
    matrix.resize(ROW,QVector<int>(COL));
    visited.resize(ROW,QVector<bool>(COL));

    for(int i=0;i<ROW;++i){
        for(int j=0;j<COL;++j){
            SpecialButton* specialButton=new SpecialButton();

            specialButton->setFixedSize(25,25);
            gLayout->addWidget(specialButton,i,j);

            //special button left click(flag), right click(discover)
            connect(specialButton,&SpecialButton::leftMouseButton,this,&Minesweeper::gameContinue);
            connect(specialButton,&SpecialButton::rightMouseButton,this,&Minesweeper::makeFlag);
        }
    }

    //the logic of the game(winning, losing)
    connect(this,&Minesweeper::weHaveTheWinner,this,&Minesweeper::winner);
    connect(this,&Minesweeper::gameOver,this,&Minesweeper::endGame);

    //game setup
    resetGame();

    vLayout=new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addLayout(gLayout);

    setLayout(vLayout);
}

Minesweeper::~Minesweeper()
{
    delete ui;
}


void Minesweeper::resetGame()
{
    for(int i=0;i<ROW;++i){
        for(int j=0;j<COL;++j){
            matrix[i][j]=0;
            visited[i][j]=false;
        }
    }

    //generating the bombs
    int n,m;
    srand(time(NULL));
    for(int i=0;i<totalBombs;++i){
        n=rand()%(ROW);
        m=rand()%(COL);
        while(matrix[n][m]==9){
            n=rand()%(ROW);
            m=rand()%(COL);
        }
        matrix[n][m]=9;
    }

    //set the number of the flags
    flagedPositions=totalBombs;
    flagCounter->showBombs(flagedPositions);

    //fill the matrix with the numbers
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

    //printing the matrix
    QDebug dbg(QtDebugMsg);
    for(int i=0;i<ROW;++i){
        for(int j=0;j<COL;++j){
            dbg << matrix[i][j];
        }
        dbg<<"\n";
    }

    //buttons set enabled, remove text, and icons+ add stylesheet
    for(int idx = 0; idx < gLayout->count(); idx++)
      {
        QWidget *item = gLayout->itemAt(idx)->widget();
        if(item !=NULL){
            item->setEnabled(true);
            SpecialButton* button=dynamic_cast<SpecialButton*>(item);
            button->setIcon(QIcon());
            button->setText("");
            button->setStyleSheet(buttonStyle);
        }
      }

    //set smiley button properties
    smileyButton->setStyleSheet(buttonStyleDisabled);
    QPixmap pixmap(":/Resources/img/smiley1.ico");
    QIcon ButtonIcon(pixmap);
    smileyButton->setIcon(ButtonIcon);
    smileyButton->setFixedSize(30,30);

    firstMove=false;
    clock->stoptTimer();
    clock->display("00");
}



bool Minesweeper::isValid(int row, int col)
{
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

void Minesweeper::gameContinue()
{
    if(!firstMove){
        clock->restart();
        firstMove=true;
    }
    //left click event
    SpecialButton *button = (SpecialButton *)sender();
    if (button != NULL){
        if(!button->icon().isNull()){
            return;
        }
        //find the position of the sender widget
        int index=gLayout->indexOf(button);
        int a,b,c;
        gLayout->getItemPosition(index,&a,&b,&c,&c);

        //backtracking
        discovery(a,b);

        //if free position==bombs => winner
        int remained=remainedPositions();
        if(remained==totalBombs){
            emit weHaveTheWinner();
        }
    }
    gLayout->indexOf(button);
}

void Minesweeper::makeFlag()
{
    //right click event
    SpecialButton *specialButton = (SpecialButton *)sender();
    if(specialButton->text()==""){
        if(specialButton->icon().isNull()){
            //add flag
            QPixmap pixmap(":/Resources/img/flag.ico");
            QIcon ButtonIcon(pixmap);
            specialButton->setIcon(ButtonIcon);
            emit minusBomb(--flagedPositions);
        }
        else{
            //remove flag
            specialButton->setIcon(QIcon());
            emit plusBomb(++flagedPositions);
        }
    }
}

void Minesweeper::discovery(int i, int j)
{
    if(matrix[i][j]==9){
        //bomb was found
        emit gameOver(i,j);
        return;
    }
    else{
        //find the sender widget by the indexes
        QLayoutItem* item =gLayout->itemAtPosition(i,j);
        QWidget* widget=item->widget();
        SpecialButton* button=dynamic_cast<SpecialButton*>(widget);

        if(!button->icon().isNull()){
            button->setIcon(QIcon());
            emit plusBomb(++flagedPositions);
        }

        if(matrix[i][j]!=0){
            //number was found, backtrack stops here
            button->setText(QString::number(matrix[i][j]));
            button->setStyleSheet(colorsOfNumbers[matrix[i][j]-1]+buttonStyleDisabled);
            return;
        }
        visited[i][j]=true;
        button->setDisabled(true);
        button->setStyleSheet(buttonStyleDisabled);

        //check all the 8 posibilities
        for(int k=0;k<8;++k){
            if(isValid(i+rowNum[k],j+colNum[k]) && !visited[i+rowNum[k]][j+colNum[k]]){
                discovery(i+rowNum[k],j+colNum[k]);
            }
        }
    }
}

void Minesweeper::endGame(int i, int j)
{
    //losing

    //find the sender widget by the indexes, and change the background red
    QLayoutItem* item =gLayout->itemAtPosition(i,j);
    QWidget* widget=item->widget();
    SpecialButton* button=dynamic_cast<SpecialButton*>(widget);
    button->setStyleSheet("background-color:red");

    //change the smiley button to sad
    QPixmap pixmap(":/Resources/img/smiley3.ico");
    QIcon ButtonIcon(pixmap);
    smileyButton->setIcon(ButtonIcon);

    //stopping the clock
    clock->stoptTimer();

    //disable all the buttons
    for(int idx = 0; idx < gLayout->count(); idx++)
      {
        QWidget *item = gLayout->itemAt(idx)->widget();
        if(item !=NULL){
            item->setDisabled(true);
            SpecialButton* button=dynamic_cast<SpecialButton*>(item);

            //find the position of the sender widget
            int index=gLayout->indexOf(button);
            int a,b,c;
            gLayout->getItemPosition(index,&a,&b,&c,&c);

            //find all the bombs and show them
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
    //counting all the free position
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
    //winning

    //set the smiley button to swag
    QPixmap pixmap(":/Resources/img/smiley.ico");
    QIcon ButtonIcon(pixmap);
    smileyButton->setIcon(ButtonIcon);

    //stopping the clock
    clock->stoptTimer();

    //change the flag counter to 0
    flagCounter->display(0);

    //disable all the buttons
    for(int idx = 0; idx < gLayout->count(); idx++)
      {
        QWidget *item = gLayout->itemAt(idx)->widget();
        if(item !=NULL){
            if(item->isEnabled()){
                SpecialButton* button=dynamic_cast<SpecialButton*>(item);

                //set the flags to all the free positions
                if(button->text()==""){
                    QPixmap pixmap(":/Resources/img/flag.ico");
                    QIcon ButtonIcon(pixmap);
                    button->setIcon(ButtonIcon);
                }
            }
            item->setDisabled(true);
        }
    }
}

