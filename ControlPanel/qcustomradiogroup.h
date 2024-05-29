#ifndef QCUSTOMRADIOGROUP_H
#define QCUSTOMRADIOGROUP_H


#include <QObject>
#include <QWidget>
#include <QButtonGroup>
#include <QKeyEvent>

class QCustomRadioGroup : public QWidget
{
    Q_OBJECT
public:
    explicit QCustomRadioGroup(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    void InitilizeButtonGroup();
public:
    QButtonGroup mainFunctionGroup;
signals:
};

#endif // QCUSTOMRADIOGROUP_H
