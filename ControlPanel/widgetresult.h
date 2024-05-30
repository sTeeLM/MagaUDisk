#ifndef WIDGETRESULT_H
#define WIDGETRESULT_H

#include "mainwindow.h"

#include <QObject>
#include <QWidget>

class WidgetResult : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetResult(QWidget *parent = nullptr);
    void setJumpWidget(MainWindow::WIDGET_ID jump)
    {
        jumpWidget = jump;
    }
    MainWindow::WIDGET_ID getJumpWidget()
    {
        return jumpWidget;
    }
private:
    MainWindow::WIDGET_ID  jumpWidget;
signals:
};

#endif // WIDGETRESULT_H
