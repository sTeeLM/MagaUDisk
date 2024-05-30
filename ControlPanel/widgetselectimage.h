#ifndef WIDGETSELECTIMAGE_H
#define WIDGETSELECTIMAGE_H

#include <QObject>
#include <QWidget>

class WidgetSelectImage : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSelectImage(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
signals:
};

#endif // WIDGETSELECTIMAGE_H
