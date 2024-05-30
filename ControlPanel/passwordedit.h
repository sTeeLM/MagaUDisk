#ifndef PASSWORDEDIT_H
#define PASSWORDEDIT_H

#include <QLineEdit>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>

class PasswordEdit : public QLineEdit
{
    Q_OBJECT
public:
    PasswordEdit(QWidget * parent = nullptr);
    ~PasswordEdit();

protected:
    void keyPressEvent(QKeyEvent * event);

};

#endif // PASSWORDEDIT_H
