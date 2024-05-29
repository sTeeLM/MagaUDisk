#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void initilizeUI();
    void showWidgetGetPass(bool show = true);
    void showWidgetMountSerial(bool show = true);
    void showWidgetMain(bool show = true);
    void showWidgetMountImage(bool show = true);
    void showWidgetMountNic(bool show = true);
    void showWidgetMountPart(bool show = true);
    void showWidgetSelectImage(bool show = true);
    void showWidgetWait(bool show = true);
    void threadFinised();
    Ui::MainWindow *ui;
    QWidget * currentInterface;
    QThread * currentThread;
};
#endif // MAINWINDOW_H
