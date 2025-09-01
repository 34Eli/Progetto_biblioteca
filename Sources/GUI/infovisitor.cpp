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
#include <QFormLayout>

//1.Implementare modify fuori dai visit
//2.delete delle cose precedenti
//3.save e salvare nel json
//4.rendere spin, line
//5.creare un nuovo metodo per gli attributi in comune (product)

QWidget* InfoVisitor::commonSetUp(Product& p){

    QWidget* common = new QWidget;
    //QVBoxLayout* commonLayout = new QVBoxLayout(common);
    QFormLayout* commonLayout = new QFormLayout(common);

    QLineEdit* titleEdit = new QLineEdit(QString::fromStdString(p.getName()));
    titleEdit->setReadOnly(true);

    QTextEdit* descrEdit = new QTextEdit(QString::fromStdString(p.getDescription()));
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

    /*commonLayout->addWidget(new QLabel("Titolo:"));
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
    commonLayout->addWidget(starsEdit);*/

    commonLayout->addRow("Titolo:", titleEdit);
    commonLayout->addRow("Descrizione:", descrEdit);
    commonLayout->addRow("Genere:", genreEdit);
    commonLayout->addRow("Paese:", countryEdit);
    commonLayout->addRow("Anno:", yearEdit);
    commonLayout->addRow("Prezzo:", costEdit);
    commonLayout->addRow("Valutazione stelle:", starsEdit);

    return common;
}


void InfoVisitor::visitFilm(Film& f) {

    QWidget* filmPage = new QWidget;
    QWidget* commonWidget = commonSetUp(f);
    QVBoxLayout* filmLayout = new QVBoxLayout;
    filmLayout->addWidget(commonWidget);

    QLineEdit* directorEdit = new QLineEdit(QString::fromStdString(f.getDirector()));
    directorEdit->setReadOnly(true);

    QLineEdit* actorEdit = new QLineEdit(QString::fromStdString(f.getActor()));
    actorEdit->setReadOnly(true);

    QLineEdit* minutesEdit = new QLineEdit(QString::number(f.getMinutes()));
    minutesEdit->setReadOnly(true);

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

    QWidget* videogamePage = new QWidget;
    QWidget* commonWidget = commonSetUp(v);
    QVBoxLayout* videogameLayout = new QVBoxLayout;
    videogameLayout->addWidget(commonWidget);

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

    QWidget* musicPage = new QWidget;
    QWidget* commonWidget = commonSetUp(m);
    QVBoxLayout* musicLayout = new QVBoxLayout;
    musicLayout->addWidget(commonWidget);

    QLineEdit* companyEdit = new QLineEdit(QString::fromStdString(m.getCompany()));
    companyEdit->setReadOnly(true);

    QLineEdit* singerEdit = new QLineEdit(QString::fromStdString(m.getSinger()));
    singerEdit->setReadOnly(true);

    QLineEdit* albumEdit = new QLineEdit(QString::fromStdString(m.getAlbum()));
    albumEdit->setReadOnly(true);

    QLineEdit* minutesEdit = new QLineEdit(QString::number(m.getMinutes()));
    minutesEdit->setReadOnly(true);

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

    QWidget* bookPage = new QWidget;
    QWidget* commonWidget = commonSetUp(b);
    QVBoxLayout* bookLayout = new QVBoxLayout;
    bookLayout->addWidget(commonWidget);

    QLineEdit* authorEdit = new QLineEdit(QString::fromStdString(b.getAuthor()));
    authorEdit->setReadOnly(true);

    QLineEdit* pagesEdit = new QLineEdit(QString::number(b.getPages()));
    pagesEdit->setReadOnly(true);

    QLineEdit* publisherEdit = new QLineEdit(QString::fromStdString(b.getPublisher()));
    publisherEdit->setReadOnly(true);

    QLineEdit* isbnEdit = new QLineEdit(QString::number(b.getISBN()));
    isbnEdit->setReadOnly(true);

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

    qDebug() << "Author:" << QString::fromStdString(b.getAuthor());
    qDebug() << "Pages:" << b.getPages();
    qDebug() << "Publisher:" << QString::fromStdString(b.getPublisher());
    qDebug() << "ISBN:" << b.getISBN();
}


void InfoVisitor::visitPhotograph(Photograph& p) {

    QWidget* photographPage = new QWidget;
    QWidget* commonWidget = commonSetUp(p);
    QVBoxLayout* photographLayout = new QVBoxLayout;
    photographLayout->addWidget(commonWidget);

    QLineEdit* authorEdit = new QLineEdit(QString::fromStdString(p.getAuthor()));
    authorEdit->setReadOnly(true);

    QCheckBox* colourBox = new QCheckBox("Colorata");
    colourBox->setChecked(p.getIsColourful());
    colourBox->setEnabled(false);

    QLineEdit* lengthEdit = new QLineEdit(QString::number(p.getLength()));
    lengthEdit->setReadOnly(true);

    QLineEdit* widthEdit = new QLineEdit(QString::number(p.getWidth()));
    widthEdit->setReadOnly(true);

    //photographLayout->addWidget(new QLabel("PHOTOGRAPH"));
    photographLayout->addWidget(new QLabel("Autore:"));
    photographLayout->addWidget(authorEdit);
    photographLayout->addWidget(colourBox);
    photographLayout->addWidget(new QLabel("Lunghezza:"));
    photographLayout->addWidget(lengthEdit);
    photographLayout->addWidget(new QLabel("Larghezza:"));
    photographLayout->addWidget(widthEdit);

    photographPage->setLayout(photographLayout);
    widget = photographPage;
}

QWidget* InfoVisitor::getWidget() const {
    return widget;
}
