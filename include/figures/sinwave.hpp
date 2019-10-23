#pragma once

#include "shape.hpp"

class SinWave : virtual public Shape {

public:
    explicit SinWave(Point startPoint, Point endPoint, double amplitude = 10, double frequency = 100, Color color = Color(0, 0, 0));
    SinWave() {};

    std::vector<Point> getAllPoints() const override;

    void move(Point delta) override;

protected:
    std::ostream& info(std::ostream &o) const override;

private:
 
    Point startPoint;
    Point endPoint;
        
    double amplitude;
    double frequency;
};