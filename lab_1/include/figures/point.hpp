#pragma once

#include <iostream>

class Point {
    double x;
    double y;

public:
    Point(double x, double y): x(x), y(y) {};
    Point() : Point(0, 0) {};
    Point(const Point &p) = default;
    Point(Point&& p) noexcept;

    ~Point() = default;

    double getX() const;
    double getY() const;

    void setX(double x);
    void setY(double y);

    double length() const ;
    double distanceTo(const Point& other) const;

    Point& operator=(Point p);
    Point& operator+=(Point p);
    Point& operator-=(Point p);
    Point& operator/(double i);
    Point& operator*(double i);
    Point& operator-();
    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend std::istream& operator>>(std::istream& is, Point& p);

    friend void swap(Point& a, Point& b);
};

bool operator==(const Point& a, const Point& b);
Point operator+(const Point& p1, const Point& p2);
Point operator-(const Point& p1, const Point& p2);

Point operator+(const Point& point, double a);
Point operator-(const Point& point, double a);


