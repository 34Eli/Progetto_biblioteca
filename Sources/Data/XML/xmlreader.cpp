#include "Sources/Data/XML/xmlreader.h"
#include <QDebug>

XmlReader::XmlReader() {}

QList<Product*> XmlReader::readAll(const QString &filename) {
    QList<Product*> library;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Impossibile aprire il file XML";
        return library;
    }

    QXmlStreamReader xml(&file);

    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartElement && xml.name() == "Product") {
            QString type = xml.attributes().value("type").toString();

            Product* product = nullptr;

            if (type == "Film") product = readFilm(xml);
            else if (type == "Music") product = readMusic(xml);
            else if (type == "Videogame") product = readVideogame(xml);
            else if (type == "Book") product = readBook(xml);
            else if (type == "Photograph") product = readPhotograph(xml);
            else qWarning() << "Classe non valida:" << type;
            if (product != nullptr) library.append(product);
        }
    }
    //controllo eventuali errori
    if (xml.hasError())
        qWarning() << "Errore parsing XML:" << xml.errorString();

    xml.clear();
    return library;
}


void XmlReader::readProduct(QXmlStreamReader &xml, ProductData& prod) {
    //ProductData prod;

    /*while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == "name") prod.name = xml.readElementText();
            else if (xml.name() == "description") prod.description = xml.readElementText();
            else if (xml.name() == "genre") prod.genre = xml.readElementText();
            else if (xml.name() == "country") prod.country = xml.readElementText();
            else if (xml.name() == "year_of_publication") prod.year_of_publication = xml.readElementText().toInt();
            else if (xml.name() == "cost") prod.cost = xml.readElementText().toInt();
            else if (xml.name() == "stars") prod.stars = xml.readElementText().toInt();
            else if (xml.name() == "imagePath") prod.imagePath = xml.readElementText();
        }
    }
    return prod;*/

    const QString tag = xml.name().toString();
    const QString value = xml.readElementText();

    if (tag == "name") prod.name = value;
    else if (tag == "description") prod.description = value;
    else if (tag == "genre") prod.genre = value;
    else if (tag == "country") prod.country = value;
    else if (tag == "year_of_publication") prod.year_of_publication = value.toInt();
    else if (tag == "cost") prod.cost = value.toInt();
    else if (tag == "stars") prod.stars = value.toInt();
    else if (tag == "imagePath") prod.imagePath = value;
}

void XmlReader::readDigital(QXmlStreamReader &xml, DigitalData& dig) {
    //DigitalData dig;

    /*while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == "company") dig.company = xml.readElementText();
        }
    }

    return dig;*/
    if (xml.name() == "company")
        dig.company = xml.readElementText();
}

void XmlReader::readPhysical(QXmlStreamReader &xml, PhysicalData& phy) {
    //PhysicalData phy;

    /*while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == "author") phy.author = xml.readElementText();
        }
    }

    return phy;*/
    if (xml.name() == "author")
        phy.author = xml.readElementText();
}

Film* XmlReader::readFilm(QXmlStreamReader &xml) {
    /*ProductData prod = readProduct(xml);
    DigitalData dig = readDigital(xml);

    QString director, mainActor;
    int minutes = 0;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == "director") director = xml.readElementText();
            else if (xml.name() == "mainActor") mainActor = xml.readElementText();
            else if (xml.name() == "minutes") minutes = xml.readElementText().toInt();
        }
    }

    return new Film(prod.name.toStdString(), prod.description.toStdString(),
                    prod.genre.toStdString(), prod.country.toStdString(),
                    prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                    dig.company.toStdString(), director.toStdString(),
                    mainActor.toStdString(), minutes);*/
    ProductData prod;
    DigitalData dig;
    QString director, mainActor;
    int minutes = 0;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();

        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            QString tag = xml.name().toString();

            if (tag == "company") readDigital(xml, dig);
            else if (tag == "director") director = xml.readElementText();
            else if (tag == "mainActor") mainActor = xml.readElementText();
            else if (tag == "minutes") minutes = xml.readElementText().toInt();
            else readProduct(xml, prod);
        }
    }

    return new Film(prod.name.toStdString(), prod.description.toStdString(),
                    prod.genre.toStdString(), prod.country.toStdString(),
                    prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                    dig.company.toStdString(), director.toStdString(),
                    mainActor.toStdString(), minutes);

}

Music* XmlReader::readMusic(QXmlStreamReader &xml) {
    /*ProductData prod = readProduct(xml);
    DigitalData dig = readDigital(xml);

    QString singer, album;
    int minutes = 0;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == "singer") singer = xml.readElementText();
            else if (xml.name() == "album") album = xml.readElementText();
            else if (xml.name() == "minutes") minutes = xml.readElementText().toInt();
        }
    }

    return new Music(prod.name.toStdString(), prod.description.toStdString(),
                     prod.genre.toStdString(), prod.country.toStdString(),
                     prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                     dig.company.toStdString(), singer.toStdString(),
                     album.toStdString(), minutes);*/
    ProductData prod;
    DigitalData dig;
    QString singer, album;
    int minutes = 0;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();

        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            QString tag = xml.name().toString();

            if (tag == "company") readDigital(xml, dig);
            else if (tag == "singer") singer = xml.readElementText();
            else if (tag == "album") album = xml.readElementText();
            else if (tag == "minutes") minutes = xml.readElementText().toInt();
            else readProduct(xml, prod);
        }
    }

    return new Music(prod.name.toStdString(), prod.description.toStdString(),
                     prod.genre.toStdString(), prod.country.toStdString(),
                     prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                     dig.company.toStdString(), singer.toStdString(),
                     album.toStdString(), minutes);
}

Videogame* XmlReader::readVideogame(QXmlStreamReader &xml) {
    /*ProductData prod = readProduct(xml);
    DigitalData dig = readDigital(xml);

    QString platform;
    bool isMultiplayer = false;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == "platform") platform = xml.readElementText();
            else if (xml.name() == "isMultiplayer") isMultiplayer = (xml.readElementText() == "true");
        }
    }

    return new Videogame(prod.name.toStdString(), prod.description.toStdString(),
                         prod.genre.toStdString(), prod.country.toStdString(),
                         prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                         dig.company.toStdString(), platform.toStdString(),
                         isMultiplayer);*/
    ProductData prod;
    DigitalData dig;
    QString platform;
    bool isMultiplayer = false;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();

        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            QString tag = xml.name().toString();

            if (tag == "company") readDigital(xml, dig);
            else if (tag == "platform") platform = xml.readElementText();
            else if (tag == "isMultiplayer") isMultiplayer = (xml.readElementText() == "true");
            else readProduct(xml, prod);
        }
    }

    return new Videogame(prod.name.toStdString(), prod.description.toStdString(),
                         prod.genre.toStdString(), prod.country.toStdString(),
                         prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                         dig.company.toStdString(), platform.toStdString(),
                         isMultiplayer);
}

Book* XmlReader::readBook(QXmlStreamReader &xml) {
    /*ProductData prod = readProduct(xml);
    PhysicalData phy = readPhysical(xml);

    int pages = 0;
    QString publisher;
    int ISBN = 0;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == "pages") pages = xml.readElementText().toInt();
            else if (xml.name() == "publisher") publisher = xml.readElementText();
            else if (xml.name() == "ISBN") ISBN = xml.readElementText().toInt();
        }
    }

    return new Book(prod.name.toStdString(), prod.description.toStdString(),
                    prod.genre.toStdString(), prod.country.toStdString(),
                    prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                    phy.author.toStdString(), pages,
                    publisher.toStdString(), ISBN);*/
    ProductData prod;
    PhysicalData phy;
    int pages = 0, ISBN = 0;
    QString publisher;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();

        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            QString tag = xml.name().toString();

            if (tag == "author") readPhysical(xml, phy);
            else if (tag == "pages") pages = xml.readElementText().toInt();
            else if (tag == "publisher") publisher = xml.readElementText();
            else if (tag == "ISBN") ISBN = xml.readElementText().toInt();
            else readProduct(xml, prod);
        }
    }

    return new Book(prod.name.toStdString(), prod.description.toStdString(),
                    prod.genre.toStdString(), prod.country.toStdString(),
                    prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                    phy.author.toStdString(), pages,
                    publisher.toStdString(), ISBN);
}

Photograph* XmlReader::readPhotograph(QXmlStreamReader &xml) {
    /*ProductData prod = readProduct(xml);
    PhysicalData phy = readPhysical(xml);

    bool isColourful = false;
    int length = 0, width = 0;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == "isColourful") isColourful = (xml.readElementText() == "true");
            else if (xml.name() == "length") length = xml.readElementText().toInt();
            else if (xml.name() == "width") width = xml.readElementText().toInt();
        }
    }

    return new Photograph(prod.name.toStdString(), prod.description.toStdString(),
                          prod.genre.toStdString(), prod.country.toStdString(),
                          prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                          phy.author.toStdString(), isColourful, length, width);*/
    ProductData prod;
    PhysicalData phy;
    bool isColourful = false;
    int length = 0, width = 0;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();

        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            QString tag = xml.name().toString();

            if (tag == "author") readPhysical(xml, phy);
            else if (tag == "isColourful") isColourful = (xml.readElementText() == "true");
            else if (tag == "length") length = xml.readElementText().toInt();
            else if (tag == "width") width = xml.readElementText().toInt();
            else readProduct(xml, prod);
        }
    }

    return new Photograph(prod.name.toStdString(), prod.description.toStdString(),
                          prod.genre.toStdString(), prod.country.toStdString(),
                          prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(),
                          phy.author.toStdString(), isColourful, length, width);
}
