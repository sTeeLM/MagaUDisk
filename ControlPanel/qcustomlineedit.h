#ifndef QCUSTOMLINEEDIT_H
#define QCUSTOMLINEEDIT_H

#include <QLineEdit>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class QCustomLineEditData;

class QCustomLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    QCustomLineEdit(QWidget * parent = nullptr);
    QCustomLineEdit(const QCustomLineEdit &);
    QCustomLineEdit &operator=(const QCustomLineEdit &);
    ~QCustomLineEdit();

protected:
    void keyPressEvent(QKeyEvent * event);
private:
    QSharedDataPointer<QCustomLineEditData> data;
};

#endif // QCUSTOMLINEEDIT_H
