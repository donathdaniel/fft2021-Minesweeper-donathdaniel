#include "specialbutton.h"

SpecialButton::SpecialButton(QWidget* parent) : QPushButton(parent) {}

void SpecialButton::mousePressEvent(QMouseEvent *e)
{

    //case of right click of the mouse
    if(e->button()==Qt::RightButton){
        emit rightMouseButton();
    }
    //case of left click of the mouse
    if(e->button()==Qt::LeftButton){
        emit leftMouseButton();
    }
}

