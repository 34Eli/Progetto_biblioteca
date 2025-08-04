#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
using std::string;

class Product {

    private:
        string name;
        string description;
        string genre;
        string country;
        int year_of_publication;
        float cost;
        int stars;

    public:
        Product(string name, string descr, string genre, string country, int year, float cost, int stars);
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
        void setYear(int& newyear);
        float getCost() const;
        void setCost(float& newcost);
        float getStars() const;
        void setStars(float& newstars);
};

#endif // PRODUCT_H
