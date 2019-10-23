#pragma once

#include "shape.hpp"

class Text : virtual public Shape {
public:
    Text(std::string text, Point leftUp, Point rigthDown,
                 Color color = Color(0, 0, 0), int textSize = 16);

    std::vector<Point> getAllPoints() const override;
    void move(Point delta) override;

    const std::string &getText() const;
    void setText(const std::string& text);

protected:
    std::ostream& info(std::ostream &os) const override;

private:
    std::string text;
    int textSize;
    Point leftUpText;
    Point rigthDownText;
    
    std::vector<Point> getRect();
};