#include "text.h"

#include <QtMath>
#include <QPainter>
#include <QTextOption>

Text::Text(QColor color, int size, const QString& text) {
    m_size = size;
    m_color = color;
    m_rect = QRectF(-m_size / 1.5, m_size / 2, m_size * 1.5, m_size);

    m_text = text;
}

Text::Text(QDataStream &stream)
    : Shape(stream) {
    stream >> m_text;
}

qreal Text::get_area() const {
    return 2 * qPow(m_size, 2);
}

void Text::write_to_stream(QDataStream& stream) const {
    stream << ShapeType::Text;   // type of figure
    stream << get_id();          // id
    stream << m_color;           // color of figure
    stream << m_size;            // size of figure
    stream << m_rect;            // bounding rect
    stream << scenePos();        // position on scene
    stream << m_text;            // text on figure
}

ShapeType Text::get_type() const {
    return ShapeType::Text;
}

void Text::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // fake rectangle to
    // give item ability to move
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawRect(m_rect);

    painter->setPen(QPen(m_color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    auto font = painter->font();
    font.setPointSize(11);
    painter->setFont(font);

    painter->drawText(m_rect, m_text);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}


