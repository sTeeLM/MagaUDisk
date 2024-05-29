#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initilizeUI();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << tr("MainWindow::keyPressEvent");
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

    showWidgetGetPass(true);
    showWidgeMountSerial(false);
    showWidgetMain(false);
    showWidgetMountImage(false);
    showWidgetMountNic(false);
    showWidgetMountPart(false);
    showWidgetSelectImage(false);


}

void MainWindow::showWidgetGetPass(bool show)
{
    ui->widgetGetPass->setEnabled(show);
    ui->widgetGetPass->setVisible(show);
}

void MainWindow::showWidgeMountSerial(bool show)
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
