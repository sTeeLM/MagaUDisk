#include "passwordedit.h"

#include <QDebug>


PasswordEdit::PasswordEdit(QWidget * parent /* = nullptr */)
    : QLineEdit(parent)
{}


PasswordEdit::~PasswordEdit()
{

}


void PasswordEdit::keyPressEvent(QKeyEvent * event)
{
    qDebug() << tr("PasswordEdit::keyPressEvent");
    if(event->key() == Qt::Key_Left) {
        QKeyEvent qev(QEvent::KeyPress, Qt::Key_Backspace,Qt::NoModifier);
        QLineEdit::keyPressEvent(&qev);
    } else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down) {
        QWidget::keyPressEvent(event);
    } else {
        QLineEdit::keyPressEvent(event);
    }

}

