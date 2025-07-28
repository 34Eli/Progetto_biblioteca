#ifndef DIGITALPRODUCT_H
#define DIGITALPRODUCT_H
#include "Product.h"

class DigitalProduct : public Product {

private:
        float minutes;
        string company;

    public:
        DigitalProduct(string name, string descr, string genre, string country, int year, float cost, int stars, float min, string company);
        ~DigitalProduct();
        float getMinutes() const;
        void setMinutes(float& newminutes);
        string getCompany() const;
        void setCompany(const string& newcompany);
};

#endif // DIGITALPRODUCT_H
