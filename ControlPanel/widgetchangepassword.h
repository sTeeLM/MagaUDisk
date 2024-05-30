#ifndef WIDGETCHANGEPASSWORD_H
#define WIDGETCHANGEPASSWORD_H

#include <QObject>
#include <QWidget>
#include <QKeyEvent>

class WidgetChangePassword : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetChangePassword(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
signals:
};

#endif // WIDGETCHANGEPASSWORD_H
