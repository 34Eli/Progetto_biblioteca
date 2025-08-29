#include "xmlreader.h"
#include <QDebug>

XmlReader::XmlReader() {}

QList<Product*> XmlReader::readAll(const QString &filename) {
    QList<Product*> library;
     //apertura file XML;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Impossibile aprire il file XML";
        return library;
    }

    QXmlStreamReader xml(&file);

    while (!xml.atEnd() && !xml.hasError()) {
        //ciclo di lettura del prossimo token
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
            //aggiungo oggetto alla lista
            if (product != nullptr) library.append(product);
        }
    }
    //controllo eventuali errori
    if (xml.hasError())
        qWarning() << "Errore parsing XML:" << xml.errorString();

    xml.clear();
    return library;
}


XmlReader::ProductData XmlReader::readProduct(QXmlStreamReader &xml) {
    ProductData prod;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
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

    return prod;
}

XmlReader::DigitalData XmlReader::readDigital(QXmlStreamReader &xml) {
    DigitalData dig;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == "company") dig.company = xml.readElementText();
        }
    }

    return dig;
}

XmlReader::PhysicalData XmlReader::readPhysical(QXmlStreamReader &xml) {
    PhysicalData phy;

    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Product")) {
        xml.readNext();
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            if (xml.name() == "author") phy.author = xml.readElementText();
        }
    }

    return phy;
}

Film* XmlReader::readFilm(QXmlStreamReader &xml) {
    ProductData prod = readProduct(xml);
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
                    mainActor.toStdString(), minutes);
}

Music* XmlReader::readMusic(QXmlStreamReader &xml) {
    ProductData prod = readProduct(xml);
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
                     album.toStdString(), minutes);
}

Videogame* XmlReader::readVideogame(QXmlStreamReader &xml) {
    ProductData prod = readProduct(xml);
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
                         isMultiplayer);
}

Book* XmlReader::readBook(QXmlStreamReader &xml) {
    ProductData prod = readProduct(xml);
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
                    publisher.toStdString(), ISBN);
}

Photograph* XmlReader::readPhotograph(QXmlStreamReader &xml) {
    ProductData prod = readProduct(xml);
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
                          phy.author.toStdString(), isColourful, length, width);
}
