#ifndef VISITOR_H
#define VISITOR_H
#include "Sources/Headers/book.h"
#include "Sources/Headers/photograph.h"
#include "Sources/Headers/film.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"

class Visitor{

    public:
        Visitor();
        virtual void visitFilm(Film* f) = 0;
        virtual void visitBook(Book* b) = 0;
        virtual void visitMusic(Music* m) = 0;
        virtual void visitPhotograph(Photograph* p) = 0;
        virtual void visitVideogame(Videogame* v) = 0;
        virtual ~Visitor() = default;
};

#endif // VISITOR_H
