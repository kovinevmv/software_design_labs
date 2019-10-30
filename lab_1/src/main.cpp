#include <iostream>

#include "point.hpp"
#include "color.hpp"
#include "sinsquare.hpp"
#include "sinwave.hpp"
#include "text.hpp"
#include "sinsquaretext.hpp"

#include "listset.hpp"

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
    
    ListSet<int> listset;
    listset.insert(1);
    listset.insert(2);
    listset.insert(3);
    listset.insert(3);
    listset.insert(4);
    listset.insert(4);
    
    listset.insert(1);
    listset.insert(1);
    listset.insert(1);
    listset.insert(1);
    listset.insert(1);
    listset.insert(1);
    listset.insert(-2);
    listset.insert(0);
    listset.insert(3);
    listset.insert(-3);
    listset.insert(-435);
    listset.insert(-1);
    
    
    std::cout << "List: ";
    for (auto it = listset.begin(); it != listset.end(); it++){
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
    

    return 0;
}