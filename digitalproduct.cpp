#include "digitalproduct.h"

DigitalProduct::DigitalProduct(string name, string descr, string genre, string country, int year, float cost, int stars, float min, string company)
    : Product(name, descr, genre, country, year, cost, stars), minutes(min), company(company){}

DigitalProduct::~DigitalProduct(){}

float DigitalProduct::getMinutes() const{
    return minutes;
}

void DigitalProduct::setMinutes(float& newminutes){
    minutes = newminutes;
}

string DigitalProduct::getCompany() const{
    return company;
}

void DigitalProduct::setCompany(const string& newcompany){
    company = newcompany;
}
