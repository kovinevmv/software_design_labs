#include <algorithm>
#include <math.h>

#include "point.hpp"
#include "shape.hpp"

Shape::Shape(Color color, Point centerPoint) :
        color(color), centerPoint(centerPoint) {};

const Point& Shape::getCenterPoint() const {
    return centerPoint;
}

const Color& Shape::getColor() const{
    return color;
}

void Shape::move(Point delta) {
    centerPoint += delta;
}

std::ostream &operator<<(std::ostream &os, const Shape &shape) {
    return shape.info(os);
}

bool Shape::operator==(const Shape& other){
    return typeid(*this).name() == typeid(other).name() && 
           this->color == other.getColor() && 
           this->centerPoint == other.getCenterPoint();
}

bool Shape::operator!=(const Shape& other){
    return !(*this == other);
}

bool Shape::operator<(const Shape& other){
    return this->centerPoint.length() < other.centerPoint.length();
}

bool Shape::operator>(const Shape& other){
    return this->centerPoint.length() > other.centerPoint.length();
}
