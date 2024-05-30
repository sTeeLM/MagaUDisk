#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadpreparedevice.h"
#include "threadmountpartation.h"
#include "threadmountserial.h"
#include "threadmountnic.h"
#include "threadlistimage.h"
#include "threadchangepassword.h"
#include "threadmountimage.h"
#include "widgetresult.h"

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

void MainWindow::listImageDone()
{
    qDebug()<<tr("MainWindow::listImageDone");
    if(currentThread->isStateOK()) {
        showWidegt(WIDGET_SELECT_IMAGE);
        ui->listWidgetImage->item(0)->setSelected(true);
        ui->listWidgetImage->setFocus();
    }
    delete currentThread;
    currentThread = nullptr;
}


void MainWindow::mountImageDone()
{
    qDebug()<<tr("MainWindow::mountImageDone");

    ThreadMountImage * thread = qobject_cast<ThreadMountImage *>(currentThread);

    if(thread->isMount()) {
        if(currentThread->isStateOK()) {
            showWidegt(WIDGET_MOUNT_PART);
        } else {
            showWidegt(WIDGET_RESULT, WIDGET_MAIN);
            ui->labelResultTitle->setText(currentThread->getStateString());
            ui->labelResultInfo->setText(currentThread->getExtra());
        }
    } else {
        if(currentThread->isStateOK()) {
            showWidegt(WIDGET_MAIN);
        } else {
            showWidegt(WIDGET_RESULT, WIDGET_MAIN);
            ui->labelResultTitle->setText(currentThread->getStateString());
            ui->labelResultInfo->setText(currentThread->getExtra());
        }
    }

    delete currentThread;
    currentThread = nullptr;
}

void MainWindow::mountPartationDone()
{
    qDebug()<<tr("MainWindow::mountPartationDone");

    ThreadMountPartation * thread = qobject_cast<ThreadMountPartation *>(currentThread);

    if(thread->isMount()) {
        if(currentThread->isStateOK()) {
            showWidegt(WIDGET_MOUNT_PART);
        } else {
            showWidegt(WIDGET_RESULT, WIDGET_MAIN);
            ui->labelResultTitle->setText(currentThread->getStateString());
            ui->labelResultInfo->setText(currentThread->getExtra());
        }
    } else {
        if(currentThread->isStateOK()) {
            showWidegt(WIDGET_MAIN);
        } else {
            showWidegt(WIDGET_RESULT, WIDGET_MAIN);
            ui->labelResultTitle->setText(currentThread->getStateString());
            ui->labelResultInfo->setText(currentThread->getExtra());
        }
    }

    delete currentThread;
    currentThread = nullptr;

}

void MainWindow::mountSerialDone()
{
    qDebug()<<tr("MainWindow::mountSerialDone");

    ThreadMountSerial * thread = qobject_cast<ThreadMountSerial *>(currentThread);

    if(thread->isMount()) {
        if(currentThread->isStateOK()) {
            showWidegt(WIDGET_MOUNT_SERIAL);
        } else {
            showWidegt(WIDGET_RESULT, WIDGET_MAIN);
            ui->labelResultTitle->setText(currentThread->getStateString());
            ui->labelResultInfo->setText(currentThread->getExtra());
        }
    } else {
        if(currentThread->isStateOK()) {
            showWidegt(WIDGET_MAIN);
        } else {
            showWidegt(WIDGET_RESULT, WIDGET_MAIN);
            ui->labelResultTitle->setText(currentThread->getStateString());
            ui->labelResultInfo->setText(currentThread->getExtra());
        }
    }

    delete currentThread;
    currentThread = nullptr;
}

void MainWindow::mountNicDone()
{
    qDebug()<<tr("MainWindow::mountNicDone");

    ThreadMountNic * thread = qobject_cast<ThreadMountNic *>(currentThread);

    if(thread->isMount()) {
        if(currentThread->isStateOK()) {
            showWidegt(WIDGET_MOUNT_NIC);
        } else {
            showWidegt(WIDGET_RESULT, WIDGET_MAIN);
            ui->labelResultTitle->setText(currentThread->getStateString());
            ui->labelResultInfo->setText(currentThread->getExtra());
        }
    } else {
        if(currentThread->isStateOK()) {
            showWidegt(WIDGET_MAIN);
        } else {
            showWidegt(WIDGET_RESULT, WIDGET_MAIN);
            ui->labelResultTitle->setText(currentThread->getStateString());
            ui->labelResultInfo->setText(currentThread->getExtra());
        }
    }

    delete currentThread;
    currentThread = nullptr;
}


void MainWindow::prepareDeviceDone()
{
    qDebug()<<tr("MainWindow::prepareDeviceDone");

    if(currentThread->isStateOK()) {
        showWidegt(WIDGET_MAIN);
    } else if(currentThread->getState() == StateThreadBase::WRONG_PASS) {
        showWidegt(WIDGET_GET_PASS);
        ui->lineEditPassword->setFocus();
        ui->lineEditPassword->setText(tr(""));
    } else {
        showWidegt(WIDGET_RESULT, WIDGET_GET_PASS);
        ui->labelResultTitle->setText(QString(tr("准备分区失败")));
        ui->labelResultInfo->setText(currentThread->getStateString());
    }

    delete currentThread;
    currentThread = nullptr;
}

void MainWindow::changePasswordDone()
{
    qDebug()<<tr("MainWindow::changePasswordDone");
    if(currentThread->isStateOK()) {
        showWidegt(WIDGET_MAIN);
    } else {
        showWidegt(WIDGET_RESULT, WIDGET_CHANGE_PASSWORD);
        ui->lineEditOldPassword->setText(tr(""));
        ui->lineEditNewPassword->setText(tr(""));
        ui->lineEditNewPasswordAgain->setText(tr(""));
        ui->labelResultTitle->setText(QString(tr("修改密码失败")));
        ui->labelResultInfo->setText(currentThread->getStateString());
    }
    delete currentThread;
    currentThread = nullptr;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(currentInterface == nullptr)
        return;
    qDebug() << tr("MainWindow::keyPressEvent") << currentInterface->objectName() << event->key();

    if(event->key() != Qt::Key_Enter
        && event->key() != Qt::Key_Return
        && event->key() != Qt::Key_Left) {
        QMainWindow::keyPressEvent(event);
        return;
    }

    /* 在获得密码界面按回车 */
    if(currentInterface->objectName() == QString(tr("widgetGetPass"))
        && (event->key() != Qt::Key_Enter || event->key() != Qt::Key_Return)) {
        ui->labelWaitInfo->setText(tr("正在准备分区"));
        currentThread = new ThreadPrepareDevice(this, ui->lineEditPassword->text());
        connect(currentThread, &QThread::finished, this, &MainWindow::prepareDeviceDone);
        showWidegt(WIDGET_WAIT);
        currentThread->start();

    /* 在主界面选择功能 */
    } else if(currentInterface->objectName() == QString(tr("widgetMain"))
        && (event->key() != Qt::Key_Enter || event->key() != Qt::Key_Return)) {
        RadioGroup * buttonGroup = qobject_cast<RadioGroup *>(ui->widgetMain);
        switch(buttonGroup->mainFunctionGroup.checkedId()) {
        case 0: /* 装载单个镜像 */
            currentThread = new ThreadListImage(this, ui->listWidgetImage);
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::listImageDone);
            currentThread->start();
            break;
        case 1: /* 装载整分区 */
            currentThread = new ThreadMountPartation(this);
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::mountPartationDone);
            currentThread->start();
            break;
        case 2: /* 连接串口 */
            currentThread = new ThreadMountSerial(this);
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::mountSerialDone);
            currentThread->start();
            break;
        case 3: /* 模拟网卡 */
            currentThread = new ThreadMountNic(this);
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::mountNicDone);
            currentThread->start();
            break;
        case 4: /* 修改密码 */
            showWidegt(WIDGET_CHANGE_PASSWORD);
            /*
            currentThread = new ThreadChangePassword(this);
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::changePasswordDone);
            currentThread->start();
            */
        }
    /* 在连接串口界面关闭串口 */
    } else if(currentInterface->objectName() == QString(tr("widgetMountSerial"))
        && (event->key() != Qt::Key_Enter || event->key() != Qt::Key_Return)) {
        currentThread = new ThreadMountSerial(this, false);
        showWidegt(WIDGET_WAIT);
        connect(currentThread, &QThread::finished, this, &MainWindow::mountSerialDone);
        currentThread->start();

    /* 在装载整分区界面关闭分区 */
    } else if(currentInterface->objectName() == QString(tr("widgetMountPart"))
        && (event->key() != Qt::Key_Enter || event->key() != Qt::Key_Return)) {
        currentThread = new ThreadMountPartation(this, false);
        showWidegt(WIDGET_WAIT);
        connect(currentThread, &QThread::finished, this, &MainWindow::mountPartationDone);
        currentThread->start();

    /* 在装载单个镜像界面关闭镜像 */
    } else if(currentInterface->objectName() == QString(tr("widgetMountImage"))
        && (event->key() != Qt::Key_Enter || event->key() != Qt::Key_Return)) {
        currentThread = new ThreadMountImage(this, false);
        showWidegt(WIDGET_WAIT);
        connect(currentThread, &QThread::finished, this, &MainWindow::mountImageDone);
        currentThread->start();

    /* 在模拟网卡界面关闭网卡 */
    } else if(currentInterface->objectName() == QString(tr("widgetMountNic"))
        && (event->key() != Qt::Key_Enter || event->key() != Qt::Key_Return)) {
        currentThread = new ThreadMountNic(this, false);
        showWidegt(WIDGET_WAIT);
        connect(currentThread, &QThread::finished, this, &MainWindow::mountNicDone);
        currentThread->start();

    /* 在选择镜像界面选择一个item */
    } else if(currentInterface->objectName() == QString(tr("widgetSelectImage"))) {


    /* 在修改密码界面按回车 */
    } else if(currentInterface->objectName() == QString(tr("widgetChangePassword"))
        && (event->key() != Qt::Key_Enter || event->key() != Qt::Key_Return)) {
        currentThread = new ThreadChangePassword(this,
                                                 ui->lineEditOldPassword->text(),
                                                 ui->lineEditNewPassword->text(),
                                                 ui->lineEditNewPasswordAgain->text());
        showWidegt(WIDGET_WAIT);
        connect(currentThread, &QThread::finished, this, &MainWindow::changePasswordDone);
        currentThread->start();
    /* 在结果界面按下回车 */
    } else if(currentInterface->objectName() == QString(tr("widgetResult"))
        && (event->key() != Qt::Key_Enter || event->key() != Qt::Key_Return)) {
        WidgetResult * res = qobject_cast<WidgetResult *>(currentInterface);
        showWidegt(res->getJumpWidget());
        res->setJumpWidget(WIDGET_NONE);
    }
}

void MainWindow::initilizeUI()
{
    ui->lineEditPassword->setEchoMode(QLineEdit::EchoMode::Password);
    ui->lineEditOldPassword->setEchoMode(QLineEdit::EchoMode::Password);
    ui->lineEditNewPassword->setEchoMode(QLineEdit::EchoMode::Password);
    ui->lineEditNewPasswordAgain->setEchoMode(QLineEdit::EchoMode::Password);

    ui->widgetGetPass->resize(130,130);
    ui->widgetMountSerial->resize(130,130);
    ui->widgetMain->resize(130,130);
    ui->widgetMountImage->resize(130,130);
    ui->widgetMountNic->resize(130,130);
    ui->widgetMountPart->resize(130,130);
    ui->widgetSelectImage->resize(130,130);
    ui->widgetWait->resize(130,130);
    ui->widgetChangePassword->resize(130,130);
    ui->widgetResult->resize(130,130);

    ui->listWidgetImage->setViewMode(QListView::ListMode);

    RadioGroup * buttonGroup = qobject_cast<RadioGroup *>(ui->widgetMain);
    buttonGroup->InitilizeButtonGroup();

    // 根据上次功能，选择用什么按钮
    ui->radioButtonSelectImage->setChecked(true);

    showWidegt(WIDGET_GET_PASS);
}


void MainWindow::showWidegt(WIDGET_ID id, WIDGET_ID idJump)
{
    WidgetResult * res = nullptr;
    ui->widgetGetPass->setEnabled(id == WIDGET_GET_PASS);
    ui->widgetGetPass->setVisible(id == WIDGET_GET_PASS);
    if(id == WIDGET_GET_PASS) {
        ui->lineEditPassword->setFocus();
    }

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
    if(id == WIDGET_SELECT_IMAGE) {
        ui->listWidgetImage->setFocus();
    }

    ui->widgetWait->setEnabled(id == WIDGET_WAIT);
    ui->widgetWait->setVisible(id == WIDGET_WAIT);

    ui->widgetChangePassword->setEnabled(id == WIDGET_CHANGE_PASSWORD);
    ui->widgetChangePassword->setVisible(id == WIDGET_CHANGE_PASSWORD);
    if(id == WIDGET_CHANGE_PASSWORD) {
        ui->lineEditOldPassword->setFocus();
    }

    ui->widgetResult->setEnabled(id == WIDGET_RESULT);
    ui->widgetResult->setVisible(id == WIDGET_RESULT);

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
    case WIDGET_CHANGE_PASSWORD:
        currentInterface = ui->widgetChangePassword;
        break;
    case WIDGET_RESULT:
        currentInterface = ui->widgetResult;
        res = qobject_cast<WidgetResult *>(currentInterface);
        res->setJumpWidget(idJump);
        break;
    case WIDGET_NONE:
    default:
        currentInterface  = nullptr;
    }

}


