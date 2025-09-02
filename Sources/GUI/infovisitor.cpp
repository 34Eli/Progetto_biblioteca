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
#include <QApplication>
#include <QDir>

//1.Implementare modify fuori dai visit
//2.delete delle cose precedenti
//3.save e salvare nel json
//4.rendere spin, line
//5.creare un nuovo metodo per gli attributi in comune (product)

QFormLayout* InfoVisitor::commonSetUp(Product& p){

    QFormLayout* commonLayout = new QFormLayout();

    QLineEdit* titleEdit = new QLineEdit(QString::fromStdString(p.getName()));
    titleEdit->setReadOnly(true);

    QTextEdit* descrEdit = new QTextEdit(QString::fromStdString(p.getDescription()));
    descrEdit->setReadOnly(true);
    descrEdit->setFixedHeight(80);

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

    commonLayout->addRow("Titolo:", titleEdit);
    commonLayout->addRow("Descrizione:", descrEdit);
    commonLayout->addRow("Genere:", genreEdit);
    commonLayout->addRow("Paese:", countryEdit);
    commonLayout->addRow("Anno:", yearEdit);
    commonLayout->addRow("Prezzo:", costEdit);
    commonLayout->addRow("Valutazione stelle:", starsEdit);

    return commonLayout;
}


void InfoVisitor::visitFilm(Film& f) {

    QWidget* filmPage = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout(filmPage);

    QWidget* imageWidget = createImageWidget(f);
    mainLayout->addWidget(imageWidget);

    QFormLayout* filmLayout = commonSetUp(f);

    QLineEdit* directorEdit = new QLineEdit(QString::fromStdString(f.getDirector()));
    directorEdit->setReadOnly(true);

    QLineEdit* actorEdit = new QLineEdit(QString::fromStdString(f.getActor()));
    actorEdit->setReadOnly(true);

    QLineEdit* minutesEdit = new QLineEdit(QString::number(f.getMinutes()));
    minutesEdit->setReadOnly(true);

    QLineEdit* companyEdit = new QLineEdit(QString::fromStdString(f.getCompany()));
    companyEdit->setReadOnly(true);

    filmLayout->addRow("Regista:", directorEdit);
    filmLayout->addRow("Attore principale:", actorEdit);
    filmLayout->addRow("Durata (minuti):", minutesEdit);
    filmLayout->addRow("Casa di produzione:", companyEdit);

    QWidget* filmWidget = new QWidget();
    filmWidget->setLayout(filmLayout);
    mainLayout->addWidget(filmWidget);

    filmPage->setLayout(mainLayout);
    widget = filmPage;
}


void InfoVisitor::visitVideogame(Videogame& v) {

    QWidget* videogamePage = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout(videogamePage);

    QWidget* imageWidget = createImageWidget(v);
    mainLayout->addWidget(imageWidget);

    QFormLayout* videogameLayout = commonSetUp(v);

    QLineEdit* companyEdit = new QLineEdit(QString::fromStdString(v.getCompany()));
    companyEdit->setReadOnly(true);

    QLineEdit* platformEdit = new QLineEdit(QString::fromStdString(v.getPlatform()));
    platformEdit->setReadOnly(true);

    QCheckBox* multiplayerBox = new QCheckBox("Multiplayer");
    multiplayerBox->setChecked(v.getIsMultiplayer());
    multiplayerBox->setEnabled(false);

    videogameLayout->addRow("Casa di produzione:", companyEdit);
    videogameLayout->addRow("Piattaforma:", companyEdit);
    videogameLayout->addRow("Multiplayer", multiplayerBox);

    QWidget* videogameWidget = new QWidget();
    videogameWidget->setLayout(videogameLayout);
    mainLayout->addWidget(videogameWidget);

    videogamePage->setLayout(mainLayout);
    widget = videogamePage;
}


void InfoVisitor::visitMusic(Music& m) {

    QWidget* musicPage = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout(musicPage);

    QWidget* imageWidget = createImageWidget(m);
    mainLayout->addWidget(imageWidget);

    QFormLayout* musicLayout = commonSetUp(m);

    QLineEdit* companyEdit = new QLineEdit(QString::fromStdString(m.getCompany()));
    companyEdit->setReadOnly(true);

    QLineEdit* singerEdit = new QLineEdit(QString::fromStdString(m.getSinger()));
    singerEdit->setReadOnly(true);

    QLineEdit* albumEdit = new QLineEdit(QString::fromStdString(m.getAlbum()));
    albumEdit->setReadOnly(true);

    QLineEdit* minutesEdit = new QLineEdit(QString::number(m.getMinutes()));
    minutesEdit->setReadOnly(true);

    musicLayout->addRow("Casa di produzione:", companyEdit);
    musicLayout->addRow("Cantante:", singerEdit);
    musicLayout->addRow("Album:", albumEdit);
    musicLayout->addRow("Durata (minuti):", minutesEdit);

    QWidget* musicWidget = new QWidget();
    musicWidget->setLayout(musicLayout);
    mainLayout->addWidget(musicWidget);

    musicPage->setLayout(mainLayout);
    widget = musicPage;
}


void InfoVisitor::visitBook(Book& b) {

    QWidget* bookPage = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout(bookPage);

    QWidget* imageWidget = createImageWidget(b);
    mainLayout->addWidget(imageWidget);

    QFormLayout* bookLayout = commonSetUp(b);

    QLineEdit* authorEdit = new QLineEdit(QString::fromStdString(b.getAuthor()));
    authorEdit->setReadOnly(true);

    QLineEdit* pagesEdit = new QLineEdit(QString::number(b.getPages()));
    pagesEdit->setReadOnly(true);

    QLineEdit* publisherEdit = new QLineEdit(QString::fromStdString(b.getPublisher()));
    publisherEdit->setReadOnly(true);

    QLineEdit* isbnEdit = new QLineEdit(QString::number(b.getISBN()));
    isbnEdit->setReadOnly(true);

    bookLayout->addRow("Autore:", authorEdit);
    bookLayout->addRow("Pagine:", pagesEdit);
    bookLayout->addRow("Editore:", publisherEdit);
    bookLayout->addRow("ISBN:", isbnEdit);

    QWidget* bookWidget = new QWidget();
    bookWidget->setLayout(bookLayout);
    mainLayout->addWidget(bookWidget);

    bookPage->setLayout(mainLayout);
    widget = bookPage;
}


void InfoVisitor::visitPhotograph(Photograph& p) {

    QWidget* photographPage = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout(photographPage);

    QWidget* imageWidget = createImageWidget(p);
    mainLayout->addWidget(imageWidget);

    QFormLayout* photographLayout = commonSetUp(p);

    QLineEdit* authorEdit = new QLineEdit(QString::fromStdString(p.getAuthor()));
    authorEdit->setReadOnly(true);

    QCheckBox* colourBox = new QCheckBox("Colorata");
    colourBox->setChecked(p.getIsColourful());
    colourBox->setEnabled(false);

    QLineEdit* lengthEdit = new QLineEdit(QString::number(p.getLength()));
    lengthEdit->setReadOnly(true);

    QLineEdit* widthEdit = new QLineEdit(QString::number(p.getWidth()));
    widthEdit->setReadOnly(true);

    photographLayout->addRow("Autore:", authorEdit);
    photographLayout->addRow("Colorata?", colourBox);
    photographLayout->addRow("Lunghezza:", lengthEdit);
    photographLayout->addRow("Larghezza:", widthEdit);

    QWidget* photographWidget = new QWidget();
    photographWidget->setLayout(photographLayout);
    mainLayout->addWidget(photographWidget);

    photographPage->setLayout(mainLayout);
    widget = photographPage;
}

QWidget* InfoVisitor::createImageWidget(Product& p){

    QLabel* imageLabel = new QLabel();
    QString path = QCoreApplication::applicationDirPath() + "/../../../Sources/IMG/";
    QString image = QString::fromStdString(p.getImage());
    QString fullPath = QDir(path).filePath(image);

    QPixmap pix(fullPath);

    if (!pix.isNull()) {
        imageLabel->setPixmap(pix.scaled(200, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        imageLabel->setText("Nessuna immagine");
        imageLabel->setAlignment(Qt::AlignCenter);
    }
    return imageLabel;
}

QWidget* InfoVisitor::getWidget() const {
    return widget;
}
