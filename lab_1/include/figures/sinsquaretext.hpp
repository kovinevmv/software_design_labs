#include "text.hpp"
#include "sinsquare.hpp"

class SinSquareText : virtual public Text, virtual public SinSquare {
public:
    SinSquareText(Point leftUpSquare, Point rightDownSquare, std::string text, 
            double amplitude = 10, double frequency = 100, 
            Color color = Color(0, 0, 0), int textSize = 16);
    SinSquareText(SinSquare& sinSquare, Text& text);

    std::vector<Point> getAllPoints() const override;
    void move(Point delta) override;

protected:
    std::ostream& info(std::ostream &os) const override;
};