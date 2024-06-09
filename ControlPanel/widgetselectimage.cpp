#include "widgetselectimage.h"

#include <QDebug>
#include <QScrollBar>
#include <QListWidget>
#include <QKeyEvent>

WidgetSelectImage::WidgetSelectImage(QWidget *parent)
    : QWidget(parent)
    , currentPath(tr("/"))
{

}

void WidgetSelectImage::keyPressEvent(QKeyEvent *event)
{
    qDebug() << tr("WidgetSelectImage::keyPressEvent");
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        QScrollBar * bar = findChild<QListWidget *>("listWidgetImage")->horizontalScrollBar();
        if(bar) {
            int curValue = bar->value();
            int minValue = bar->minimum();
            int maxValue = bar->maximum();
            int stepValue = bar->singleStep();
            if(event->key() == Qt::Key_Left) {
                curValue -= stepValue;
                if(curValue < minValue) {
                    curValue = minValue;
                }
            } else {
                curValue += stepValue;
                if(curValue > maxValue) {
                    curValue = maxValue;
                }
            }
            bar->setValue(curValue);
        } else {
            QWidget::keyPressEvent(event);
        }
    } else {
        QWidget::keyPressEvent(event);
    }
}
