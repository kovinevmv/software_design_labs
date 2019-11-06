#include <cmath>
#include "sinsquare.hpp"

SinSquare::SinSquare(Point lu, Point rd, double amplitude /* = 10*/, 
        double frequency /* = 100*/, Color color /*= Color(0, 0, 0)*/) : 
        Shape(color){
    
    
    Point rightUp = Point(lu.getX() + rd.getX() + lu.getY() - rd.getY(), 
                rd.getX() - lu.getX() + lu.getY() + rd.getY()) / 2;
    Point leftDown = Point(lu.getX() + rd.getX() + rd.getY() - lu.getY(), 
                lu.getX() - rd.getX() + lu.getY() + rd.getY()) / 2;
    
    points.push_back(lu);
    points.push_back(rightUp);
    points.push_back(rd);
    points.push_back(leftDown);

    centerPoint = (lu + rd) / 2;
    updateSides(amplitude, frequency); 
}

void SinSquare::updateSides(double amplitude, double frequency){
    sides.push_back(SinWave(points[0], points[3], amplitude, frequency));
    sides.push_back(SinWave(points[0], points[1], amplitude, frequency));
    sides.push_back(SinWave(points[1], points[2], amplitude, frequency));
    sides.push_back(SinWave(points[3], points[2], amplitude, frequency));
}

void SinSquare::move(Point delta) {
    Shape::move(delta);

    for (auto& point : points)
        point += delta;
    
    updateSides(sides[0].getAmplitude(), sides[0].getFrequency());
}


std::vector<Point> SinSquare::getAllPoints() const {
    return points;
}

std::ostream& SinSquare::info(std::ostream &os) const {
    return os << "SinSquare {" 
        << points[0] << ", " << points[1] << ", " 
        << points[2] << ", " << points[4] << "}";
}
