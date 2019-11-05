#pragma once

#include <iostream>

class Point {
    double x;
    double y;

public:
    Point(double x, double y): x(x), y(y) {};
    Point() : Point(0, 0) {};
    Point(const Point &) = default;
    Point(Point&& p) noexcept;

    ~Point() = default;

    double getX() const;
    double getY() const;

    void setX(double);
    void setY(double);

    double length() const ;
    double distanceTo(const Point&) const;

    Point& operator=(Point);
    Point& operator+=(Point);
    Point& operator-=(Point);
    Point& operator/(double);
    Point& operator*(double);
    Point& operator-();

    bool operator==(const Point&);
    bool operator!=(const Point&);
    

    friend std::ostream& operator<<(std::ostream&, const Point&);
    friend std::istream& operator>>(std::istream&, Point&);

    friend void swap(Point&, Point&);
};

bool operator==(const Point&, const Point&);
Point operator+(const Point&, const Point&);
Point operator-(const Point&, const Point&);

Point operator+(const Point&, double);
Point operator-(const Point&, double);


