#ifndef SHAPE_H
#define SHAPE_H

#include "shapetypes.h"

#include <QDataStream>
#include <QGraphicsObject>


class ShapeScene;

class Shape : public QGraphicsObject {

    Q_OBJECT

    friend class ShapeScene;

public:

    static Shape* load_figure(QDataStream& stream);

    virtual ~Shape() override = default;

    int get_id() const;

    qreal virtual get_area() const = 0;
    void virtual write_to_stream(QDataStream& stream) const = 0;
    ShapeType virtual get_type() const = 0;
    Shape();
    Shape(Shape&&);
    Shape(const Shape&);

    Shape(QDataStream& stream);

protected:
    QColor m_color;
    QColor temp_color;
    QRectF m_rect;
    int m_size;

private:

    void setColor(QColor);
    void saveColor();

    static inline int m_id_count = 0;
    int m_id;

    QRectF boundingRect() const override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

QDataStream& operator<<(QDataStream& stream, const Shape& shape);
QDataStream& operator<<(QDataStream& stream, const Shape* shape);

template<>
struct std::hash<Shape*> {
    inline std::size_t operator()(const Shape* figure) {
        return reinterpret_cast<std::uintptr_t>(figure);
    }
};

template<>
struct std::equal_to<Shape*> {
    inline bool operator()(const Shape* lhs, const Shape* rhs) {
        return lhs == rhs;
    }
};

#endif // SHAPE_H
