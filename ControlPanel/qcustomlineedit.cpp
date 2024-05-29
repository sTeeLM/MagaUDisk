#include "qcustomlineedit.h"

#include <QDebug>

class QCustomLineEditData : public QSharedData
{
public:
};

QCustomLineEdit::QCustomLineEdit(QWidget * parent /* = nullptr */)
    : QLineEdit(parent),data(new QCustomLineEditData)
{}

QCustomLineEdit::QCustomLineEdit(const QCustomLineEdit &rhs)
    : data{rhs.data}
{}

QCustomLineEdit &QCustomLineEdit::operator=(const QCustomLineEdit &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}

QCustomLineEdit::~QCustomLineEdit()
{

}

void QCustomLineEdit::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Left) {
        QKeyEvent qev(QEvent::KeyPress, Qt::Key_Backspace,Qt::NoModifier);
        QLineEdit::keyPressEvent(&qev);
    } else if (event->key() == Qt::Key_Up) {
    } else {
        QLineEdit::keyPressEvent(event);
    }
    qDebug() << tr("keyPressEvent");
}

