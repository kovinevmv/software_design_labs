#include "text.hpp"


Text::Text(std::string text, Point leftUp, Point rigthDown,
        Color color /* Color(0,0,0) */, int textSize /* =16*/) : 
        Shape(color), text(text), textSize(textSize), leftUpText(leftUp), rigthDownText(rigthDown){
    centerPoint = (rigthDown + leftUp) / 2;
}

std::vector<Point> Text::getAllPoints() const{
    Point rightUp = Point(leftUpText.getX() + rigthDownText.getX() + leftUpText.getY() - rigthDownText.getY(), 
                rigthDownText.getX() - leftUpText.getX() + leftUpText.getY() + rigthDownText.getY()) / 2;
    Point leftDown = Point(leftUpText.getX() + rigthDownText.getX() + rigthDownText.getY() - leftUpText.getY(), 
                leftUpText.getX() - rigthDownText.getX() + leftUpText.getY() + rigthDownText.getY()) / 2;
    
    auto points = std::vector<Point>();
    points.push_back(leftUpText);
    points.push_back(leftDown);
    points.push_back(rightUp);
    points.push_back(rigthDownText);
    return points;
}

void Text::move(Point delta) {
    Shape::move(delta);
    leftUpText += delta;
    rigthDownText += delta;
}

std::ostream& Text::info(std::ostream &os) const {
    return os << "Text: {text: " << text << "; size:" << textSize << "}";
}

const std::string &Text::getText() const {
    return text;
}

void Text::setText(const std::string &text) {
    this->text = text;
}
