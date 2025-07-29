#include "digitalproduct.h"

DigitalProduct::DigitalProduct(string name, string descr, string genre, string country, int year, float cost, int stars, string company)
    : Product(name, descr, genre, country, year, cost, stars), company(company){}

DigitalProduct::~DigitalProduct(){}

string DigitalProduct::getCompany() const{
    return company;
}

void DigitalProduct::setCompany(const string& newcompany){
    company = newcompany;
}
