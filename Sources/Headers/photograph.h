#ifndef PHOTOGRAPH_H
#define PHOTOGRAPH_H
#include "PhysicalProduct.h"

class Photograph : public PhysicalProduct {

    private:
        bool isColourful;
        int length;
        int width;

    public:
        Photograph(string name, string descr, string genre, string country, int year, int cost, int stars, string author, bool colour, int length, int width);
        ~Photograph();
        bool getIsColourful() const;
        void setIsColourful(bool newcolour);
        int getLength() const;
        void setLength(int newlength);
        int getWidth() const;
        void setWidth(int newwidth);
        void accept(Visitor& visitor) override = 0;
};

#endif // PHOTOGRAPH_H
