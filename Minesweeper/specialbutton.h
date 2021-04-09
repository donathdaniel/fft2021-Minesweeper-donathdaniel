#ifndef SPECIALBUTTON_H
#define SPECIALBUTTON_H

#include <QMouseEvent>
#include <QPushButton>

class SpecialButton : public QPushButton
{
    Q_OBJECT
    //defining a special button which have different behaviour for right and left click
public:
   SpecialButton(QWidget* parent=nullptr);

public slots:
    void mousePressEvent(QMouseEvent *) override;

signals:
   void leftMouseButton();
   void rightMouseButton();
};

#endif // SPECIALBUTTON_H

