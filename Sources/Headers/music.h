#ifndef MUSIC_H
#define MUSIC_H
#include "DigitalProduct.h"

class Music : public DigitalProduct {

    private:
        string singer;
        string album;
        int minutes;

    public:
        Music(string name, string descr, string genre, string country, int year, int cost, int stars, string company, string sing, string alb, int min);
        ~Music();
        string getSinger() const;
        void setSinger(const string& newsinger);
        string getAlbum() const;
        void setAlbum(const string& newalbum);
        int getMinutes() const;
        void setMinutes(int newminutes);
};

#endif // MUSIC_H
