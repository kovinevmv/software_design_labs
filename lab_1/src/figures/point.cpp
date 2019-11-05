#include <algorithm>
#include <cmath>

#include "point.hpp"

Point::Point(Point &&p) noexcept {
    swap(*this, p);
}

double Point::getX() const{
    return this->x;
}

double Point::getY() const{
    return this->y;
}

void Point::setX(double x){
    this->x = x;
}
void Point::setY(double y){
    this->y = y;
}

double Point::distanceTo(const Point& other) const {
    return sqrt(pow(this->x - other.getX(), 2) + pow(this->y - other.getY(), 2));
}

double Point::length() const {
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

Point &Point::operator=(Point p) {
    swap(*this, p);
    return *this;
}

Point & Point::operator/(double k){
    x /= k;
    y /= k;
    return *this;
}

Point & Point::operator*(double k){
    x *= k;
    y *= k;
    return *this;
}

Point &Point::operator+=(Point point) {
    x += point.getX();
    y += point.getY();
    return *this;
}

Point &Point::operator-=(Point point) {
    x -= point.getX();
    y -= point.getY();
    return *this;
}

Point &Point::operator-() {
    x = -x;
    y = -y;
}

bool operator==(const Point & lhs, const Point & rhs){
    return ((lhs.getX() == rhs.getX()) && (lhs.getY() == rhs.getY()));
}

Point operator+(const Point& lhs, const Point& rhs) {
    return Point(lhs.getX() + rhs.getX(), lhs.getY() + rhs.getY());
}

Point operator-(const Point& lhs, const Point& rhs) {
    return lhs + -Point(rhs);
}

Point operator+(const Point& point, double a) {
    return point + Point(a, a);
}

Point operator-(const Point& point, double a) {
    return point + -a;
}

bool Point::operator==(const Point& other) {
    return this->x == other.getX() && this->y == other.getY();
}

bool Point::operator!=(const Point& other) {
    return !(*this == other);
}

std::ostream & operator<<(std::ostream & os, const Point& point){
    return os << "Point(" << point.x << "," << point.y << ")";
}

std::istream & operator>> (std::istream & is, Point& point){
    return is >> point.x >> point.y;
}

void swap(Point &a, Point &b) {
    std::swap(a.x, b.x);
    std::swap(a.y, b.y);
}