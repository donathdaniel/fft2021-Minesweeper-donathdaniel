#include "specialbutton.h"

SpecialButton::SpecialButton(QWidget* parent) : QPushButton(parent) {}

void SpecialButton::mousePressEvent(QMouseEvent *e)
{

    if(e->button()==Qt::RightButton){
        emit rightMouseButton();
    }
    if(e->button()==Qt::LeftButton){
        emit leftMouseButton();
    }
}
