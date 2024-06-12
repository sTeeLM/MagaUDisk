#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "threadpreparedevice.h"
#include "threadmountserial.h"
#include "threadmountnic.h"
#include "threadlistimage.h"
#include "threadchangepassword.h"
#include "threadmountimage.h"
#include "threadmountpartation.h"
#include "threadlistnic.h"
#include "widgetresult.h"
#include "widgetmountblock.h"
#include "widgetgetpassword.h"

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
        if(ui->listWidgetImage->count()) {
            ui->listWidgetImage->item(0)->setSelected(true);
            ui->listWidgetImage->setFocus();
        }
    }
    delete currentThread;
    currentThread = nullptr;
}

void MainWindow::listNicDone()
{
    qDebug()<<tr("MainWindow::listNicDone");
    if(currentThread->isStateOK()) {
        showWidegt(WIDGET_SELECT_NIC);
        if(ui->treeWidgetNic->currentItem()) {
            ui->treeWidgetNic->currentItem()->setSelected(true);
            ui->treeWidgetNic->setFocus();
        }
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
            ui->widgetMountBlock->setMountImage(true);
            ui->listWidgetBlockInfo->clear();
            for( int i = 0 ; i < thread->getBlockInfo().size() ; i ++) {
                ui->listWidgetBlockInfo->addItem(thread->getBlockInfo().at(i));
            }
            showWidegt(WIDGET_MOUNT_BLOCK);
        } else {
            showWidegt(WIDGET_RESULT, WIDGET_MAIN);
            ui->labelResultTitle->setText(currentThread->getStateString());
            ui->labelResultInfo->setText(currentThread->getExtra());
        }
    } else {
        if(currentThread->isStateOK()) {
            showWidegt(WIDGET_SELECT_IMAGE);
        } else {
            showWidegt(WIDGET_RESULT, WIDGET_SELECT_IMAGE);
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
            ui->widgetMountBlock->setMountImage(false);
            ui->listWidgetBlockInfo->clear();
            for( int i = 0 ; i < thread->getBlockInfo().size() ; i ++) {
                ui->listWidgetBlockInfo->addItem(thread->getBlockInfo().at(i));
            }
            if(thread->getBlockInfo().size()) {
                ui->listWidgetBlockInfo->item(0)->setSelected(true);
                ui->listWidgetBlockInfo->setFocus();
            }
            showWidegt(WIDGET_MOUNT_BLOCK);
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
    } else {
        showWidegt(WIDGET_RESULT, WIDGET_GET_PASS);
        ui->lineEditPassword->setText("");
        ui->widgetGetPass->setPrepare();
        ui->labelResultTitle->setText(currentThread->getStateString());
        ui->labelResultInfo->setText(currentThread->getExtra());
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
        ui->lineEditOldPassword->setText("");
        ui->lineEditNewPassword->setText("");
        ui->lineEditNewPasswordAgain->setText("");
        ui->labelResultTitle->setText(currentThread->getStateString());
        ui->labelResultInfo->setText(currentThread->getExtra());
    }
    delete currentThread;
    currentThread = nullptr;
}

void MainWindow::clossDeviceDone()
{
    qDebug()<<tr("MainWindow::clossDeviceDone");
    if(currentThread->isStateOK()) {
        ui->lineEditPassword->setText("");
        ui->widgetGetPass->setPrepare();
        showWidegt(WIDGET_GET_PASS);
    } else {
        ui->lineEditPassword->setText("");
        ui->widgetGetPass->setPrepare();
        showWidegt(WIDGET_RESULT, WIDGET_GET_PASS);
        ui->labelResultTitle->setText(currentThread->getStateString());
        ui->labelResultInfo->setText(currentThread->getExtra());
    }
    delete currentThread;
    currentThread = nullptr;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(currentInterface == nullptr)
        return;
    qDebug() << tr("MainWindow::keyPressEvent") << currentInterface->objectName() << event->key();

    if(event->key() != Qt::Key_Enter && event->key() != Qt::Key_Return
            && event->key() != Qt::Key_Left && event->key() != Qt::Key_Right) {
        QMainWindow::keyPressEvent(event);
        return;
    }

    /* 在获得密码界面按回车 */
    if(currentInterface->objectName() == QString("widgetGetPass")
        && (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)) {
        WidgetGetPassword * p = qobject_cast<WidgetGetPassword *>(currentInterface);
        if(p->isPrepare()) {
            currentThread = new ThreadPrepareDevice(this, ui->lineEditPassword->text());
            connect(currentThread, &QThread::finished, this, &MainWindow::prepareDeviceDone);
            ui->labelWaitInfo->setText("正在准备分区");
            showWidegt(WIDGET_WAIT);
            currentThread->start();
        } else {
            if(ui->treeWidgetNic->selectedItems().size()) {
                NicItem * item = static_cast<NicItem *>(ui->treeWidgetNic->selectedItems().at(0));
                currentThread = new ThreadMountNic(this, true, item, ui->lineEditPassword->text());
                connect(currentThread, &QThread::finished, this, &MainWindow::mountNicDone);
                ui->labelWaitInfo->setText("正在链接网卡");
                showWidegt(WIDGET_WAIT);
                currentThread->start();
            }
        }
    /* 在主界面选择功能 */
    } else if(currentInterface->objectName() == QString("widgetMain")
        && (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)) {
        RadioGroup * buttonGroup = qobject_cast<RadioGroup *>(ui->widgetMain);
        switch(buttonGroup->mainFunctionGroup.checkedId()) {
        case 0: /* 装载单个镜像 */
            currentThread = new ThreadListImage(this, ui->listWidgetImage, ui->widgetSelectImage->getCurrentPath());
            ui->labelWaitInfo->setText("正在枚举镜像");
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::listImageDone);
            currentThread->start();
            break;
        case 1: /* 装载整分区 */
            currentThread = new ThreadMountPartation(this);
            ui->labelWaitInfo->setText("正在装载分区");
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::mountPartationDone);
            currentThread->start();
            break;
        case 2: /* 连接串口 */
            currentThread = new ThreadMountSerial(this);
            ui->labelWaitInfo->setText("正在连接串口");
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::mountSerialDone);
            currentThread->start();
            break;
        case 3: /* 模拟网卡 */
            currentThread = new ThreadListNic(this, ui->treeWidgetNic);
            ui->labelWaitInfo->setText("正在探测WIFI");
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::listNicDone);
            currentThread->start();
            break;
        case 4: /* 修改密码 */
            ui->lineEditOldPassword->setText("");
            ui->lineEditNewPassword->setText("");
            ui->lineEditNewPasswordAgain->setText("");
            showWidegt(WIDGET_CHANGE_PASSWORD);
            break;
        case 5: /* 关闭设备 */
            currentThread = new ThreadPrepareDevice(this, {}, false);
            connect(currentThread, &QThread::finished, this, &MainWindow::clossDeviceDone);
            ui->labelWaitInfo->setText("正在关闭设备");
            showWidegt(WIDGET_WAIT);
            currentThread->start();
        }
    /* 在连接串口界面关闭串口 */
    } else if(currentInterface->objectName() == QString("widgetMountSerial")
        && (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)) {
        currentThread = new ThreadMountSerial(this, false);
        ui->labelWaitInfo->setText("正在关闭串口");
        showWidegt(WIDGET_WAIT);
        connect(currentThread, &QThread::finished, this, &MainWindow::mountSerialDone);
        currentThread->start();
    /* 在装载整分区界面/装载单个镜像界面关闭镜像 */
    } else if(currentInterface->objectName() == QString("widgetMountBlock")
        && (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)) {
        if(ui->widgetMountBlock->getMountImage()) {
            currentThread = new ThreadMountImage(this, false);
            ui->labelWaitInfo->setText("正在关闭镜像");
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::mountImageDone);
            currentThread->start();
        } else {
            currentThread = new ThreadMountPartation(this, false);
            ui->labelWaitInfo->setText("正在关闭分区");
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::mountPartationDone);
            currentThread->start();
        }
    /* 在模拟网卡界面关闭网卡 */
    } else if(currentInterface->objectName() == QString("widgetMountNic")
        && (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)) {
        currentThread = new ThreadMountNic(this, false);
        ui->labelWaitInfo->setText("正在关闭网卡");
        showWidegt(WIDGET_WAIT);

        connect(currentThread, &QThread::finished, this, &MainWindow::mountNicDone);
        currentThread->start();

    /* 在选择镜像界面选择一个item */
    } else if((currentInterface->objectName() == QString("widgetSelectImage"))
              && (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)) {
        QListWidgetItem * item = nullptr;
        if(ui->listWidgetImage->selectedItems().length()) {
            item = ui->listWidgetImage->selectedItems()[0];
        }
        QString currentPath = ui->widgetSelectImage->getCurrentPath();
        if(item && item->type() == 0) { // is an folder
            QString currentPath;
            if(item->text() != QString("..")) {
                currentPath = ui->widgetSelectImage->pushPath(item->text());
            } else {
                if(ui->widgetSelectImage->getCurrentPath() != QString("/")) {
                    currentPath = ui->widgetSelectImage->popPath();
                } else {
                    currentPath = "";
                }
            }
            if(currentPath.length()) {
                currentThread = new ThreadListImage(this, ui->listWidgetImage, currentPath);
                ui->labelWaitInfo->setText("正在打开目录");
                showWidegt(WIDGET_WAIT);
                connect(currentThread, &QThread::finished, this, &MainWindow::listImageDone);
                currentThread->start();
            } else {
                showWidegt(WIDGET_MAIN);
            }
        } else if(item && item->type() == 1) { // is a image
            if(currentPath.right(1) != QChar('/')) {
                currentPath += "/";
            }
            currentPath += item->text();
            currentThread = new ThreadMountImage(this, true, currentPath);
            ui->labelWaitInfo->setText("正在装载镜像");
            showWidegt(WIDGET_WAIT);
            connect(currentThread, &QThread::finished, this, &MainWindow::mountImageDone);
            currentThread->start();
        }
     /* 选择链接一个WIFI */
    } else if((currentInterface->objectName() == QString("widgetSelectNic"))
              && (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)) {
        ui->widgetGetPass->setPrepare(false);
        ui->lineEditPassword->setText("");
        showWidegt(WIDGET_GET_PASS);
    /* 在修改密码界面按回车 */
    } else if(currentInterface->objectName() == QString("widgetChangePassword")
        && (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)) {
        currentThread = new ThreadChangePassword(this,
                                                 ui->lineEditOldPassword->text(),
                                                 ui->lineEditNewPassword->text(),
                                                 ui->lineEditNewPasswordAgain->text());
        ui->labelWaitInfo->setText("正在修改密码");
        showWidegt(WIDGET_WAIT);
        connect(currentThread, &QThread::finished, this, &MainWindow::changePasswordDone);
        currentThread->start();
    /* 在结果界面按下回车 */
    } else if(currentInterface->objectName() == QString("widgetResult")
        && (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)) {
        WidgetResult * res = qobject_cast<WidgetResult *>(currentInterface);
        showWidegt(res->getJumpWidget());
        res->setJumpWidget(WIDGET_NONE);
    }
}

void MainWindow::initilizeUI()
{

    /*
    ui->lineEditPassword->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);
    ui->lineEditOldPassword->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);
    ui->lineEditNewPassword->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);
    ui->lineEditNewPasswordAgain->setEchoMode(QLineEdit::EchoMode::PasswordEchoOnEdit);
    */

    ui->widgetGetPass->resize(130,130);
    ui->widgetMountSerial->resize(130,130);
    ui->widgetMain->resize(130,130);
    ui->widgetMountBlock->resize(130,130);
    ui->widgetMountNic->resize(130,130);
    ui->widgetSelectImage->resize(130,130);
    ui->widgetSelectNic->resize(130,130);
    ui->widgetWait->resize(130,130);
    ui->widgetChangePassword->resize(130,130);
    ui->widgetResult->resize(130,130);

    ui->treeWidgetNic->setColumnCount(3);
    QStringList lst;
    lst.append("SSID");
    lst.append("信号");
    lst.append("安全");
    lst.append("BSSID");
    ui->treeWidgetNic->setHeaderLabels(lst);

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

    ui->widgetMountBlock->setEnabled(id == WIDGET_MOUNT_BLOCK);
    ui->widgetMountBlock->setVisible(id == WIDGET_MOUNT_BLOCK);
    if(id == WIDGET_MOUNT_BLOCK) {
        ui->listWidgetBlockInfo->setFocus();
    }

    ui->widgetMountNic->setEnabled(id == WIDGET_MOUNT_NIC);
    ui->widgetMountNic->setVisible(id == WIDGET_MOUNT_NIC);

    ui->widgetSelectImage->setEnabled(id == WIDGET_SELECT_IMAGE);
    ui->widgetSelectImage->setVisible(id == WIDGET_SELECT_IMAGE);
    if(id == WIDGET_SELECT_IMAGE) {
        ui->listWidgetImage->setFocus();
    }

    ui->widgetSelectNic->setEnabled(id == WIDGET_SELECT_NIC);
    ui->widgetSelectNic->setVisible(id == WIDGET_SELECT_NIC);
    if(id == WIDGET_SELECT_NIC) {
        ui->treeWidgetNic->setFocus();
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
    case WIDGET_MOUNT_BLOCK:
        currentInterface = ui->widgetMountBlock;
        break;
    case WIDGET_MOUNT_NIC:
        currentInterface = ui->widgetMountNic;
        break;
    case WIDGET_SELECT_IMAGE:
        currentInterface = ui->widgetSelectImage;
        break;
    case WIDGET_SELECT_NIC:
        currentInterface = ui->widgetSelectNic;
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


