#include "sinwave.h"

#include <QTextOption>
#include <QPainter>
#include <QtMath>
#include <QColor>
#include <QGraphicsSceneContextMenuEvent>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

SinWave::SinWave(QColor color, int radius, QPointF start, QPointF end, double amplitude_, double frequency_) {
    m_color = color;
    m_size = radius;
    startPoint = start;
    endPoint = end;
    m_rect = QRectF(-m_size / 2, m_size / 2, m_size * 2, m_size * 2);
    frequency = frequency_;
    amplitude = amplitude_;

    setPoints(startPoint, endPoint);
}

SinWave::SinWave(QDataStream &stream)
    : Shape(stream) {

    stream >> amplitude;
    stream >> frequency;
    stream >> startPoint;
    stream >> endPoint;
}

void SinWave::write_to_stream(QDataStream &stream) const {
    stream << ShapeType::SinWave; // type of figure
    stream << get_id();          // id
    stream << m_color;           // color of figure
    stream << m_size;            // size of figure
    stream << m_rect;            // bounding rect
    stream << scenePos();        // position on scene
    stream << amplitude;
    stream << frequency;
    stream << startPoint;
    stream << endPoint;


}

void SinWave::setPoints(QPointF a, QPointF b){
    startPoint = a;
    endPoint = b;

    if (startPoint.x() == -1 && startPoint.y() == 1){
        startPoint = m_rect.topLeft();
    }
    if (startPoint.x() == 1 && startPoint.y() == 1){
        startPoint = m_rect.topRight();
    }
    if (startPoint.x() == -1 && startPoint.y() == -1){
        startPoint = m_rect.bottomLeft();
    }
    if (startPoint.x() == 1 && startPoint.y() == -1){
        startPoint = m_rect.bottomRight();
    }

    if (startPoint.x() == 0 && startPoint.y() == 1){
        startPoint = (m_rect.topLeft() + m_rect.topRight()) / 2.0;
    }
    if (startPoint.x() == 0 && startPoint.y() == -1){
        startPoint = (m_rect.bottomLeft() + m_rect.bottomRight()) / 2.0;
    }
    if (startPoint.x() == -1 && startPoint.y() == 0){
        startPoint = (m_rect.topLeft() + m_rect.bottomLeft()) / 2.0;
    }
    if (startPoint.x() == 1 && startPoint.y() == 0){
        startPoint = (m_rect.topRight() + m_rect.bottomRight()) / 2.0;
    }

    if (endPoint.x() == -1 && endPoint.y() == 1){
        endPoint = m_rect.topLeft();
    }
    if (endPoint.x() == 1 && endPoint.y() == 1){
        endPoint = m_rect.topRight();
    }
    if (endPoint.x() == -1 && endPoint.y() == -1){
        endPoint = m_rect.bottomLeft();
    }
    if (endPoint.x() == 1 && endPoint.y() == -1){
        endPoint = m_rect.bottomRight();
    }


    if (endPoint.x() == 0 && endPoint.y() == 1){
        endPoint = (m_rect.topLeft() + m_rect.topRight()) / 2.0;
    }
    if (endPoint.x() == 0 && endPoint.y() == -1){
        endPoint = (m_rect.bottomLeft() + m_rect.bottomRight()) / 2.0;
    }
    if (endPoint.x() == -1 && endPoint.y() == 0){
        startPoint = (m_rect.topLeft() + m_rect.bottomLeft()) / 2.0;
    }
    if (endPoint.x() == 1 && endPoint.y() == 0){
        endPoint = (m_rect.topRight() + m_rect.bottomRight()) / 2.0;
    }
}

qreal SinWave::get_area() const {
    return M_PI * qPow(m_size, 2);
}

QVector<QPointF> SinWave::getAllPoints() {
    auto points = QVector<QPointF>();

    QPointF d = endPoint - startPoint;
    QPointF n = QPoint(-d.y(), d.x());

    points.push_back(startPoint);
    for (double i = 1; i < frequency; i++){
        QPointF currentPoint = startPoint + d * i / frequency;
        currentPoint += n * (qSin(i) * amplitude);
        points.push_back(currentPoint);
    }
    points.push_back(endPoint);

    return points;
}

QRectF SinWave::getBoundingRect() {
    // [0] - left up
    // [1] - left down
    // [2] - right down
    // [3] - right up
    std::vector<QPointF> ret_points= {QPointF(0, 0), QPointF(0, 0), QPointF(0, 0), QPointF(0, 0)};

    auto points = getAllPoints();
    for (int i = 0; i < points.size(); i++){
        auto point = points[i];
        if (point.x() >= ret_points[0].x() && point.y() >= ret_points[0].y())
            ret_points[0] = point;
        if (point.x() >= ret_points[1].x() && point.y() <= ret_points[1].y())
            ret_points[1] = point;
        if (point.x() <= ret_points[2].x() && point.y() <= ret_points[2].y())
            ret_points[2] = point;
        if (point.x() <= ret_points[3].x() && point.y() >= ret_points[3].y())
            ret_points[3] = point;
    }

    return QRectF(ret_points[3], ret_points[1]);
}



ShapeType SinWave::get_type() const {
    return ShapeType::SinWave;
}

void SinWave::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(m_color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    auto points = getAllPoints();

    QPainterPath path;
    QPolygonF myPolygon(points);
    path.addPolygon(myPolygon);
    painter->drawPath(path);

    //painter->drawText(m_rect, QString::number(get_id()), text_options);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

SinWave::SinWave(const SinWave& other){
    this->m_color = other.m_color;
    this->m_size = other.m_size;
    this->startPoint = other.startPoint;
    this->endPoint = other.endPoint;
    this->frequency = other.frequency;
    this->amplitude = other.amplitude;
}


SinWave& SinWave::operator=(SinWave other){
    this->m_color = other.m_color;
    this->m_size = other.m_size;
    this->startPoint = other.startPoint;
    this->endPoint = other.endPoint;
    this->frequency = other.frequency;
    this->amplitude = other.amplitude;
    return *this;
}


