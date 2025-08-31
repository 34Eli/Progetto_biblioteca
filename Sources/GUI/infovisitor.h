#ifndef INFOVISITOR_H
#define INFOVISITOR_H

#include "Sources/Model/visitor.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class InfoVisitor : public Visitor {
public:
    InfoVisitor() = default;
    ~InfoVisitor() override = default;

    // Ridefinizione dei metodi visit
    void visitFilm(Film& f) override;
    void visitBook(Book& b) override;
    void visitMusic(Music& m) override;
    void visitPhotograph(Photograph& p) override;
    void visitVideogame(Videogame& v) override;

    QWidget* getWidget() const { return widget; }

private:
    QWidget* widget = nullptr;  // contiene il layout creato durante la visita
};

#endif // INFOVISITOR_H
