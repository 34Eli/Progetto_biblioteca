#include "jsonreader.h"
#include <QFileInfo> //per test


JsonReader::JsonReader() {}

JsonReader::ProductData JsonReader::readProduct(const QJsonObject& obj){
    ProductData prod;
    prod.name = obj["name"].toString();
    prod.description = obj["description"].toString();
    prod.genre = obj["genre"].toString();
    prod.country = obj["country"].toString();
    prod.year_of_publication = obj["year_of_publication"].toInt();
    prod.cost = obj["cost"].toInt();
    prod.stars = obj["stars"].toInt();
    prod.imagePath = obj["imagePath"].toString();
    return prod;
}

JsonReader::DigitalData JsonReader::readDigital(const QJsonObject& obj){
    DigitalData dig;
    dig.company = obj["company"].toString();
    return dig;
}

JsonReader::PhysicalData JsonReader::readPhysical(const QJsonObject& obj){
    PhysicalData phy;
    phy.author = obj["author"].toString();
    return phy;
}


Film* JsonReader::readFilm(const QJsonObject& obj){
    ProductData prod = readProduct(obj);
    DigitalData dig = readDigital(obj);
    QString director = obj["director"].toString();
    QString mainActor = obj["actor"].toString();
    int minutes = obj["minutes"].toInt();
    return new Film(prod.name.toStdString(), prod.description.toStdString(), prod.genre.toStdString(), prod.country.toStdString(), prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(), dig.company.toStdString(), director.toStdString(), mainActor.toStdString(), minutes);
    //ricorda di deferenziare puntatore/sistemare la memoria per sta roba del new Film()
}

Music* JsonReader::readMusic(const QJsonObject& obj){
    ProductData prod = readProduct(obj);
    DigitalData dig = readDigital(obj);
    QString singer = obj["singer"].toString();
    QString album = obj["album"].toString();
    int minutes = obj["minutes"].toInt();
    return new Music(prod.name.toStdString(), prod.description.toStdString(), prod.genre.toStdString(), prod.country.toStdString(), prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(), dig.company.toStdString(), singer.toStdString(), album.toStdString(), minutes);

}

Videogame* JsonReader::readVideogame(const QJsonObject& obj){
    ProductData prod = readProduct(obj);
    DigitalData dig = readDigital(obj);
    QString platform = obj["platform"].toString();
    bool isMultiplayer = obj["isMultiplayer"].toBool();
    return new Videogame(prod.name.toStdString(), prod.description.toStdString(), prod.genre.toStdString(), prod.country.toStdString(), prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(), dig.company.toStdString(), platform.toStdString(), isMultiplayer);
}

Book* JsonReader::readBook(const QJsonObject& obj){
    ProductData prod = readProduct(obj);
    PhysicalData phy = readPhysical(obj);
    int pages = obj["pages"].toInt();
    QString publisher = obj["publisher"].toString();
    int ISBN = obj["ISBN"].toInt();
    return new Book(prod.name.toStdString(), prod.description.toStdString(), prod.genre.toStdString(), prod.country.toStdString(), prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(), phy.author.toStdString(), pages, publisher.toStdString(), ISBN);
}

Photograph* JsonReader::readPhotograph(const QJsonObject& obj){
    ProductData prod = readProduct(obj);
    PhysicalData phy = readPhysical(obj);
    bool isColourful = obj["isColourful"].toBool();
    int length = obj["length"].toInt();
    int width = obj["width"].toInt();
    return new Photograph(prod.name.toStdString(), prod.description.toStdString(), prod.genre.toStdString(), prod.country.toStdString(), prod.year_of_publication, prod.cost, prod.stars, prod.imagePath.toStdString(), phy.author.toStdString(), isColourful, length, width);
}



QList<Product*> JsonReader::readAll(const string& filename){   //restituisce una lista con tutti gli oggetti delle varie classi

    QList<Product*> library;
    QFile file(QString::fromStdString(filename));

    //per test
    //QString filePath = QString::fromStdString(filename);
    //qDebug() << "[DEBUG] Path file richiesto:" << QFileInfo(filePath).absoluteFilePath();
    //per test

    if (!file.open(QIODevice::ReadOnly)){
        qWarning() << "Apertura non ha successo";
        return library;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if(!doc.isArray()){
        qWarning() << "Il file non è un array";
        return library;
    }

    QJsonArray array = doc.array();


    for (const QJsonValue& val : array) {

        if (val.isObject()){

             QJsonObject obj = val.toObject();
             QString type = obj["type"].toString();

             if(type == "Film"){
                 library.append(readFilm(obj));
             }
             else if(type == "Music"){
                 library.append(readMusic(obj));
             }
             else if(type == "Videogame"){
                 library.append(readVideogame(obj));
             }
             else if(type == "Book"){
                 library.append(readBook(obj));
             }
             else if(type == "Photograph"){
                 library.append(readPhotograph(obj));
             }
             else {
                 qWarning() << "Classe non valida";
             }
        }
    }

    return library;
}

