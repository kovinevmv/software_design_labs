#ifndef SinWave_H
#define SinWave_H

#include "shape.h"

#include <QDataStream>
#include <QVector>

class SinWave : public virtual Shape
{
public:
    SinWave(QColor color, int radius, QPointF start, QPointF end, double, double);
    SinWave(QDataStream& stream);

    qreal get_area() const override;
    void write_to_stream(QDataStream& stream) const override;
    ShapeType get_type() const override;

    QVector<QPointF> getAllPoints() ;
    QRectF getBoundingRect() ;
    SinWave() = default;
    SinWave(const SinWave&);
    SinWave& operator=(SinWave);

protected:
    QPointF startPoint;
    QPointF endPoint;
    double frequency;
    double amplitude;


private:

    void setPoints(QPointF, QPointF);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // SinWave_H
