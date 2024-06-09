#ifndef WIDGETGETPASSWORD_H
#define WIDGETGETPASSWORD_H

#include <QObject>
#include <QWidget>

class WidgetGetPassword : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetGetPassword(QWidget *parent = nullptr, bool prepare = true);

    bool isPrepare()
    {
        return prepare;
    }

    void setPrepare(bool v = true)
    {
        prepare = v;
    }

private:
    bool prepare;
signals:

};

#endif // WIDGETGETPASSWORD_H
