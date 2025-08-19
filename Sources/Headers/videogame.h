#ifndef VIDEOGAME_H
#define VIDEOGAME_H
#include "DigitalProduct.h"

class Visitor;


class Videogame : public DigitalProduct {

    private:
        string platform;
        bool isMultiplayer;

    public:
        Videogame(string name, string descr, string genre, string country, int year, int cost, int stars, string company, string plat, bool multiplayer);
        ~Videogame();
        string getPlatform() const;
        void setPlatform(const string& newplatform);
        bool getIsMultiplayer() const;
        void setIsMultiplayer(bool newmultiplayer);
        void accept(Visitor& visitor) override;
};

#endif // VIDEOGAME_H
