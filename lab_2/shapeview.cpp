#include "shapeview.h"

#include <QWheelEvent>
#include <QtMath>

ShapeView::ShapeView(QWidget *parent)
    : QGraphicsView(parent) {
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing, true);

    scale(1, 1);
    setDragMode(QGraphicsView::RubberBandDrag);
    setTransformationAnchor(AnchorUnderMouse);
}

void ShapeView::wheelEvent(QWheelEvent *event) {
    scale_view(qPow(2, event->delta() / 240.0));
}

void ShapeView::scale_view(qreal scale_factor) {
    qreal factor = transform()
                   .scale(scale_factor, scale_factor)
                   .mapRect(QRectF(0, 0, 1, 1))
                   .width();

    if (factor < 0.07 || factor > 100)
        return;

    scale(scale_factor, scale_factor);
}
