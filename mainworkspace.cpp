#include "mainworkspace.h"
#include <QDebug>

MainWorkspace::MainWorkspace()
{
    //Create a blank image of size 64 by 64
    image = QImage(64, 64, QImage::Format_ARGB32);
    image.fill(qRgba(0, 0, 0, 0));

    //Set the default brush color
    brushColor = qRgba(105, 0, 255, 255);

    //Add the created image to the list of layers as a pixmap item
    layers.push_back(new QGraphicsPixmapItem(QPixmap::fromImage(image)));
    currentLayer = 0;

    //Add the item to the scene
    scene->addItem(layers[currentLayer]);
}

MainWorkspace::~MainWorkspace()
{
    for(QGraphicsPixmapItem* pixmap : layers)
    {
        delete pixmap;
    }
    layers.clear();
}

void MainWorkspace::firstCall()
{
    //Display the created scene
    emit displayScene(scene);
}

void MainWorkspace::drawPixel(QPoint pos)
{
    //Find the x and y coordinates converted from canvas to pixels
    int x = pos.x() * scene->width() / 400;
    int y = pos.y() * scene->height() /400;

    //Set the clicked on pixel to the current brush color
    image.setPixel(x, y, brushColor.rgba());

    //replace the pixmap of the current layer
    layers[currentLayer]->setPixmap(QPixmap::fromImage(image));

    //Tell the view the scene has been changed
    emit imageChanged(scene);
}

void MainWorkspace::addLayer()
{
    //Create a blank image of size 64 by 64
    QImage newImage(64, 64, QImage::Format_ARGB32);
    newImage.fill(qRgba(0, 0, 0, 0));

    //Add the created image to the list of layers as a pixmap item
    layers.push_back(new QGraphicsPixmapItem(QPixmap::fromImage(newImage)));

    //Add the item to the scene
    scene->addItem(layers[layers.count()-1]);
}

void MainWorkspace::changeLayer(int layer)
{
    //Set the current layer index and image to be that of the new layer
    currentLayer = layer;
    image = layers[currentLayer]->pixmap().toImage();
}

void MainWorkspace::setVisibility(int pos, bool vis)
{
    layers[pos]->setVisible(vis);
}
