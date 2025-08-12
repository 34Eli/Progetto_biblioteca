#ifndef DIGITALPRODUCT_H
#define DIGITALPRODUCT_H
#include "Product.h"

class DigitalProduct : public Product {

private:
        string company;

    public:
        DigitalProduct(string name, string descr, string genre, string country, int year, int cost, int stars, string company);
        ~DigitalProduct();
        string getCompany() const;
        void setCompany(const string& newcompany);
};

#endif // DIGITALPRODUCT_H
