#ifndef WIDGETSELECTNIC_H
#define WIDGETSELECTNIC_H

#include <QObject>
#include <QWidget>

class WidgetSelectNic : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSelectNic(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
signals:

};

#endif // WIDGETSELECTNIC_H
