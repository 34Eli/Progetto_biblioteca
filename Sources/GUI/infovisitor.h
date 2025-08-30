#ifndef INFOVISITOR_H
#define INFOVISITOR_H

#include <QWidget>

//dichiaro nomi classi
class Film;
class Book;
class Music;
class Videogame;
class Photograph;

class InfoVisitor {
public:
    //costruttore di default
    InfoVisitor() = default;

    //dichiarazione dei metodi visit
    QWidget* visit(Film& f);
    QWidget* visit(Videogame& v);
    QWidget* visit(Music& m);
    QWidget* visit(Book& b);
    QWidget* visit(Photograph& p);

    //distruttore di default
    ~InfoVisitor() = default;
};

#endif

