#include "music.h"

Music::Music(string name, string descr, string genre, string country, int year, float cost, int stars, float min, string company, string sin)
    : DigitalProduct(name, descr, genre, country, year, cost, stars, min, company), singer(sin){}

Music::~Music(){}

string Music::getSinger() const{
    return singer;
}

void Music::setSinger(const string& newsinger){
    singer = newsinger;
}
