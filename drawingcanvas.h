#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QGraphicsView>
#include <QMouseEvent>

class DrawingCanvas : public QGraphicsView
{
    Q_OBJECT

public:

    explicit DrawingCanvas(QWidget* parent = 0);

    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);

signals:

    void mousePressed(QPoint);
};

#endif // DRAWINGCANVAS_H
