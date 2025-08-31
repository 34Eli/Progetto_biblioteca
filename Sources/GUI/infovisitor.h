#ifndef INFOVISITOR_H
#define INFOVISITOR_H

#include "Sources/Model/visitor.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class InfoVisitor : public Visitor {

    private:
        QWidget* widget = nullptr;

    public:
        InfoVisitor() = default;
        ~InfoVisitor() override = default;

        void visitFilm(Film& f) override;
        void visitBook(Book& b) override;
        void visitMusic(Music& m) override;
        void visitPhotograph(Photograph& p) override;
        void visitVideogame(Videogame& v) override;

        QWidget* commonSetUp(Product& p);

        QWidget* getWidget() const;


};

#endif // INFOVISITOR_H
