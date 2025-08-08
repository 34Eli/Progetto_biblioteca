#include "Sources/Headers/film.h"

Film::Film(string name, string descr, string genre, string country, int year, float cost, int stars, string company, string dir, string actor, int min)
    : DigitalProduct(name, descr, genre, country, year, cost, stars, company), director(dir), mainActor(actor), minutes(min){}

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

int Film::getMinutes() const {
    return minutes;
}

void Film::setMinutes(int& newminutes){
    minutes = newminutes;
}
