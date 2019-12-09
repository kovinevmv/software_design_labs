#include "squarewithtext.h"

#include <QPainter>
#include <QTextOption>
#include <QColor>
#include <QGraphicsSceneContextMenuEvent>
#include <QStyleOptionGraphicsItem>

SquareWithText::SquareWithText(QColor color, int size, const QString &text, double amplitude, double freq)
    : Text(color, size, text), Square(color, size, amplitude, freq){
    m_rect = QRectF(-m_size / 1.3, m_size / 2.5, m_size * 2.4, m_size * 2.4);
}

SquareWithText::SquareWithText(QDataStream &stream)
    : Shape(stream) {
    stream >> m_text;

    for (int i = 0; i < 4; i++){
        ShapeType type;
        stream >> type;
        sides.push_back(SinWave(stream));
   }
}

qreal SquareWithText::get_area() const {
    return Square::get_area();
}

void SquareWithText::write_to_stream(QDataStream& stream) const {
    stream << ShapeType::SquareWithText;   // type of figure
    stream << get_id();                    // id
    stream << m_color;                     // color of figure
    stream << m_size;                      // size of figure
    stream << m_rect;                      // bounding rect
    stream << scenePos();                  // position on scene
    stream << m_text;                      // text on figure

    for (int i = 0; i < sides.size(); i++)
        stream << sides[i];
}

ShapeType SquareWithText::get_type() const {
    return ShapeType::SquareWithText;
}

void SquareWithText::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(m_color, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    //painter->setBrush(m_color);

    for (int i = 0; i < sides.size(); i++){
        auto points = sides[i].getAllPoints();
        QPainterPath path;
        QPolygonF myPolygon(points);
        path.addPolygon(myPolygon);
        painter->drawPath(path);
    }

    auto text_options = QTextOption();
    text_options.setAlignment(Qt::AlignCenter);

    auto font = painter->font();
    font.setPointSize(11);
    painter->setFont(font);
    painter->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    painter->drawText(m_rect, m_text, text_options);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
