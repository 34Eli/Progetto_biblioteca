#include "film.h"

Film::Film(string name, string descr, string genre, string country, int year, float cost, int stars, float min, string company, string dir, string actor)
    : DigitalProduct(name, descr, genre, country, year, cost, stars, min, company), director(dir), mainActor(actor){}

Film::~Film(){}

string Film::getDirector() const{
    return director;
}

void Film::setDirector(const string& newdirector){
    director = newdirector;
}

string Film::getActor() const{
    return mainActor;
}

void Film::setActor(const string& newactor){
    mainActor = newactor;
}
