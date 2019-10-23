#pragma once

#include "shape.hpp"
#include "sinwave.hpp"

class SinSquare : virtual public Shape {

public:
    SinSquare(Point leftUp, Point rightDown, 
                double amplitude = 10, double frequency = 100, Color color = Color(0, 0, 0));

    std::vector<Point> getAllPoints() const override;
    void move(Point delta) override;

protected:
    std::ostream& info(std::ostream &os) const override;

private:
    void updateSides();

    Point leftUp;
    Point leftDown;
    Point rightUp;
    Point rightDown;

    SinWave leftSide;
    SinWave rightSide;
    SinWave upSide;
    SinWave downSide;
    
    double amplitude;
    double frequency;
};