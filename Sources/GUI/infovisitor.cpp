#include "infovisitor.h"
#include "Sources/Headers/film.h"
#include "Sources/Headers/book.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"
#include "Sources/Headers/photograph.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QObject>
#include <QString>
#include <QCheckBox>

//1.Implementare modify fuori dai visit
//2.delete delle cose precedenti
//3.save e salvare nel json
//4.rendere spin, line
//5.creare un nuovo metodo per gli attributi in comune (product)

QWidget* InfoVisitor::commonSetUp(Product& p){

    QWidget* common = new QWidget;
    QVBoxLayout* commonLayout = new QVBoxLayout();

    QLineEdit* titleEdit = new QLineEdit(QString::fromStdString(p.getName()));
    titleEdit->setReadOnly(true);

    QLineEdit* descrEdit = new QLineEdit(QString::fromStdString(p.getDescription()));
    descrEdit->setReadOnly(true);

    QLineEdit* genreEdit = new QLineEdit(QString::fromStdString(p.getGenre()));
    genreEdit->setReadOnly(true);

    QLineEdit* countryEdit = new QLineEdit(QString::fromStdString(p.getCountry()));
    countryEdit->setReadOnly(true);

    QLineEdit* yearEdit = new QLineEdit(QString::number(p.getYear()));
    yearEdit->setReadOnly(true);

    QLineEdit* costEdit = new QLineEdit(QString::number(p.getCost()));
    costEdit->setReadOnly(true);

    QLineEdit* starsEdit = new QLineEdit(QString::number(p.getStars()));
    starsEdit->setReadOnly(true);

    commonLayout->addWidget(new QLabel("Titolo:"));
    commonLayout->addWidget(titleEdit);
    commonLayout->addWidget(new QLabel("Descrizione:"));
    commonLayout->addWidget(descrEdit);
    commonLayout->addWidget(new QLabel("Genere:"));
    commonLayout->addWidget(genreEdit);
    commonLayout->addWidget(new QLabel("Paese:"));
    commonLayout->addWidget(countryEdit);
    commonLayout->addWidget(new QLabel("Anno:"));
    commonLayout->addWidget(yearEdit);
    commonLayout->addWidget(new QLabel("Prezzo:"));
    commonLayout->addWidget(costEdit);
    commonLayout->addWidget(new QLabel("Valutazione stelle:"));
    commonLayout->addWidget(starsEdit);

    common->setLayout(commonLayout);
    return common;
}


void InfoVisitor::visitFilm(Film& f) {

    QWidget* filmPage = commonSetUp(f);
    QVBoxLayout* filmLayout = new QVBoxLayout();

    QLineEdit* directorEdit = new QLineEdit(QString::fromStdString(f.getDirector()));
    directorEdit->setReadOnly(true);

    QLineEdit* actorEdit = new QLineEdit(QString::fromStdString(f.getActor()));
    actorEdit->setReadOnly(true);

    QSpinBox* minutesEdit = new QSpinBox();
    minutesEdit->setRange(1, 500);
    minutesEdit->setValue(f.getMinutes());
    minutesEdit->setEnabled(false);

    QLineEdit* companyEdit = new QLineEdit(QString::fromStdString(f.getCompany()));
    companyEdit->setReadOnly(true);


    //filmLayout->addWidget(new QLabel("FILM")); come fare per il titolo
    filmLayout->addWidget(new QLabel("Regista:"));
    filmLayout->addWidget(directorEdit);
    filmLayout->addWidget(new QLabel("Attore principale:"));
    filmLayout->addWidget(actorEdit);
    filmLayout->addWidget(new QLabel("Durata (minuti):"));
    filmLayout->addWidget(minutesEdit);
    filmLayout->addWidget(new QLabel("Casa di produzione:"));
    filmLayout->addWidget(companyEdit);

    filmPage->setLayout(filmLayout);
    widget = filmPage;
}


void InfoVisitor::visitVideogame(Videogame& v) {

    QWidget* videogamePage = commonSetUp(v);
    QVBoxLayout* videogameLayout = new QVBoxLayout();

    QLineEdit* companyEdit = new QLineEdit(QString::fromStdString(v.getCompany()));
    companyEdit->setReadOnly(true);

    QLineEdit* platformEdit = new QLineEdit(QString::fromStdString(v.getPlatform()));
    platformEdit->setReadOnly(true);

    QCheckBox* multiplayerBox = new QCheckBox("Multiplayer");
    multiplayerBox->setChecked(v.getIsMultiplayer());
    multiplayerBox->setEnabled(false);

    //videogameLayout->addWidget(new QLabel("VIDEOGAME"));
    videogameLayout->addWidget(new QLabel("Casa di produzione:"));
    videogameLayout->addWidget(companyEdit);
    videogameLayout->addWidget(new QLabel("Piattaforma:"));
    videogameLayout->addWidget(platformEdit);
    videogameLayout->addWidget(multiplayerBox);

    videogamePage->setLayout(videogameLayout);
    widget = videogamePage;
}


void InfoVisitor::visitMusic(Music& m) {

    QWidget* musicPage = commonSetUp(m);
    QVBoxLayout* musicLayout = new QVBoxLayout();

    QLineEdit* companyEdit = new QLineEdit(QString::fromStdString(m.getCompany()));
    companyEdit->setReadOnly(true);

    QLineEdit* singerEdit = new QLineEdit(QString::fromStdString(m.getSinger()));
    singerEdit->setReadOnly(true);

    QLineEdit* albumEdit = new QLineEdit(QString::fromStdString(m.getAlbum()));
    albumEdit->setReadOnly(true);

    QSpinBox* minutesEdit = new QSpinBox();
    minutesEdit->setRange(0, 1000);
    minutesEdit->setValue(m.getMinutes());
    minutesEdit->setEnabled(false);

    //musicLayout->addWidget(new QLabel("MUSIC"));
    musicLayout->addWidget(new QLabel("Casa di produzione:"));
    musicLayout->addWidget(companyEdit);
    musicLayout->addWidget(new QLabel("Cantante:"));
    musicLayout->addWidget(singerEdit);
    musicLayout->addWidget(new QLabel("Album:"));
    musicLayout->addWidget(albumEdit);
    musicLayout->addWidget(new QLabel("Durata minuti:"));
    musicLayout->addWidget(minutesEdit);

    musicPage->setLayout(musicLayout);
    widget = musicPage;
}


void InfoVisitor::visitBook(Book& b) {

    QWidget* bookPage = commonSetUp(b);
    QVBoxLayout* bookLayout = new QVBoxLayout();

    QLineEdit* authorEdit = new QLineEdit(QString::fromStdString(b.getAuthor()));
    authorEdit->setReadOnly(true);

    QSpinBox* pagesEdit = new QSpinBox();
    pagesEdit->setRange(1, 5000);
    pagesEdit->setValue(b.getPages());
    pagesEdit->setEnabled(false);

    QLineEdit* publisherEdit = new QLineEdit(QString::fromStdString(b.getPublisher()));
    publisherEdit->setReadOnly(true);

    QSpinBox* isbnEdit = new QSpinBox();
    isbnEdit->setRange(0, 999999999);
    isbnEdit->setValue(b.getISBN());
    isbnEdit->setEnabled(false);

    //bookLayout->addWidget(new QLabel("BOOK"));
    bookLayout->addWidget(new QLabel("Autore:"));
    bookLayout->addWidget(authorEdit);
    bookLayout->addWidget(new QLabel("Pagine:"));
    bookLayout->addWidget(pagesEdit);
    bookLayout->addWidget(new QLabel("Editore:"));
    bookLayout->addWidget(publisherEdit);
    bookLayout->addWidget(new QLabel("ISBN:"));
    bookLayout->addWidget(isbnEdit);

    bookPage->setLayout(bookLayout);
    widget = bookPage;
}


void InfoVisitor::visitPhotograph(Photograph& p) {

    QWidget* photographPage = commonSetUp(p);
    QVBoxLayout* photographLayout = new QVBoxLayout();

    QLineEdit* authorEdit = new QLineEdit(QString::fromStdString(p.getAuthor()));
    authorEdit->setReadOnly(true);

    QCheckBox* colourBox = new QCheckBox("Colorata");
    colourBox->setChecked(p.getIsColourful());
    colourBox->setEnabled(false);

    QSpinBox* lengthEdit = new QSpinBox();
    lengthEdit->setRange(0, 5000);
    lengthEdit->setValue(p.getLength());
    lengthEdit->setEnabled(false);

    QSpinBox* widthEdit = new QSpinBox();
    widthEdit->setRange(0, 5000);
    widthEdit->setValue(p.getWidth());
    widthEdit->setEnabled(false);

    //photographLayout->addWidget(new QLabel("PHOTOGRAPH"));
    photographLayout->addWidget(new QLabel("Autore:"));
    photographLayout->addWidget(authorEdit);
    photographLayout->addWidget(new QLabel("Colorata?"));
    photographLayout->addWidget(colourBox);
    photographLayout->addWidget(new QLabel("Lunghezza:"));
    photographLayout->addWidget(lengthEdit);
    photographLayout->addWidget(new QLabel("Larghezza:"));
    photographLayout->addWidget(widthEdit);
    photographLayout->addWidget(new QLabel("Genere:"));

    photographPage->setLayout(photographLayout);
    widget = photographPage;
}

QWidget* InfoVisitor::getWidget() const {
    return widget;
}
