#ifndef WIDGETMOUNTBLOCK_H
#define WIDGETMOUNTBLOCK_H

#include <QObject>
#include <QWidget>

class WidgetMountBlock : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetMountBlock(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    bool getMountImage () {
        return mountImage;
    }
    void setMountImage(bool isImage) {
        mountImage = isImage;
    }
private:
    bool mountImage;
signals:

};

#endif // WIDGETMOUNTBLOCK_H
