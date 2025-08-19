#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
using std::string;

class Visitor;

class Product {

    private:
        string name;
        string description;
        string genre;
        string country;
        int year_of_publication;
        int cost;
        int stars;

    public:
        Product(string name, string descr, string genre, string country, int year, int cost, int stars);
        ~Product();
        string getName() const;
        void setName(const string& newname);
        string getDescription() const;
        void setDescription(const string& newdescription);
        string getGenre() const;
        void setGenre(const string& newgenre);
        string getCountry() const;
        void setCountry(const string& newcountry);
        int getYear() const;
        void setYear(int newyear);
        int getCost() const;
        void setCost(int newcost);
        int getStars() const;
        void setStars(int newstars);
        virtual void accept(Visitor& visitor) = 0;
};

#endif // PRODUCT_H
