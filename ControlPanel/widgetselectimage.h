#ifndef WIDGETSELECTIMAGE_H
#define WIDGETSELECTIMAGE_H

#include <QObject>
#include <QWidget>

class WidgetSelectImage : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSelectImage(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *event);
    const QString & getCurrentPath()
    {
        return currentPath;
    }
    const QString &  pushPath(const QString & path)
    {
        if(currentPath.length() && currentPath.right(1) != QChar('/')) {
            currentPath.append(QChar('/'));
        }
        currentPath.append(path);
        while(currentPath.length() > 1 && currentPath.right(1) == QChar('/')) {
            currentPath.chop(1);
        }
        return currentPath;
    }
    const QString & popPath()
    {
        if(currentPath.length() > 1 && currentPath.right(1) != QChar('/')) {
            int index = currentPath.lastIndexOf(QChar('/'));
            if(index > 0) {
                currentPath.chop(currentPath.length() - index);
            } else if(index == 0) {
                currentPath.chop(currentPath.length() - 1);
            }
        }
        return currentPath;
        // /anal/fuckme
    }
private:
    QString currentPath;
signals:
};

#endif // WIDGETSELECTIMAGE_H
