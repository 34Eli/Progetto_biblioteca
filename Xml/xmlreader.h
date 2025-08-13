#ifndef XMLREADER_H
#define XMLREADER_H
#include "Sources/Headers/book.h"
#include "Sources/Headers/photograph.h"
#include "Sources/Headers/film.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"

#include <QList>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>

class XmlReader {

private:

    //gli struct servono per memorizzare gli attributi comuni delle classi concrete
    struct ProductData {
        QString name;
        QString description;
        QString genre;
        QString country;
        int year_of_publication;
        int cost;
        int stars;
    };

    struct DigitalData {
        QString company;
    };

    struct PhysicalData {
        QString author;
    };

    // Metodi per leggere campi dati comuni dai nodi XML
    ProductData readProduct(QXmlStreamReader &xml);
    DigitalData readDigital(QXmlStreamReader &xml);
    PhysicalData readPhysical(QXmlStreamReader &xml);

    // Metodi per creare oggetti concreti
    Film* readFilm(QXmlStreamReader &xml);
    Music* readMusic(QXmlStreamReader &xml);
    Videogame* readVideogame(QXmlStreamReader &xml);
    Book* readBook(QXmlStreamReader &xml);
    Photograph* readPhotograph(QXmlStreamReader &xml);

public:

    XmlReader();

    // Metodo pubblico che legge tutti gli oggetti dal file XML
    QList<Product*> readAll(const QString &filename);
};

#endif // XMLREADER_H
