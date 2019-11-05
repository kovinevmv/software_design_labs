#include "sinsquaretext.hpp"

SinSquareText::SinSquareText(Point leftUpSquare, Point rightDownSquare, 
                            std::string text, double amplitude/* = 10*/, double frequency/* = 100*/, 
                            Color color/* = Color(0, 0, 0)*/, int textSize/* = 16*/) :
                            SinSquare(leftUpSquare, rightDownSquare, amplitude, frequency, color), 
                            Text(text, leftUpSquare, rightDownSquare, color, textSize) {};

SinSquareText::SinSquareText(SinSquare& sinSquare, Text& text) :
             SinSquare(sinSquare), Text(text) {};


std::ostream& SinSquareText::info(std::ostream &os) const {
    os << "SinSquareText {";
    Text::info(os);
    os << ", ";
    SinSquare::info(os);
    return os << "}";
}


std::vector<Point> SinSquareText::getAllPoints() const {
    auto sinSquarePoint = SinSquareText::getAllPoints();
    auto textPoints = Text::getAllPoints();
    sinSquarePoint.insert(sinSquarePoint.end(), textPoints.begin(), textPoints.end());
    return sinSquarePoint;
}

void SinSquareText::move(Point delta) {
    Text::move(delta);
    SinSquare::move(delta);
}

