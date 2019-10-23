#include <color.hpp>
#include <sstream>

Color::Color(unsigned short int r_, unsigned short int g_, unsigned short int b_, unsigned short int alpha_ /*= 255*/) :
    r(r_), g(g_), b(b_), alpha(alpha_) {};
    
Color::Color() : Color(0, 0, 0) {};

Color::Color(const std::string& hexString){
    std::string currentHexString = hexString;

    if(currentHexString.at(0) == '#') {
        currentHexString = currentHexString.substr(1, currentHexString.length());
    }

    std::istringstream(currentHexString.substr(0,2)) >> std::hex >> r;
    std::istringstream(currentHexString.substr(2,2)) >> std::hex >> g;
    std::istringstream(currentHexString.substr(4,2)) >> std::hex >> b;
    alpha = 255;
}

Color::Color(Color &&color) noexcept {
    swap(*this, color);
}

unsigned short int Color::getR() const{
    return this->r;
}

unsigned short int Color::getG() const{
    return this->g;
}

unsigned short int Color::getB() const{
    return this->b;
}
unsigned short int Color::getAlpha() const{
    return this->alpha;
}

void swap(Color &a, Color &b) {
    std::swap(a.r, b.r);
    std::swap(a.g, b.g);
    std::swap(a.b, b.b);
    std::swap(a.alpha, b.alpha);
}

Color &Color::operator=(Color color) {
    swap(*this, color);
    return *this;
}

std::ostream & operator<<(std::ostream & os, const Color& color){
    return os << "Color(" << (int)color.r << "," 
                          << (int)color.g << "," 
                          << (int)color.b << ","
                          << (int)color.alpha << ")";
}

std::istream & operator>> (std::istream & is, Color& color){
    return is >> color.r >> color.g >> color.b >> color.alpha;
}



