#ifndef MAINWORKSPACE_H
#define MAINWORKSPACE_H

#include "qgraphicsscene.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class MainWorkspace : public QObject
{
    Q_OBJECT

    QGraphicsScene *scene = new QGraphicsScene(0, 0, 64, 64);
    QVector<QGraphicsPixmapItem*> layers;

    QImage image;
    int currentLayer;
    QColor brushColor;

public:
    MainWorkspace();
    ~MainWorkspace();

public slots:

    void firstCall();
    void drawPixel(QPoint);
    void addLayer();
    void changeLayer(int);
    void setVisibility(int, bool);

signals:

    void displayScene(QGraphicsScene* scene);
    void imageChanged(QGraphicsScene* scene);
};

#endif // MAINWORKSPACE_H
