#include <ctime>
#include <iostream>
#include <random>
#include "gtest/gtest.h"

#include "point.hpp"
#include "color.hpp"
#include "sinsquare.hpp"
#include "sinwave.hpp"
#include "text.hpp"
#include "sinsquaretext.hpp"
#include "listset.hpp"


TEST(PointTest, PointTestCreation) {
   double x = 3.0;
   double y = 4.0;

    Point p1(x, y);
    Point p2;
    Point p3(p1);

    EXPECT_DOUBLE_EQ(p1.getX(), x);
    EXPECT_DOUBLE_EQ(p1.getY(), y);

    EXPECT_DOUBLE_EQ(p2.getX(), 0.0);
    EXPECT_DOUBLE_EQ(p2.getY(), 0.0);
    
    EXPECT_DOUBLE_EQ(p3.getX(), x);
    EXPECT_DOUBLE_EQ(p3.getY(), y);   


    Point p4(4.0, 5.0);
    Point p5 = p4 + p1;
    EXPECT_DOUBLE_EQ(p5.getX(), 4.0 + x);
    EXPECT_DOUBLE_EQ(p5.getY(), 5.0 + y);  

    p5 = p5 * 5.0;
    EXPECT_DOUBLE_EQ(p5.getX(), 5.0 * (4.0 + x));
    EXPECT_DOUBLE_EQ(p5.getY(), 5.0 * (5.0 + y));  
}

TEST(sinwave, sinwave){
    SinWave sinwave(Point(0, 0), Point(1, 1), 2, 3, Color(10, 20, 30));

    sinwave.move(Point(1, 1));

    EXPECT_DOUBLE_EQ(sinwave.getCenterPoint().getX(), 0.5 + 1);
    EXPECT_DOUBLE_EQ(sinwave.getCenterPoint().getY(), 0.5 + 1);


    EXPECT_DOUBLE_EQ(sinwave.getColor().getR(), 10);
    EXPECT_DOUBLE_EQ(sinwave.getColor().getG(), 20);
    EXPECT_DOUBLE_EQ(sinwave.getColor().getB(), 30);    
}

TEST(text, text){
    Text text("helloworld", Point(0, 0), Point(1, 1), Color(10, 20, 30), 18);

    text.move(Point(1, 1));

    EXPECT_DOUBLE_EQ(text.getCenterPoint().getX(), 0.5 + 1);
    EXPECT_DOUBLE_EQ(text.getCenterPoint().getY(), 0.5 + 1);

    ASSERT_EQ(text.getText(), "helloworld");

    EXPECT_DOUBLE_EQ(text.getColor().getR(), 10);
    EXPECT_DOUBLE_EQ(text.getColor().getG(), 20);
    EXPECT_DOUBLE_EQ(text.getColor().getB(), 30);    
}

TEST(sinsquare, sinsquare){
    SinSquare sinsquare(Point(0, 1), Point(0, 1), 10, 100, Color(10, 20, 30));

    auto points = sinsquare.getAllPoints();

    EXPECT_DOUBLE_EQ(points[0].getX(), 0);
    EXPECT_DOUBLE_EQ(points[0].getY(), 1);
    EXPECT_DOUBLE_EQ(points[1].getX(), 0);
    EXPECT_DOUBLE_EQ(points[1].getY(), 1);
    EXPECT_DOUBLE_EQ(points[2].getX(), 0);
    EXPECT_DOUBLE_EQ(points[2].getY(), 1);
    EXPECT_DOUBLE_EQ(points[3].getX(), 0);
    EXPECT_DOUBLE_EQ(points[3].getY(), 1);
    
    EXPECT_DOUBLE_EQ(sinsquare.getColor().getR(), 10);
    EXPECT_DOUBLE_EQ(sinsquare.getColor().getG(), 20);
    EXPECT_DOUBLE_EQ(sinsquare.getColor().getB(), 30);    
}


TEST(container, container){
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

    std::vector<int> correct = {-435, -3, -2, -1, 0, 1, 2, 3, 4};
    int i = 0;
    for (auto it = listset.begin(); it != listset.end(); it++, i++)
        EXPECT_EQ(correct[i], *it);
}

TEST(container, addFigures){
    SinWave sinWave(Point(0, 0), Point(10, 20), 10, 2);
    Text text("hello", Point(1, 0), Point(0, 1), Color(10, 20, 30), 14);
	SinSquare sinSquare(Point(0, 1), Point(1, 0), 2, 3);
    SinSquareText sinSquareText(Point(0, 1), Point(0, 1), "test", 10, 100, Color(10, 20, 30), 14);
    SinSquareText sinSquareText2(sinSquare, text);


    ListSet<Shape*> listset;
    listset.insert(&sinWave);
    listset.insert(&text);
	listset.insert(&sinSquare);
	listset.insert(&sinSquareText);
	listset.insert(&sinSquareText2);
	
    // Expect added 5 figures
    EXPECT_EQ(listset.size(), 5);
    
    // First figure sinWave
    auto it = listset.begin();
    EXPECT_EQ((*it)->getCenterPoint().getX(), sinWave.getCenterPoint().getX());
    EXPECT_EQ((*it)->getCenterPoint().getY(), sinWave.getCenterPoint().getY());

    // Next figure
    it++;
    EXPECT_EQ((*it)->getCenterPoint().getX(), text.getCenterPoint().getX());
    EXPECT_EQ((*it)->getCenterPoint().getY(), text.getCenterPoint().getY());
}

TEST(container, addSimiliarFigures){
    ListSet<Shape*> listset;

    SinWave sinWave(Point(0, 0), Point(10, 20), 10, 2);

    listset.insert(&sinWave);
    listset.insert(&sinWave);
    listset.insert(&sinWave);
    listset.insert(&sinWave);
    listset.insert(&sinWave);
    listset.insert(&sinWave);

    EXPECT_EQ(listset.size(), 1);
}

TEST(container, testUnion){
    ListSet<int> listset1;
    ListSet<int> listset2;

    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {4, 5, 6, 7};
    std::vector<int> expected_union = {1, 2, 3, 4, 5, 6, 7};
    
    for (auto& v : v1)
        listset1.insert(v);

    for (auto& v : v2)
        listset2.insert(v);

    ListSet<int> unionList = listset1 + listset2;

    size_t i =0;
    for (auto it = unionList.begin(); it != unionList.end(); it++){
        EXPECT_EQ(*it, expected_union[i++]);
    }        
}

TEST(container, testIntersection){
    ListSet<int> listset1;
    ListSet<int> listset2;

    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {4, 5, 6, 7};
    std::vector<int> expected_intersection = {4, 5};
    
    for (auto& v : v1)
        listset1.insert(v);

    for (auto& v : v2)
        listset2.insert(v);

    ListSet<int> intersectionList = listset1.intersectionWith(listset2);

    int i = 0;
    for (auto it = intersectionList.begin(); it != intersectionList.end(); it++){
        EXPECT_EQ(*it, expected_intersection[i++]);
    }        
}

TEST(container, testDiv){
    ListSet<int> listset1;
    ListSet<int> listset2;

    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {4, 5, 6, 7};
    std::vector<int> expected_div = {1, 2, 3};
    
    for (auto& v : v1)
        listset1.insert(v);

    for (auto& v : v2)
        listset2.insert(v);

    ListSet<int> divList = listset1 - listset2;

    int i =0;
    for (auto it = divList.begin(); it != divList.end(); it++){
        EXPECT_EQ(*it, expected_div[i++]);
    }        
}


TEST(container, testEqual){
    ListSet<int> listset1;
    ListSet<int> listset2;

    std::vector<int> v1 = {1, 2, 3, 4, 5};

    for (auto& v : v1){
        listset1.insert(v);
        listset2.insert(v);
    }

    EXPECT_EQ(listset2 == listset1, true);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}