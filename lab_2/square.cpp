#include "square.h"

#include <QtMath>
#include <QColor>
#include <QGraphicsSceneContextMenuEvent>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QTextOption>
#include <QTextStream>
#include <QRectF>

Square::Square(QColor color, int size, double amplitude, double freq) {
    m_color = color;
    m_size = size;
    m_rect = QRectF(-m_size / 1.3, m_size / 2.5, m_size * 2.4, m_size * 2.4);

    sides.clear();
    sides.push_back(SinWave(m_color, m_size, QPointF(-1, 1), QPointF(-1, -1), amplitude, freq));
    sides.push_back(SinWave(m_color, m_size, QPointF(-1, -1), QPointF(1, -1), amplitude, freq));
    sides.push_back(SinWave(m_color, m_size, QPointF(1, -1), QPointF(1, 1), amplitude, freq));
    sides.push_back(SinWave(m_color, m_size, QPointF(-1, 1), QPointF(1, 1), amplitude, freq));
}

Square::Square(QDataStream &stream)
    : Shape(stream) {

    for (int i = 0; i < 4; i++){
        ShapeType type;
        stream >> type;
        sides.push_back(SinWave(stream));
   }
}

qreal Square::get_area() const {
    return qPow(m_size, 2);
}

void Square::write_to_stream(QDataStream& stream) const {
    stream << ShapeType::Square; // type of figure
    stream << get_id();          // id
    stream << m_color;           // color of figure
    stream << m_size;            // size of figure
    stream << m_rect;            // bounding rect
    stream << scenePos();        // position on scene

    for (int i = 0; i < sides.size(); i++)
        stream << sides[i];
}

ShapeType Square::get_type() const {
    return ShapeType::Square;
}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(m_color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    for (int i = 0; i < sides.size(); i++){
        auto points = sides[i].getAllPoints();
        QPainterPath path;
        QPolygonF myPolygon(points);
        path.addPolygon(myPolygon);
        painter->drawPath(path);
    }

    painter->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
