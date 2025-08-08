#include "Sources/Headers/book.h"

Book::Book(string name, string descr, string genre, string country, int year, float cost, int stars, string author, int pages, string publ, int ISBN)
    : PhysicalProduct(name, descr, genre, country, year, cost, stars, author), pages(pages), publisher(publ), ISBN(ISBN){}

Book::~Book(){}

int Book::getPages() const{
    return pages;
}

void Book::setPages(int& newpages){
    pages = newpages;
}

string Book::getPublisher() const{
    return publisher;
}

void Book::setPublisher(const string& newpublisher){
    publisher = newpublisher;
}

int Book::getISBN() const{
    return ISBN;
}

void Book::setISBN(int& newISBN){
    ISBN = newISBN;
}
