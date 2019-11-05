#include <cmath>
#include "sinwave.hpp"

SinWave::SinWave(Point startPoint, Point endPoint, double amplitude/* = 10*/,
                 double frequency/* = 100*/, Color color/* = Color(0, 0, 0)*/)
        : Shape(color), startPoint(startPoint), endPoint(endPoint), 
          amplitude(amplitude), frequency(frequency) {
    centerPoint = (startPoint + endPoint) / 2;
}


void SinWave::move(Point delta) {
    Shape::move(delta);
    startPoint += delta;
    endPoint += delta;
}

std::vector<Point> SinWave::getAllPoints() const {
    auto points = std::vector<Point>();

    Point d = endPoint - startPoint;
    Point n = Point(-d.getY(), d.getX());

    points.push_back(startPoint);
    for (size_t i = 1; i < this->frequency; i++){
        Point currentPoint = startPoint + d * i / frequency;
        currentPoint += n * (sin(i) * amplitude);
        points.push_back(currentPoint);
    }
    points.push_back(endPoint);

    return points;
}

std::ostream& SinWave::info(std::ostream &os) const {
    return os << "SinWave (startPoint: " << startPoint << ", endPoint: "
              << endPoint << ", amplitude: " << amplitude << ", frequency: " 
              << frequency << ")";
}
