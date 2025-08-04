#include "videogame.h"

Videogame::Videogame(string name, string descr, string genre, string country, int year, float cost, int stars, string company, string plat, bool multiplayer)
    : DigitalProduct(name, descr, genre, country, year, cost, stars, company), platform(plat), isMultiplayer(multiplayer){}

Videogame::~Videogame(){}

string Videogame::getPlatform() const{
    return platform;
}

void Videogame::setPlatform(const string& newplatform){
    platform = newplatform;
}

bool Videogame::getIsMultiplayer() const{
    return isMultiplayer;
}

void Videogame::setIsMultiplayer(bool& newmultiplayer){
    isMultiplayer = newmultiplayer;
}
