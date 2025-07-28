#ifndef FILM_H
#define FILM_H
#include "DigitalProduct.h"

class Film : public DigitalProduct {

    private:
        string director;
        string mainActor;

    public:
        Film(string name, string descr, string genre, string country, int year, float cost, int stars, float min, string company, string dir, string actor);
        ~Film();
        string getDirector() const;
        void setDirector(const string& newdirector);
        string getActor() const;
        void setActor(const string& newactor);
};

#endif // FILM_H
