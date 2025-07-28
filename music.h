#ifndef MUSIC_H
#define MUSIC_H
#include "DigitalProduct.h"

class Music : public DigitalProduct {

    private:
        string singer;

    public:
        Music(string name, string descr, string genre, string country, int year, float cost, int stars, float min, string company, string sing);
        ~Music();
        string getSinger() const;
        void setSinger(const string& newsinger);
};

#endif // MUSIC_H
