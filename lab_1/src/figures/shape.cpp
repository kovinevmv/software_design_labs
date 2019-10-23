#include <algorithm>
#include <math.h>

#include "point.hpp"
#include "shape.hpp"

const Point& Shape::getCenterPoint() const {
    return centerPoint;
}

void Shape::move(Point delta) {
    centerPoint += delta;
}

std::ostream &operator<<(std::ostream &os, const Shape &shape) {
    return shape.info(os);
}