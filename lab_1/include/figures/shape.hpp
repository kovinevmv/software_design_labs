#pragma once

#include <tuple>
#include <vector>
#include <utility>
#include <ostream>
#include <typeinfo>

#include "point.hpp"
#include "color.hpp"


class Shape {
public:
    Shape(Color color = Color(0, 0, 0), Point centerPoint = Point(0, 0));
    virtual ~Shape() = default;

    virtual std::vector<Point> getAllPoints() const = 0;
    virtual void move(Point);

    const Point& getCenterPoint() const;
    const Color& getColor() const;
    void setColor(const Color&);

    friend std::ostream &operator<<(std::ostream &os, const Shape &shape);
    
    bool operator==(const Shape&);
    bool operator!=(const Shape&);
    bool operator<(const Shape&);
    bool operator>(const Shape&);

protected:
    virtual std::ostream& info(std::ostream &o) const = 0;

    Color color;
    Point centerPoint;
};
