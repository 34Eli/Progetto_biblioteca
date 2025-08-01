#include "PhysicalProduct.h"

PhysicalProduct::PhysicalProduct(string name, string descr, string genre, string country, int year, float cost, int stars, string author)
    :Product(name, descr, genre, country, year, cost, stars), author(author){}

PhysicalProduct::~PhysicalProduct(){}

string PhysicalProduct::getAuthor() const{
    return author;
}

void PhysicalProduct::setAuthor(const string& newauthor){
    author = newauthor;
}
