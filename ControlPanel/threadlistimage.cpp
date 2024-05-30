#include "threadlistimage.h"


ThreadListImage::ThreadListImage(QObject *parent, QListWidget * list)
    : StateThreadBase(parent)
    , listImage(list)
{

}

void ThreadListImage::run()
{
    /*
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    listImage->setModel(model);
    listImage->setRootIndex(model->index(QDir::currentPath()));
    */
    QListWidgetItem * item1 = new QListWidgetItem(QIcon(tr("/Users/michael/Downloads/MegaUDisk/ControlPanel/ico/folder.png")), QString(tr("item1")), listImage);
    QListWidgetItem * item2 = new QListWidgetItem(QIcon(tr("/Users/michael/Downloads/MegaUDisk/ControlPanel/ico/hdd.png")), QString(tr("item2")), listImage);
    QListWidgetItem * item3 = new QListWidgetItem(QIcon(tr("/Users/michael/Downloads/MegaUDisk/ControlPanel/ico/cdrom.png")), QString(tr("item3")), listImage);


    listImage->addItem(item1);
    listImage->addItem(item2);
    listImage->addItem(item3);
    setStateOK();
}
