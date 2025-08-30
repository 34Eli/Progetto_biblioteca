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

//
QWidget* InfoVisitor::visit(Film& f) {
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);

    // --- Campi inizialmente bloccati ---
    QLineEdit* titleEdit = new QLineEdit(QString::fromStdString(f.getName()));
    titleEdit->setReadOnly(true);

    QLineEdit* directorEdit = new QLineEdit(QString::fromStdString(f.getDirector()));
    directorEdit->setReadOnly(true);

    QLineEdit* actorEdit = new QLineEdit(QString::fromStdString(f.getActor()));
    actorEdit->setReadOnly(true);

    QSpinBox* minutesEdit = new QSpinBox();
    minutesEdit->setRange(1, 500);
    minutesEdit->setValue(f.getMinutes());
    minutesEdit->setEnabled(false);

    QLineEdit* genreEdit = new QLineEdit(QString::fromStdString(f.getGenre()));
    genreEdit->setReadOnly(true);

    QLineEdit* countryEdit = new QLineEdit(QString::fromStdString(f.getCountry()));
    countryEdit->setReadOnly(true);

    QSpinBox* yearEdit = new QSpinBox();
    yearEdit->setRange(1800, 2100);
    yearEdit->setValue(f.getYear());
    yearEdit->setEnabled(false);

    QSpinBox* costEdit = new QSpinBox();
    costEdit->setRange(0, 10000);
    costEdit->setValue(f.getCost());
    costEdit->setEnabled(false);

    QSpinBox* starsEdit = new QSpinBox();
    starsEdit->setRange(0, 5);
    starsEdit->setValue(f.getStars());
    starsEdit->setEnabled(false);

    QLineEdit* companyEdit = new QLineEdit(QString::fromStdString(f.getCompany()));
    companyEdit->setReadOnly(true);

    QTextEdit* descrEdit = new QTextEdit(QString::fromStdString(f.getDescription()));
    descrEdit->setReadOnly(true);

    // --- Layout ---
    layout->addWidget(new QLabel("🎬 Film"));
    layout->addWidget(new QLabel("Titolo:"));
    layout->addWidget(titleEdit);
    layout->addWidget(new QLabel("Regista:"));
    layout->addWidget(directorEdit);
    layout->addWidget(new QLabel("Attore principale:"));
    layout->addWidget(actorEdit);
    layout->addWidget(new QLabel("Durata (minuti):"));
    layout->addWidget(minutesEdit);
    layout->addWidget(new QLabel("Genere:"));
    layout->addWidget(genreEdit);
    layout->addWidget(new QLabel("Paese:"));
    layout->addWidget(countryEdit);
    layout->addWidget(new QLabel("Anno:"));
    layout->addWidget(yearEdit);
    layout->addWidget(new QLabel("Prezzo:"));
    layout->addWidget(costEdit);
    layout->addWidget(new QLabel("Valutazione stelle:"));
    layout->addWidget(starsEdit);
    layout->addWidget(new QLabel("Casa di produzione:"));
    layout->addWidget(companyEdit);
    layout->addWidget(new QLabel("Descrizione:"));
    layout->addWidget(descrEdit);

    // --- Pulsante Modify/Save ---
    QPushButton* modifyButton = new QPushButton("Modify");
    layout->addWidget(modifyButton);

    // Puntatore a Film invece della capture mista
    Film* filmPtr = &f;
    bool* clicked = new bool(false); // variabile persistente nella lambda

    QObject::connect(modifyButton, &QPushButton::clicked, page, [=]() mutable {
        if (!*clicked) {
            // Abilita tutti i campi
            titleEdit->setReadOnly(false);
            directorEdit->setReadOnly(false);
            actorEdit->setReadOnly(false);
            minutesEdit->setEnabled(true);
            genreEdit->setReadOnly(false);
            countryEdit->setReadOnly(false);
            yearEdit->setEnabled(true);
            costEdit->setEnabled(true);
            starsEdit->setEnabled(true);
            companyEdit->setReadOnly(false);
            descrEdit->setReadOnly(false);

            modifyButton->setText("Save");
            *clicked = true;
        } else {
            // Salva valori nell'oggetto Film
            filmPtr->setName(titleEdit->text().toStdString());
            filmPtr->setDirector(directorEdit->text().toStdString());
            filmPtr->setActor(actorEdit->text().toStdString());
            filmPtr->setMinutes(minutesEdit->value());
            filmPtr->setGenre(genreEdit->text().toStdString());
            filmPtr->setCountry(countryEdit->text().toStdString());
            filmPtr->setYear(yearEdit->value());
            filmPtr->setCost(costEdit->value());
            filmPtr->setStars(starsEdit->value());
            filmPtr->setCompany(companyEdit->text().toStdString());
            filmPtr->setDescription(descrEdit->toPlainText().toStdString());

            // Blocca di nuovo i campi
            titleEdit->setReadOnly(true);
            directorEdit->setReadOnly(true);
            actorEdit->setReadOnly(true);
            minutesEdit->setEnabled(false);
            genreEdit->setReadOnly(true);
            countryEdit->setReadOnly(true);
            yearEdit->setEnabled(false);
            costEdit->setEnabled(false);
            starsEdit->setEnabled(false);
            companyEdit->setReadOnly(true);
            descrEdit->setReadOnly(true);

            modifyButton->setText("Modify");
            *clicked = false;
        }
    });

    page->setLayout(layout);
    return page;
}

//
QWidget* InfoVisitor::visit(Videogame& v) {
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);

    // --- Campi inizialmente bloccati ---
    QLineEdit* titleEdit = new QLineEdit(QString::fromStdString(v.getName()));
    titleEdit->setReadOnly(true);

    QLineEdit* companyEdit = new QLineEdit(QString::fromStdString(v.getCompany()));
    companyEdit->setReadOnly(true);

    QLineEdit* platformEdit = new QLineEdit(QString::fromStdString(v.getPlatform()));
    platformEdit->setReadOnly(true);

    QCheckBox* multiplayerBox = new QCheckBox("Multiplayer");
    multiplayerBox->setChecked(v.getIsMultiplayer());
    multiplayerBox->setEnabled(false);

    QLineEdit* genreEdit = new QLineEdit(QString::fromStdString(v.getGenre()));
    genreEdit->setReadOnly(true);

    QLineEdit* countryEdit = new QLineEdit(QString::fromStdString(v.getCountry()));
    countryEdit->setReadOnly(true);

    QSpinBox* yearEdit = new QSpinBox();
    yearEdit->setRange(1980, 2100);
    yearEdit->setValue(v.getYear());
    yearEdit->setEnabled(false);

    QSpinBox* costEdit = new QSpinBox();
    costEdit->setRange(0, 10000);
    costEdit->setValue(v.getCost());
    costEdit->setEnabled(false);

    QSpinBox* starsEdit = new QSpinBox();
    starsEdit->setRange(0, 5);
    starsEdit->setValue(v.getStars());
    starsEdit->setEnabled(false);

    QTextEdit* descrEdit = new QTextEdit(QString::fromStdString(v.getDescription()));
    descrEdit->setReadOnly(true);

    // --- Layout ---
    layout->addWidget(new QLabel("🎮 Videogame"));
    layout->addWidget(new QLabel("Titolo:"));
    layout->addWidget(titleEdit);
    layout->addWidget(new QLabel("Casa di produzione:"));
    layout->addWidget(companyEdit);
    layout->addWidget(new QLabel("Piattaforma:"));
    layout->addWidget(platformEdit);
    layout->addWidget(multiplayerBox);
    layout->addWidget(new QLabel("Genere:"));
    layout->addWidget(genreEdit);
    layout->addWidget(new QLabel("Paese:"));
    layout->addWidget(countryEdit);
    layout->addWidget(new QLabel("Anno:"));
    layout->addWidget(yearEdit);
    layout->addWidget(new QLabel("Prezzo:"));
    layout->addWidget(costEdit);
    layout->addWidget(new QLabel("Valutazione stelle:"));
    layout->addWidget(starsEdit);
    layout->addWidget(new QLabel("Descrizione:"));
    layout->addWidget(descrEdit);

    // --- Pulsante Modify/Save ---
    QPushButton* modifyButton = new QPushButton("Modify");
    layout->addWidget(modifyButton);

    // --- Stato cliccato su heap per sicurezza ---
    Videogame* gamePtr = &v;
    bool* clicked = new bool(false);  // allocato sul heap

    QObject::connect(modifyButton, &QPushButton::clicked, page, [=]() mutable {

        if (!*clicked) {
            // Abilita campi
            titleEdit->setReadOnly(false);
            companyEdit->setReadOnly(false);
            platformEdit->setReadOnly(false);
            multiplayerBox->setEnabled(true);
            genreEdit->setReadOnly(false);
            countryEdit->setReadOnly(false);
            yearEdit->setEnabled(true);
            costEdit->setEnabled(true);
            starsEdit->setEnabled(true);
            descrEdit->setReadOnly(false);

            *clicked = true;
        } else {
            // Salva dati nell'oggetto Videogame
            gamePtr->setName(titleEdit->text().toStdString());
            gamePtr->setCompany(companyEdit->text().toStdString());
            gamePtr->setPlatform(platformEdit->text().toStdString());
            gamePtr->setIsMultiplayer(multiplayerBox->isChecked());
            gamePtr->setGenre(genreEdit->text().toStdString());
            gamePtr->setCountry(countryEdit->text().toStdString());
            gamePtr->setYear(yearEdit->value());
            gamePtr->setCost(costEdit->value());
            gamePtr->setStars(starsEdit->value());
            gamePtr->setDescription(descrEdit->toPlainText().toStdString());

            // Blocca campi
            titleEdit->setReadOnly(true);
            companyEdit->setReadOnly(true);
            platformEdit->setReadOnly(true);
            multiplayerBox->setEnabled(false);
            genreEdit->setReadOnly(true);
            countryEdit->setReadOnly(true);
            yearEdit->setEnabled(false);
            costEdit->setEnabled(false);
            starsEdit->setEnabled(false);
            descrEdit->setReadOnly(true);

            *clicked = false;
        }

    });

    page->setLayout(layout);
    return page;
}

//
QWidget* InfoVisitor::visit(Music& m) {
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);

    // --- Campi inizialmente bloccati ---
    QLineEdit* titleEdit = new QLineEdit(QString::fromStdString(m.getName()));
    titleEdit->setReadOnly(true);

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

    QLineEdit* genreEdit = new QLineEdit(QString::fromStdString(m.getGenre()));
    genreEdit->setReadOnly(true);

    QLineEdit* countryEdit = new QLineEdit(QString::fromStdString(m.getCountry()));
    countryEdit->setReadOnly(true);

    QSpinBox* yearEdit = new QSpinBox();
    yearEdit->setRange(1900, 2100);
    yearEdit->setValue(m.getYear());
    yearEdit->setEnabled(false);

    QSpinBox* costEdit = new QSpinBox();
    costEdit->setRange(0, 10000);
    costEdit->setValue(m.getCost());
    costEdit->setEnabled(false);

    QSpinBox* starsEdit = new QSpinBox();
    starsEdit->setRange(0, 5);
    starsEdit->setValue(m.getStars());
    starsEdit->setEnabled(false);

    QTextEdit* descrEdit = new QTextEdit(QString::fromStdString(m.getDescription()));
    descrEdit->setReadOnly(true);

    // --- Layout ---
    layout->addWidget(new QLabel("🎵 Music"));
    layout->addWidget(new QLabel("Titolo:"));
    layout->addWidget(titleEdit);
    layout->addWidget(new QLabel("Casa di produzione:"));
    layout->addWidget(companyEdit);
    layout->addWidget(new QLabel("Cantante:"));
    layout->addWidget(singerEdit);
    layout->addWidget(new QLabel("Album:"));
    layout->addWidget(albumEdit);
    layout->addWidget(new QLabel("Durata minuti:"));
    layout->addWidget(minutesEdit);
    layout->addWidget(new QLabel("Genere:"));
    layout->addWidget(genreEdit);
    layout->addWidget(new QLabel("Paese:"));
    layout->addWidget(countryEdit);
    layout->addWidget(new QLabel("Anno:"));
    layout->addWidget(yearEdit);
    layout->addWidget(new QLabel("Prezzo:"));
    layout->addWidget(costEdit);
    layout->addWidget(new QLabel("Valutazione stelle:"));
    layout->addWidget(starsEdit);
    layout->addWidget(new QLabel("Descrizione:"));
    layout->addWidget(descrEdit);

    // --- Pulsante Modify/Save ---
    QPushButton* modifyButton = new QPushButton("Modify");
    layout->addWidget(modifyButton);

    // --- Stato cliccato su heap per sicurezza ---
    Music* musicPtr = &m;
    bool* clicked = new bool(false);  // allocato sul heap

    QObject::connect(modifyButton, &QPushButton::clicked, page, [=]() mutable {

        if (!*clicked) {
            // Abilita campi
            titleEdit->setReadOnly(false);
            companyEdit->setReadOnly(false);
            singerEdit->setReadOnly(false);
            albumEdit->setReadOnly(false);
            minutesEdit->setEnabled(true);
            genreEdit->setReadOnly(false);
            countryEdit->setReadOnly(false);
            yearEdit->setEnabled(true);
            costEdit->setEnabled(true);
            starsEdit->setEnabled(true);
            descrEdit->setReadOnly(false);

            *clicked = true;
        } else {
            // Salva dati nell'oggetto Music
            musicPtr->setName(titleEdit->text().toStdString());
            musicPtr->setCompany(companyEdit->text().toStdString());
            musicPtr->setSinger(singerEdit->text().toStdString());
            musicPtr->setAlbum(albumEdit->text().toStdString());
            musicPtr->setMinutes(minutesEdit->value());
            musicPtr->setGenre(genreEdit->text().toStdString());
            musicPtr->setCountry(countryEdit->text().toStdString());
            musicPtr->setYear(yearEdit->value());
            musicPtr->setCost(costEdit->value());
            musicPtr->setStars(starsEdit->value());
            musicPtr->setDescription(descrEdit->toPlainText().toStdString());

            // Blocca campi
            titleEdit->setReadOnly(true);
            companyEdit->setReadOnly(true);
            singerEdit->setReadOnly(true);
            albumEdit->setReadOnly(true);
            minutesEdit->setEnabled(false);
            genreEdit->setReadOnly(true);
            countryEdit->setReadOnly(true);
            yearEdit->setEnabled(false);
            costEdit->setEnabled(false);
            starsEdit->setEnabled(false);
            descrEdit->setReadOnly(true);

            *clicked = false;
        }

    });

    page->setLayout(layout);
    return page;
}

//
QWidget* InfoVisitor::visit(Book& b) {
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);

    // --- Campi inizialmente bloccati ---
    QLineEdit* titleEdit = new QLineEdit(QString::fromStdString(b.getName()));
    titleEdit->setReadOnly(true);

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

    QLineEdit* genreEdit = new QLineEdit(QString::fromStdString(b.getGenre()));
    genreEdit->setReadOnly(true);

    QLineEdit* countryEdit = new QLineEdit(QString::fromStdString(b.getCountry()));
    countryEdit->setReadOnly(true);

    QSpinBox* yearEdit = new QSpinBox();
    yearEdit->setRange(1800, 2100);
    yearEdit->setValue(b.getYear());
    yearEdit->setEnabled(false);

    QSpinBox* costEdit = new QSpinBox();
    costEdit->setRange(0, 10000);
    costEdit->setValue(b.getCost());
    costEdit->setEnabled(false);

    QSpinBox* starsEdit = new QSpinBox();
    starsEdit->setRange(0, 5);
    starsEdit->setValue(b.getStars());
    starsEdit->setEnabled(false);

    QTextEdit* descrEdit = new QTextEdit(QString::fromStdString(b.getDescription()));
    descrEdit->setReadOnly(true);

    // --- Layout ---
    layout->addWidget(new QLabel("📚 Book"));
    layout->addWidget(new QLabel("Titolo:"));
    layout->addWidget(titleEdit);
    layout->addWidget(new QLabel("Autore:"));
    layout->addWidget(authorEdit);
    layout->addWidget(new QLabel("Pagine:"));
    layout->addWidget(pagesEdit);
    layout->addWidget(new QLabel("Editore:"));
    layout->addWidget(publisherEdit);
    layout->addWidget(new QLabel("ISBN:"));
    layout->addWidget(isbnEdit);
    layout->addWidget(new QLabel("Genere:"));
    layout->addWidget(genreEdit);
    layout->addWidget(new QLabel("Paese:"));
    layout->addWidget(countryEdit);
    layout->addWidget(new QLabel("Anno:"));
    layout->addWidget(yearEdit);
    layout->addWidget(new QLabel("Prezzo:"));
    layout->addWidget(costEdit);
    layout->addWidget(new QLabel("Valutazione stelle:"));
    layout->addWidget(starsEdit);
    layout->addWidget(new QLabel("Descrizione:"));
    layout->addWidget(descrEdit);

    // --- Pulsante Modify/Save ---
    QPushButton* modifyButton = new QPushButton("Modify");
    layout->addWidget(modifyButton);

    // --- Stato cliccato su heap per sicurezza ---
    Book* bookPtr = &b;
    bool* clicked = new bool(false);  // allocato sul heap

    QObject::connect(modifyButton, &QPushButton::clicked, page, [bookPtr, titleEdit, authorEdit, pagesEdit,
                                                                 publisherEdit, isbnEdit, genreEdit, countryEdit, yearEdit, costEdit, starsEdit, descrEdit, clicked]() mutable {

        if (!*clicked) {
            // Abilita campi
            titleEdit->setReadOnly(false);
            authorEdit->setReadOnly(false);
            pagesEdit->setEnabled(true);
            publisherEdit->setReadOnly(false);
            isbnEdit->setEnabled(true);
            genreEdit->setReadOnly(false);
            countryEdit->setReadOnly(false);
            yearEdit->setEnabled(true);
            costEdit->setEnabled(true);
            starsEdit->setEnabled(true);
            descrEdit->setReadOnly(false);

            *clicked = true;
        } else {
            // Salva dati nell'oggetto Book
            bookPtr->setName(titleEdit->text().toStdString());
            bookPtr->setAuthor(authorEdit->text().toStdString());
            bookPtr->setPages(pagesEdit->value());
            bookPtr->setPublisher(publisherEdit->text().toStdString());
            bookPtr->setISBN(isbnEdit->value());
            bookPtr->setGenre(genreEdit->text().toStdString());
            bookPtr->setCountry(countryEdit->text().toStdString());
            bookPtr->setYear(yearEdit->value());
            bookPtr->setCost(costEdit->value());
            bookPtr->setStars(starsEdit->value());
            bookPtr->setDescription(descrEdit->toPlainText().toStdString());

            // Blocca campi
            titleEdit->setReadOnly(true);
            authorEdit->setReadOnly(true);
            pagesEdit->setEnabled(false);
            publisherEdit->setReadOnly(true);
            isbnEdit->setEnabled(false);
            genreEdit->setReadOnly(true);
            countryEdit->setReadOnly(true);
            yearEdit->setEnabled(false);
            costEdit->setEnabled(false);
            starsEdit->setEnabled(false);
            descrEdit->setReadOnly(true);

            *clicked = false;
        }

    });

    page->setLayout(layout);
    return page;
}

//
QWidget* InfoVisitor::visit(Photograph& p) {
    QWidget* page = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(page);

    // --- Campi inizialmente bloccati ---
    QLineEdit* titleEdit = new QLineEdit(QString::fromStdString(p.getName()));
    titleEdit->setReadOnly(true);

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

    QLineEdit* genreEdit = new QLineEdit(QString::fromStdString(p.getGenre()));
    genreEdit->setReadOnly(true);

    QLineEdit* countryEdit = new QLineEdit(QString::fromStdString(p.getCountry()));
    countryEdit->setReadOnly(true);

    QSpinBox* yearEdit = new QSpinBox();
    yearEdit->setRange(1900, 2100);
    yearEdit->setValue(p.getYear());
    yearEdit->setEnabled(false);

    QSpinBox* costEdit = new QSpinBox();
    costEdit->setRange(0, 10000);
    costEdit->setValue(p.getCost());
    costEdit->setEnabled(false);

    QSpinBox* starsEdit = new QSpinBox();
    starsEdit->setRange(0, 5);
    starsEdit->setValue(p.getStars());
    starsEdit->setEnabled(false);

    QTextEdit* descrEdit = new QTextEdit(QString::fromStdString(p.getDescription()));
    descrEdit->setReadOnly(true);

    // --- Layout ---
    layout->addWidget(new QLabel("📸 Photograph"));
    layout->addWidget(new QLabel("Titolo:"));
    layout->addWidget(titleEdit);
    layout->addWidget(new QLabel("Autore:"));
    layout->addWidget(authorEdit);
    layout->addWidget(colourBox);
    layout->addWidget(new QLabel("Lunghezza:"));
    layout->addWidget(lengthEdit);
    layout->addWidget(new QLabel("Larghezza:"));
    layout->addWidget(widthEdit);
    layout->addWidget(new QLabel("Genere:"));
    layout->addWidget(genreEdit);
    layout->addWidget(new QLabel("Paese:"));
    layout->addWidget(countryEdit);
    layout->addWidget(new QLabel("Anno:"));
    layout->addWidget(yearEdit);
    layout->addWidget(new QLabel("Prezzo:"));
    layout->addWidget(costEdit);
    layout->addWidget(new QLabel("Valutazione stelle:"));
    layout->addWidget(starsEdit);
    layout->addWidget(new QLabel("Descrizione:"));
    layout->addWidget(descrEdit);

    // --- Pulsante Modify/Save ---
    QPushButton* modifyButton = new QPushButton("Modify");
    layout->addWidget(modifyButton);

    // --- Stato cliccato su heap ---
    Photograph* photoPtr = &p;
    bool* clicked = new bool(false);

    QObject::connect(modifyButton, &QPushButton::clicked, page, [=]() mutable {
        if (!*clicked) {
            // Abilita campi
            titleEdit->setReadOnly(false);
            authorEdit->setReadOnly(false);
            colourBox->setEnabled(true);
            lengthEdit->setEnabled(true);
            widthEdit->setEnabled(true);
            genreEdit->setReadOnly(false);
            countryEdit->setReadOnly(false);
            yearEdit->setEnabled(true);
            costEdit->setEnabled(true);
            starsEdit->setEnabled(true);
            descrEdit->setReadOnly(false);
            *clicked = true;
        } else {
            // Salva dati nell'oggetto Photograph
            photoPtr->setName(titleEdit->text().toStdString());
            photoPtr->setAuthor(authorEdit->text().toStdString());
            photoPtr->setIsColourful(colourBox->isChecked());
            photoPtr->setLength(lengthEdit->value());
            photoPtr->setWidth(widthEdit->value());
            photoPtr->setGenre(genreEdit->text().toStdString());
            photoPtr->setCountry(countryEdit->text().toStdString());
            photoPtr->setYear(yearEdit->value());
            photoPtr->setCost(costEdit->value());
            photoPtr->setStars(starsEdit->value());
            photoPtr->setDescription(descrEdit->toPlainText().toStdString());

            // Blocca campi
            titleEdit->setReadOnly(true);
            authorEdit->setReadOnly(true);
            colourBox->setEnabled(false);
            lengthEdit->setEnabled(false);
            widthEdit->setEnabled(false);
            genreEdit->setReadOnly(true);
            countryEdit->setReadOnly(true);
            yearEdit->setEnabled(false);
            costEdit->setEnabled(false);
            starsEdit->setEnabled(false);
            descrEdit->setReadOnly(true);
            *clicked = false;
        }
    });

    page->setLayout(layout);
    return page;
}
