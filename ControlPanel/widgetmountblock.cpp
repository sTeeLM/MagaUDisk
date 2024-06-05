#include "widgetmountblock.h"
#include <QtDebug>
#include <QKeyEvent>
#include <QListWidget>
#include <QScrollBar>

WidgetMountBlock::WidgetMountBlock(QWidget *parent)
    : QWidget(parent)
    , mountImage(false)
{

}


void WidgetMountBlock::keyPressEvent(QKeyEvent *event)
{
    qDebug() << tr("WidgetMountBlock::keyPressEvent");
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        QScrollBar * bar = findChild<QListWidget *>("listWidgetBlockInfo")->horizontalScrollBar();
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
}
