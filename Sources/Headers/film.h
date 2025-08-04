#ifndef FILM_H
#define FILM_H
#include "DigitalProduct.h"

class Film : public DigitalProduct {

    private:
        string director;
        string mainActor;
        int minutes;

    public:
        Film(string name, string descr, string genre, string country, int year, float cost, int stars, string company, string dir, string actor, int min);
        ~Film();
        string getDirector() const;
        void setDirector(const string& newdirector);
        string getActor() const;
        void setActor(const string& newactor);
        int getMinutes() const;
        void setMinutes(int& newminutes);
};

#endif // FILM_H
