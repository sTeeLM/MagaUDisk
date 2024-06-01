#include "widgetchangepassword.h"

#include <QDebug>
#include <QLineEdit>

WidgetChangePassword::WidgetChangePassword(QWidget *parent)
    : QWidget{parent}
{}


void WidgetChangePassword::keyPressEvent(QKeyEvent *event)
{
    QLineEdit * p[3];
    int focus = 0;

    qDebug() << tr("WidgetChangePassword::keyPressEvent");

    p[0] = findChild<QLineEdit *>("lineEditOldPassword");
    p[1] = findChild<QLineEdit *>("lineEditNewPassword");
    p[2] = findChild<QLineEdit *>("lineEditNewPasswordAgain");

    if(p[0]->hasFocus()) {
        focus = 0;
    } else if (p[1]->hasFocus()) {
        focus = 1;
    } else {
        focus = 2;
    }

    if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down) {
        if(event->key() == Qt::Key_Down)
            focus = (++focus) % 3;
        else {
            focus --;
            if(focus < 0) focus = 2;
        }
        p[focus]->setFocus();
    } else {
        QWidget::keyPressEvent(event);
    }
}
