#pragma once

#include <inttypes.h>
#include <string>

class Color{
    unsigned short int r;
    unsigned short int g;
    unsigned short int b;
    unsigned short int alpha;

public:
    Color(unsigned short int r_, unsigned short int g_, unsigned short int b_, unsigned short int alpha_ = 255);
    Color();
    Color(const std::string& hex);
    Color(Color&& p) noexcept;
    Color(const Color& p) = default;

    ~Color() = default;

    unsigned short int getR() const;
    unsigned short int getG() const;
    unsigned short int getB() const;
    unsigned short int getAlpha() const;

    Color& operator=(Color p);
    friend std::ostream& operator<<(std::ostream& os, const Color& color);
    friend std::istream& operator>>(std::istream& is, Color& color);

    bool operator==(const Color&);
    bool operator!=(const Color&);

    friend void swap(Color& a, Color& b);   
};