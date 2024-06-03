#include "threadmountimage.h"

ThreadMountImage::ThreadMountImage(QObject *parent, bool isMount, const QString & image)
    : StateThreadMount(parent, isMount)
    , imagePath(image)
{}
