#ifndef LIBRARY_H
#define LIBRARY_H
#include "Sources/Headers/Product.h"
#include <list>

class Library {
    private:
        std::list<Product*> library;
    public:
        Library();
};

#endif // LIBRARY_H
