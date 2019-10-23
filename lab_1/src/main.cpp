#include <iostream>

#include "point.hpp"
#include "color.hpp"
#include "sinsquare.hpp"
#include "sinwave.hpp"
#include "text.hpp"
#include "sinsquaretext.hpp"

int main(){
    Point point(10, 20);
    std::cout << point << std::endl;

    Color color1(10, 20, 30);
    std::cout << color1 << std::endl;
    
    Color color2("#FF0010");
    std::cout << color2 <<std::endl;

    SinWave sinWave(Point(0, 0), Point(10, 20), 10, 2);
    std::cout << sinWave << std::endl;

    SinSquare sinSquare(Point(0, 1), Point(1, 0), 2, 3);
    std::cout << sinSquare << std::endl;

    Text text("hello", Point(1, 0), Point(0, 1), Color(10, 20, 30), 14);
    std::cout << text << std::endl;

    SinSquareText sinSquareText(Point(0, 1), Point(0, 1), "test", 10, 100, Color(10, 20, 30), 14);
    std::cout << sinSquareText << std::endl;

    SinSquareText sinSquareText2(sinSquare, text);
    std::cout << sinSquareText2 << std::endl;

    return 0;
}