#include "drawingcanvas.h"

#include <QDebug>

DrawingCanvas::DrawingCanvas(QWidget* parent) : QGraphicsView(parent)
{

}

void DrawingCanvas::mousePressEvent(QMouseEvent *e)
{
    emit mousePressed(e->pos());
}

void DrawingCanvas::mouseMoveEvent(QMouseEvent *e)
{
    emit mousePressed(e->pos());
}
