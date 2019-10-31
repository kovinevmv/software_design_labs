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
    Shape(Color color = Color(0, 0, 0), Point centerPoint = Point(0, 0)): 
                color(color), centerPoint(centerPoint){};

    virtual ~Shape() = default;

    virtual std::vector<Point> getAllPoints() const = 0;

    virtual void move(Point delta);

    const Point& getCenterPoint() const;

    friend std::ostream &operator<<(std::ostream &os, const Shape &shape);
    bool operator==(const Shape& other);
    bool operator<(const Shape& other);
    bool operator>(const Shape& other);

protected:
    virtual std::ostream& info(std::ostream &o) const = 0;

    Color color;
    Point centerPoint;
};
