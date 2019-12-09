#ifndef TEXT_H
#define TEXT_H

#include "shape.h"

#include <QString>
#include <QDataStream>

class Text : public virtual Shape
{

public:

    Text(QColor color, int size, const QString& text);
    Text(QDataStream& stream);

    qreal get_area() const override;
    void write_to_stream(QDataStream& stream) const override;
    ShapeType get_type() const override;

protected:

    Text() = default;

    QString m_text;

private:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // TEXT_H
