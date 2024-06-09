#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "statethreadbase.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *event);

public:
    enum WIDGET_ID {
        WIDGET_NONE = -1,
        WIDGET_GET_PASS = 0,
        WIDGET_MAIN,
        WIDGET_MOUNT_SERIAL,
        WIDGET_MOUNT_BLOCK,
        WIDGET_MOUNT_NIC,
        WIDGET_SELECT_IMAGE,
        WIDGET_SELECT_NIC,
        WIDGET_WAIT,
        WIDGET_CHANGE_PASSWORD,
        WIDGET_RESULT
    };

private:
    void initilizeUI();

    void showWidegt(WIDGET_ID id, WIDGET_ID idJump = WIDGET_NONE);

    void listNicDone();
    void listImageDone();
    void prepareDeviceDone();
    void mountPartationDone();
    void mountSerialDone();
    void mountNicDone();
    void mountImageDone();
    void changePasswordDone();
    void clossDeviceDone();

    Ui::MainWindow *ui;
    QWidget * currentInterface;
    StateThreadBase * currentThread;
};
#endif // MAINWINDOW_H
