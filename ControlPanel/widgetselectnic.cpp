#include "widgetselectnic.h"

#include <QDebug>
#include <QScrollBar>
#include <QTreeWidget>
#include <QKeyEvent>

WidgetSelectNic::WidgetSelectNic(QWidget *parent)
    : QWidget{parent}
{

}

void WidgetSelectNic::keyPressEvent(QKeyEvent *event)
{
    qDebug() << tr("WidgetSelectNic::keyPressEvent");
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        QScrollBar * bar = findChild<QTreeWidget *>("treeWidgetNic")->horizontalScrollBar();
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
