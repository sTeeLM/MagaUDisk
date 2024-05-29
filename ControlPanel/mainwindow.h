#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "statethread.h"

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

private:
    enum WIDGET_ID {
        WIDGET_GET_PASS = 0,
        WIDGET_MOUNT_SERIAL,
        WIDGET_MAIN,
        WIDGET_MOUNT_IMAGE,
        WIDGET_MOUNT_NIC,
        WIDGET_MOUNT_PART,
        WIDGET_SELECT_IMAGE,
        WIDGET_WAIT
    };

    void initilizeUI();

    void showWidegt(WIDGET_ID id);

    void prepareDeviceDone();
    void mountPartationDone();
    void mountSerialDone();
    void mountNicDone();

    Ui::MainWindow *ui;
    QWidget * currentInterface;
    StateThread * currentThread;
};
#endif // MAINWINDOW_H
