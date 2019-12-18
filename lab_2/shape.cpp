#include "shape.h"
#include "shapetypes.h"
#include "square.h"
#include "sinwave.h"
#include "squarewithtext.h"

#include <QGraphicsSceneEvent>
#include <QCursor>
#include <QMessageBox>

Shape::Shape() {
    m_id = m_id_count;
    m_id_count++;

    setCacheMode(DeviceCoordinateCache);
}

Shape::Shape(QDataStream& stream) {
    stream >> m_id;
    stream >> m_color;
    stream >> m_size;
    stream >> m_rect;

    QPointF pos;
    stream >> pos;
    setPos(pos);

    setCacheMode(DeviceCoordinateCache);
}



Shape* Shape::load_figure(QDataStream &stream) {
    ShapeType type;
    stream >> type;


    switch (type) {
        case ShapeType::Square:
            return new Square(stream);
        case ShapeType::SinWave:
            return new SinWave(stream);
        case ShapeType::Text:
            return new Text(stream);
        case ShapeType::SquareWithText:
            return new SquareWithText(stream);
        default:
            return nullptr;
    }
}

int Shape::get_id() const {
    return m_id;
}

QDataStream& operator<<(QDataStream& stream, const Shape& shape) {
    shape.write_to_stream(stream);
    return stream;
}

QDataStream& operator<<(QDataStream& stream, const Shape* shape) {
    shape->write_to_stream(stream);
    return stream;
}

QRectF Shape::boundingRect() const {
    return m_rect;
}

void Shape::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    this->setPos(mapToScene(event->pos()));
}

void Shape::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
    }

    Q_UNUSED(event)
}

void Shape::setColor(QColor q){
    saveColor();
    m_color = q;
}

void Shape::saveColor(){
    this->temp_color = m_color;
}


void Shape::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        this->setCursor(QCursor(Qt::ArrowCursor));
    }

    Q_UNUSED(event)
}

QColor Shape::get_color() const{
    return m_color;
}

QRectF Shape::get_rect() const{
    return m_rect;
}


bool Shape::operator==(const Shape& other){
    return this->m_color == other.get_color() &&
           this->m_rect == other.get_rect() &&
           this->get_type() == other.get_type();
}

bool Shape::operator!=(const Shape& other){
    return !(*this == other);
}
