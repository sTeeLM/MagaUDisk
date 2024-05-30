#ifndef RADIOGROUP_H
#define RADIOGROUP_H


#include <QObject>
#include <QWidget>
#include <QButtonGroup>
#include <QKeyEvent>

class RadioGroup : public QWidget
{
    Q_OBJECT
public:
    explicit RadioGroup(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void InitilizeButtonGroup();
public:
    QButtonGroup mainFunctionGroup;
signals:
};

#endif // RADIOGROUP_H
