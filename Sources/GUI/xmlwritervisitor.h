#ifndef XMLWRITERVISITOR_H
#define XMLWRITERVISITOR_H

#include <QtXml/QDomDocument>
#include "Sources/Model/visitor.h"
#include "Sources/Headers/product.h"
#include "Sources/Headers/digitalproduct.h"
#include "Sources/Headers/physicalproduct.h"
#include "Sources/Headers/film.h"
#include "Sources/Headers/book.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"
#include "Sources/Headers/photograph.h"

class XmlWriterVisitor : public Visitor {
private:
    QDomDocument doc;
    QDomElement root;

    void productFields(const Product& p, QDomElement& elem);

    void digitalFields(const DigitalProduct& d, QDomElement& elem);

    void physicalFields(const PhysicalProduct& p, QDomElement& elem);

public:
    XmlWriterVisitor();

    void visitFilm(Film& f) override;
    void visitBook(Book& b) override;
    void visitMusic(Music& m) override;
    void visitPhotograph(Photograph& p) override;
    void visitVideogame(Videogame& v) override;

    QDomDocument getXmlDocument() const;
};

#endif // XMLWRITERVISITOR_H
