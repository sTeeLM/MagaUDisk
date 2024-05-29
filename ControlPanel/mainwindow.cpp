#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controlapplication.h"
#include "threadpreparedevice.h"
#include "threadmountpartation.h"
#include "threadmountserial.h"
#include "threadmountnic.h"


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

void MainWindow::mountPartationDone()
{
    qDebug()<<tr("MainWindow::mountPartationDone");
}

void MainWindow::mountSerialDone()
{
    qDebug()<<tr("MainWindow::mountSerialDone");
}

void MainWindow::mountNicDone()
{
    qDebug()<<tr("MainWindow::mountNicDone");
}


void MainWindow::prepareDeviceDone()
{
    qDebug()<<tr("MainWindow::prepareDeviceDone");

    if(currentThread->isOK()) {
        showWidegt(WIDGET_MAIN);
    } else if(currentThread->getState() == StateThread::WRONG_PASS) {
        showWidegt(WIDGET_GET_PASS);
        ui->lineEditPassword->setFocus();
        ui->lineEditPassword->setText(tr(""));
    } else {
        ui->labelWaitInfo->setText(QString(tr("准备分区失败")) + currentThread->getStateString());
    }

    delete currentThread;
    currentThread = nullptr;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(currentInterface == nullptr)
        return;
    qDebug() << tr("MainWindow::keyPressEvent") << currentInterface->objectName() << event->key();

    if(event->key() != Qt::Key_Enter && event->key() != Qt::Key_Return) {
        QMainWindow::keyPressEvent(event);
    } else if(currentInterface->objectName() == QString(tr("widgetGetPass"))) {
        ui->labelWaitInfo->setText(tr("正在准备分区"));
        ThreadPrepareDevice * tempThread = new ThreadPrepareDevice;
        currentThread = tempThread;
        connect(currentThread, &QThread::finished, this, &MainWindow::prepareDeviceDone);
        tempThread->setEncrypted(ui->lineEditPassword->text());
        showWidegt(WIDGET_WAIT);
        currentThread->start();

    } else if(currentInterface->objectName() == QString(tr("widgetMain"))) {
        QCustomRadioGroup * buttonGroup = qobject_cast<QCustomRadioGroup *>(ui->widgetMain);
        switch(buttonGroup->mainFunctionGroup.checkedId()) {
        case 0: /* 装载单个镜像 */
            showWidegt(WIDGET_SELECT_IMAGE);
            break;
        case 1: /* 装载整分区 */
            currentThread = new ThreadMountPartation;
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::mountPartationDone);
            currentThread->start();
        case 2: /* 连接串口 */
            currentThread = new ThreadMountSerial;
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::mountSerialDone);
            currentThread->start();
        case 3: /* 模拟网卡 */
            currentThread = new ThreadMountNic;
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::mountNicDone);
            currentThread->start();
        case 4: /* 设置密码 */
        case 5: /* 其他功能 */
        }
    }
}

void MainWindow::initilizeUI()
{
    ui->lineEditPassword->setEchoMode(QLineEdit::EchoMode::Password);
    ui->widgetGetPass->resize(130,130);
    ui->widgetMountSerial->resize(130,130);
    ui->widgetMain->resize(130,130);
    ui->widgetMountImage->resize(130,130);
    ui->widgetMountNic->resize(130,130);
    ui->widgetMountPart->resize(130,130);
    ui->widgetSelectImage->resize(130,130);
    ui->widgetWait->resize(130,130);

    QCustomRadioGroup * buttonGroup = qobject_cast<QCustomRadioGroup *>(ui->widgetMain);
    buttonGroup->InitilizeButtonGroup();

    // 根据上次功能，选择用什么按钮
    ui->radioButtonSelectImage->setChecked(true);

    if((qobject_cast<ControlApplication *>qApp)->config.isEncryptPart()) {
        showWidegt(WIDGET_GET_PASS);
    } else {
        showWidegt(WIDGET_WAIT);
        ui->labelWaitInfo->setText(tr("正在准备分区"));
        currentThread = new ThreadPrepareDevice;
        connect(currentThread, &QThread::finished, this, &MainWindow::prepareDeviceDone);
        currentThread->start();
    }
}


void MainWindow::showWidegt(WIDGET_ID id)
{
    ui->widgetGetPass->setEnabled(id == WIDGET_GET_PASS);
    ui->widgetGetPass->setVisible(id == WIDGET_GET_PASS);

    ui->widgetMountSerial->setEnabled(id == WIDGET_MOUNT_SERIAL);
    ui->widgetMountSerial->setVisible(id == WIDGET_MOUNT_SERIAL);

    ui->widgetMain->setEnabled(id == WIDGET_MAIN);
    ui->widgetMain->setVisible(id == WIDGET_MAIN);
    if(id == WIDGET_MAIN) {
        ui->widgetMain->setFocus();
    }

    ui->widgetMountImage->setEnabled(id == WIDGET_MOUNT_IMAGE);
    ui->widgetMountImage->setVisible(id == WIDGET_MOUNT_IMAGE);

    ui->widgetMountNic->setEnabled(id == WIDGET_MOUNT_NIC);
    ui->widgetMountNic->setVisible(id == WIDGET_MOUNT_NIC);

    ui->widgetMountPart->setEnabled(id == WIDGET_MOUNT_PART);
    ui->widgetMountPart->setVisible(id == WIDGET_MOUNT_PART);

    ui->widgetSelectImage->setEnabled(id == WIDGET_SELECT_IMAGE);
    ui->widgetSelectImage->setVisible(id == WIDGET_SELECT_IMAGE);

    ui->widgetWait->setEnabled(id == WIDGET_WAIT);
    ui->widgetWait->setVisible(id == WIDGET_WAIT);

    switch(id) {
    case WIDGET_GET_PASS:
        currentInterface = ui->widgetGetPass;
        break;
    case WIDGET_MOUNT_SERIAL:
        currentInterface = ui->widgetMountSerial;
        break;
    case WIDGET_MAIN:
        currentInterface = ui->widgetMain;
        break;
    case WIDGET_MOUNT_IMAGE:
        currentInterface = ui->widgetMountImage;
        break;
    case WIDGET_MOUNT_NIC:
        currentInterface = ui->widgetMountNic;
        break;
    case WIDGET_MOUNT_PART:
        currentInterface = ui->widgetMountPart;
        break;
    case WIDGET_SELECT_IMAGE:
        currentInterface = ui->widgetSelectImage;
        break;
    case WIDGET_WAIT:
        currentInterface = ui->widgetWait;
        break;
    default:
        currentInterface  = nullptr;
    }
}


