#include "Sources/Headers/music.h "

Music::Music(string name, string descr, string genre, string country, int year, float cost, int stars, string company, string sin, int min)
    : DigitalProduct(name, descr, genre, country, year, cost, stars, company), singer(sin), minutes(min){}

Music::~Music(){}

string Music::getSinger() const{
    return singer;
}

void Music::setSinger(const string& newsinger){
    singer = newsinger;
}

string Music::getAlbum() const{
    return album;
}

void Music::setAlbum(const string& newalbum){
    album = newalbum;
}

int Music::getMinutes() const {
    return minutes;
}

void Music::setMinutes(int& newminutes){
    minutes = newminutes;
}
