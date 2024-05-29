#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controlapplication.h"
#include "threadpreparedevice.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentInterface(nullptr)
    , currentThread(nullptr)
{
    ui->setupUi(this);
    initilizeUI();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::threadFinised()
{
    qDebug()<<tr("MainWindow::threadFinised");
    delete currentThread;
    currentThread = nullptr;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(currentInterface == nullptr)
        return;
    qDebug() << tr("MainWindow::keyPressEvent") << currentInterface->objectName();

    if(currentInterface->objectName() == QString(tr("widgetGetPass"))) {


    }
}

void MainWindow::initilizeUI()
{
    ui->lineEdit->setEchoMode(QLineEdit::EchoMode::Password);
    ui->widgetGetPass->resize(130,130);
    ui->widgeMountSerial->resize(130,130);
    ui->widgetMain->resize(130,130);
    ui->widgetMountImage->resize(130,130);
    ui->widgetMountNic->resize(130,130);
    ui->widgetMountPart->resize(130,130);
    ui->widgetSelectImage->resize(130,130);

    showWidgetMountSerial(false);
    showWidgetMountImage(false);
    showWidgetMountNic(false);
    showWidgetMountPart(false);
    showWidgetSelectImage(false);
    showWidgetGetPass(false);
    showWidgetMain(false);

    if((qobject_cast<ControlApplication *>qApp)->config.isEncryptPart()) {
        showWidgetGetPass(true);
        currentInterface = ui->widgetGetPass;
    } else {
        ui->labelWaitInfo->setText(tr("正在准备分区"));
        showWidgetWait();
        currentInterface = ui->widgetWait;
        currentThread = new ThreadPrepareDevice;
        connect(currentThread, &QThread::finished, this, &MainWindow::threadFinised);
        currentThread->start();
    }
}

void MainWindow::showWidgetGetPass(bool show)
{
    ui->widgetGetPass->setEnabled(show);
    ui->widgetGetPass->setVisible(show);
}

void MainWindow::showWidgetMountSerial(bool show)
{
    ui->widgeMountSerial->setEnabled(show);
    ui->widgeMountSerial->setVisible(show);
}

void MainWindow::showWidgetMain(bool show)
{
    ui->widgetMain->setEnabled(show);
    ui->widgetMain->setVisible(show);
}

void MainWindow::showWidgetMountImage(bool show)
{
    ui->widgetMountImage->setEnabled(show);
    ui->widgetMountImage->setVisible(show);
}

void MainWindow::showWidgetMountNic(bool show)
{
    ui->widgetMountNic->setEnabled(show);
    ui->widgetMountNic->setVisible(show);
}

void MainWindow::showWidgetMountPart(bool show)
{
    ui->widgetMountPart->setEnabled(show);
    ui->widgetMountPart->setVisible(show);
}

void MainWindow::showWidgetSelectImage( bool show)
{
    ui->widgetSelectImage->setEnabled(show);
    ui->widgetSelectImage->setVisible(show);
}

void MainWindow::showWidgetWait(bool show)
{
    ui->widgetWait->setEnabled(show);
    ui->widgetWait->setVisible(show);
}
