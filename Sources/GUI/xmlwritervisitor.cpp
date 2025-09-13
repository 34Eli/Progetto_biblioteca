#include "xmlwritervisitor.h"
#include <QString>

XmlWriterVisitor::XmlWriterVisitor(QDomDocument& doc) : doc(doc) {
    root = doc.createElement("Products");
    doc.appendChild(root);
}

void XmlWriterVisitor::productFields(const Product& p, QDomElement& elem) {
    QDomElement name = doc.createElement("name");
    name.appendChild(doc.createTextNode(QString::fromStdString(p.getName())));
    elem.appendChild(name);

    QDomElement desc = doc.createElement("description");
    desc.appendChild(doc.createTextNode(QString::fromStdString(p.getDescription())));
    elem.appendChild(desc);

    QDomElement genre = doc.createElement("genre");
    genre.appendChild(doc.createTextNode(QString::fromStdString(p.getGenre())));
    elem.appendChild(genre);

    QDomElement country = doc.createElement("country");
    country.appendChild(doc.createTextNode(QString::fromStdString(p.getCountry())));
    elem.appendChild(country);

    QDomElement year = doc.createElement("year_of_publication");
    year.appendChild(doc.createTextNode(QString::number(p.getYear())));
    elem.appendChild(year);

    QDomElement cost = doc.createElement("cost");
    cost.appendChild(doc.createTextNode(QString::number(p.getCost())));
    elem.appendChild(cost);

    QDomElement stars = doc.createElement("stars");
    stars.appendChild(doc.createTextNode(QString::number(p.getStars())));
    elem.appendChild(stars);
}

void XmlWriterVisitor::digitalFields(const DigitalProduct& d, QDomElement& elem) {
    QDomElement company = doc.createElement("company");
    company.appendChild(doc.createTextNode(QString::fromStdString(d.getCompany())));
    elem.appendChild(company);
}

void XmlWriterVisitor::physicalFields(const PhysicalProduct& p, QDomElement& elem) {
    QDomElement author = doc.createElement("author");
    author.appendChild(doc.createTextNode(QString::fromStdString(p.getAuthor())));
    elem.appendChild(author);
}

void XmlWriterVisitor::visitFilm(Film& f) {
    QDomElement filmElem = doc.createElement("Film");
    productFields(f, filmElem);
    digitalFields(f, filmElem);

    QDomElement director = doc.createElement("director");
    director.appendChild(doc.createTextNode(QString::fromStdString(f.getDirector())));
    filmElem.appendChild(director);

    QDomElement actor = doc.createElement("actor");
    actor.appendChild(doc.createTextNode(QString::fromStdString(f.getActor())));
    filmElem.appendChild(actor);

    QDomElement minutes = doc.createElement("minutes");
    minutes.appendChild(doc.createTextNode(QString::number(f.getMinutes())));
    filmElem.appendChild(minutes);

    root.appendChild(filmElem);
}

void XmlWriterVisitor::visitBook(Book& b) {
    QDomElement bookElem = doc.createElement("Book");
    productFields(b, bookElem);
    physicalFields(b, bookElem);

    QDomElement pages = doc.createElement("pages");
    pages.appendChild(doc.createTextNode(QString::number(b.getPages())));
    bookElem.appendChild(pages);

    QDomElement publisher = doc.createElement("publisher");
    publisher.appendChild(doc.createTextNode(QString::fromStdString(b.getPublisher())));
    bookElem.appendChild(publisher);

    root.appendChild(bookElem);
}

void XmlWriterVisitor::visitMusic(Music& m) {
    QDomElement musicElem = doc.createElement("Music");
    productFields(m, musicElem);
    digitalFields(m, musicElem);

    QDomElement minutes = doc.createElement("minutes");
    minutes.appendChild(doc.createTextNode(QString::number(m.getMinutes())));
    musicElem.appendChild(minutes);

    QDomElement singer = doc.createElement("singer");
    singer.appendChild(doc.createTextNode(QString::fromStdString(m.getSinger())));
    musicElem.appendChild(singer);

    QDomElement album = doc.createElement("album");
    album.appendChild(doc.createTextNode(QString::fromStdString(m.getAlbum())));
    musicElem.appendChild(album);

    root.appendChild(musicElem);
}

void XmlWriterVisitor::visitPhotograph(Photograph& p) {
    QDomElement photoElem = doc.createElement("Photograph");
    productFields(p, photoElem);
    physicalFields(p, photoElem);

    QDomElement isColourful = doc.createElement("isColourful");
    isColourful.appendChild(doc.createTextNode(p.getIsColourful() ? "true" : "false"));
    photoElem.appendChild(isColourful);

    QDomElement length = doc.createElement("length");
    length.appendChild(doc.createTextNode(QString::number(p.getLength())));
    photoElem.appendChild(length);

    QDomElement width = doc.createElement("width");
    width.appendChild(doc.createTextNode(QString::number(p.getWidth())));
    photoElem.appendChild(width);

    root.appendChild(photoElem);
}

void XmlWriterVisitor::visitVideogame(Videogame& v) {
    QDomElement vgElem = doc.createElement("Videogame");
    productFields(v, vgElem);
    digitalFields(v, vgElem);

    QDomElement platform = doc.createElement("platform");
    platform.appendChild(doc.createTextNode(QString::fromStdString(v.getPlatform())));
    vgElem.appendChild(platform);

    QDomElement multiplayer = doc.createElement("isMultiplayer");
    multiplayer.appendChild(doc.createTextNode(v.getIsMultiplayer() ? "true" : "false"));
    vgElem.appendChild(multiplayer);

    root.appendChild(vgElem);
}

QDomDocument& XmlWriterVisitor::getXmlDocument() const {
    return doc;
}
