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

bool Shape::operator==(const Shape& other){
    return typeid(*this).name() == typeid(other).name();
}

bool Shape::operator<(const Shape& other){
    return this->centerPoint.length() < other.centerPoint.length();
}

bool Shape::operator>(const Shape& other){
    return this->centerPoint.length() > other.centerPoint.length();
}
