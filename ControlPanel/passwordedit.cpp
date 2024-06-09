#include "passwordedit.h"

#include <QDebug>


PasswordEdit::PasswordEdit(QWidget * parent /* = nullptr */)
    : QLineEdit(parent)
{}


PasswordEdit::~PasswordEdit()
{

}

#define CHAR_BEGIN 0x21 /* ! */
#define CHAR_END   0x7E /* ~ */

void PasswordEdit::keyPressEvent(QKeyEvent * event)
{
    qDebug() << tr("PasswordEdit::keyPressEvent");

    if(event->key() == Qt::Key_Left) {
        QKeyEvent qev(QEvent::KeyPress, Qt::Key_Backspace,Qt::NoModifier);
        QLineEdit::keyPressEvent(&qev);
    } else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_Down) {
        QWidget::keyPressEvent(event);
    } else if(event->key() == Qt::Key_A || event->key() == Qt::Key_B || event->key() == Qt::Key_C){
        QString strBuffer = this->text();
        bool skip = false;
        if(!strBuffer.length()) {
            strBuffer += QChar('A');
            skip = true;
        }
        char lastChar = strBuffer.right(1).at(0).unicode();

        if(event->key() == Qt::Key_A) { /* page up a char*/
            if(!skip) {
                lastChar = lastChar -1;
                if(lastChar < CHAR_BEGIN) {
                    lastChar = CHAR_END;
                }
                strBuffer.replace(strBuffer.size() - 1, 1, QChar(lastChar));
            }
        } else if(event->key() == Qt::Key_B){ /* next char */
            if(strBuffer.length() < 6) {
                if(!skip) {
                    strBuffer += QChar('A');
                }
            }
        } else { /* page down a char */
            if(!skip) {
                lastChar = lastChar +1;
                if(lastChar > CHAR_END) {
                    lastChar = CHAR_BEGIN;
                }
                strBuffer.replace(strBuffer.size() - 1, 1, QChar(lastChar));
            }
        }
        this->setText(strBuffer);
    } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
        QLineEdit::keyPressEvent(event);
    }
    /* else {
        QLineEdit::keyPressEvent(event);
    } */
}

