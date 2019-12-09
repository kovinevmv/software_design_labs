#ifndef SHAPEVIEW_H
#define SHAPEVIEW_H

#include <QGraphicsView>

class ShapeView : public QGraphicsView
{

public:

    ShapeView(QWidget *parent = 0);

protected:

    void wheelEvent(QWheelEvent *event) override;

private:

    void scale_view(qreal scale_factor);

};

#endif // SHAPEVIEW_H
