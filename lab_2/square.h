#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"
#include <sinwave.h>


class Square : public virtual Shape {

public:

    Square(QColor color, int size, double amplitude, double freq);
    Square(QDataStream& stream);

    qreal get_area() const override;
    void write_to_stream(QDataStream& stream) const override;
    ShapeType get_type() const override;

protected:

    Square() = default;

    QVector<QPointF> points;
    QVector<SinWave> sides;

private:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // SQUARE_H
