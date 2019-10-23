#include <cmath>
#include "sinsquare.hpp"

SinSquare::SinSquare(Point lu, Point rd, double amplitude /* = 10*/, 
        double frequency /* = 100*/, Color color /*= Color(0, 0, 0)*/) : 
        Shape(color), leftUp(lu), rightDown(rd), 
        amplitude(amplitude), frequency(frequency) {
    
    
    rightUp = Point(lu.getX() + rd.getX() + lu.getY() - rd.getY(), 
                rd.getX() - lu.getX() + lu.getY() + rd.getY()) / 2;
    leftDown = Point(lu.getX() + rd.getX() + rd.getY() - lu.getY(), 
                lu.getX() - rd.getX() + lu.getY() + rd.getY()) / 2;
    

    centerPoint = (lu + rd) / 2;
    updateSides(); 
}

void SinSquare::updateSides(){
    leftSide = SinWave(leftUp, leftDown, amplitude, frequency);
    upSide = SinWave(leftUp, rightUp, amplitude, frequency);
    rightSide = SinWave(rightUp, rightUp, amplitude, frequency);
    downSide = SinWave(leftDown, rightDown, amplitude, frequency);
}

void SinSquare::move(Point delta) {
    Shape::move(delta);

    leftUp += delta; 
    leftDown += delta;
    rightUp += delta;
    rightDown += delta;
    updateSides();
}


std::vector<Point> SinSquare::getAllPoints() const {
    auto points = std::vector<Point>();
    points.push_back(leftUp);
    points.push_back(leftDown);
    points.push_back(rightUp);
    points.push_back(rightDown);
    return points;
}

std::ostream& SinSquare::info(std::ostream &os) const {
    return os << "SinSquare {" 
        << rightUp << ", " << rightDown << ", " 
        << leftDown << ", " << leftUp << "}";
}
