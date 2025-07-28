#ifndef BOOK_H
#define BOOK_H
#include "PhysicalProduct.h"

class Book : public PhysicalProduct {

    private:
        int pages;
        string publisher;

    public:
        Book(string name, string descr, string genre, string country, int year, float cost, int stars, string author, int pages, string publ);
        ~Book();
        int getPages() const;
        void setPages(int& newpages);
        string getPublisher() const;
        void setPublisher(const string& newpublisher);
};

#endif // BOOK_H
