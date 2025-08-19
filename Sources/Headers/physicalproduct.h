#ifndef PHYSICALPRODUCT_H
#define PHYSICALPRODUCT_H
#include "Product.h"

class PhysicalProduct : public Product {

    private:
        string author;

    public:
        PhysicalProduct(string name, string descr, string genre, string country, int year, int cost, int stars, string author);
        ~PhysicalProduct();
        string getAuthor() const;
        void setAuthor(const string& newauthor);
        void accept(Visitor& visitor) override = 0;
};

#endif // PHYSICALPRODUCT_H
