#ifndef SQUAREWITHTEXT_H
#define SQUAREWITHTEXT_H

#include "square.h"
#include "text.h"

class SquareWithText : public virtual Text, public virtual Square
{

public:

    SquareWithText(QColor color, int size, const QString& text, double amplitude, double freq);
    SquareWithText(QDataStream& stream);

    qreal get_area() const override;
    void write_to_stream(QDataStream& stream) const override;
    ShapeType get_type() const override;

private:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // SQUAREWITHTEXT_H
