#include "Sources/Headers/photograph.h"

Photograph::Photograph(string name, string descr, string genre, string country, int year, float cost, int stars, string author, bool colour, int length, int width)
    : PhysicalProduct(name, descr, genre, country, year, cost, stars, author), isColourful(colour), length(length), width(width){}

Photograph::~Photograph(){}

bool Photograph::getIsColourful() const{
    return isColourful;
}

void Photograph::setIsColourful(bool& newcolour){
    isColourful = newcolour;
}

int Photograph::getLength() const{
    return length;
}

void Photograph::setLength(int& newlength){
    length = newlength;
}

int Photograph::getWidth() const{
    return width;
}

void Photograph::setWidth(int& newwidth){
    width = newwidth;
}
