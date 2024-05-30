#include "widgetselectimage.h"

#include <QDebug>

WidgetSelectImage::WidgetSelectImage(QWidget *parent)
    : QWidget{parent}
{

}

void WidgetSelectImage::keyPressEvent(QKeyEvent *event)
{
    qDebug() << tr("WidgetSelectImage::keyPressEvent");
    QWidget::keyPressEvent(event);
}
