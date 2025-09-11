#include "infovisitor.h"
#include "Sources/Headers/film.h"
#include "Sources/Headers/book.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"
#include "Sources/Headers/photograph.h"
#include "Sources/GUI/typevisitor.h"


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
#include <QPushButton>

//1.Implementare modify fuori dai visit
//2.delete delle cose precedenti
//3.save e salvare nel json
//4.rendere spin, line
//5.creare un nuovo metodo per gli attributi in comune (product)

InfoVisitor::InfoVisitor(QObject* parent) : QObject(parent) {}

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

    editableFields.append(titleEdit);
    editableFields.append(descrEdit);
    editableFields.append(genreEdit);
    editableFields.append(countryEdit);
    editableFields.append(yearEdit);
    editableFields.append(costEdit);
    editableFields.append(starsEdit);

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
    QHBoxLayout* mainLayout = new QHBoxLayout();

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

    editableFields.append(directorEdit);
    editableFields.append(actorEdit);
    editableFields.append(minutesEdit);
    editableFields.append(companyEdit);

    filmLayout->addRow("Regista:", directorEdit);
    filmLayout->addRow("Attore principale:", actorEdit);
    filmLayout->addRow("Durata (minuti):", minutesEdit);
    filmLayout->addRow("Casa di produzione:", companyEdit);

    QWidget* filmWidget = new QWidget();
    filmWidget->setLayout(filmLayout);
    mainLayout->addWidget(filmWidget);

    QVBoxLayout* finalLayout = new QVBoxLayout();
    finalLayout->addLayout(mainLayout);
    finalLayout->addWidget(createButtonWidget());

    filmPage->setLayout(finalLayout);
    widget = filmPage;
}


void InfoVisitor::visitVideogame(Videogame& v) {

    QWidget* videogamePage = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout();

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

    editableFields.append(companyEdit);
    editableFields.append(platformEdit);
    editableFields.append(multiplayerBox);

    videogameLayout->addRow("Casa di produzione:", companyEdit);
    videogameLayout->addRow("Piattaforma:", platformEdit);
    videogameLayout->addRow("Multiplayer", multiplayerBox);

    QWidget* videogameWidget = new QWidget();
    videogameWidget->setLayout(videogameLayout);
    mainLayout->addWidget(videogameWidget);

    QVBoxLayout* finalLayout = new QVBoxLayout();
    finalLayout->addLayout(mainLayout);
    finalLayout->addWidget(createButtonWidget());

    videogamePage->setLayout(finalLayout);
    widget = videogamePage;
}


void InfoVisitor::visitMusic(Music& m) {

    QWidget* musicPage = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout();

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

    editableFields.append(companyEdit);
    editableFields.append(singerEdit);
    editableFields.append(albumEdit);
    editableFields.append(minutesEdit);

    musicLayout->addRow("Casa di produzione:", companyEdit);
    musicLayout->addRow("Cantante:", singerEdit);
    musicLayout->addRow("Album:", albumEdit);
    musicLayout->addRow("Durata (minuti):", minutesEdit);

    QWidget* musicWidget = new QWidget();
    musicWidget->setLayout(musicLayout);
    mainLayout->addWidget(musicWidget);

    QVBoxLayout* finalLayout = new QVBoxLayout();
    finalLayout->addLayout(mainLayout);
    finalLayout->addWidget(createButtonWidget());

    musicPage->setLayout(finalLayout);
    widget = musicPage;
}


void InfoVisitor::visitBook(Book& b) {

    QWidget* bookPage = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout();

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

    editableFields.append(authorEdit);
    editableFields.append(pagesEdit);
    editableFields.append(publisherEdit);
    editableFields.append(isbnEdit);

    bookLayout->addRow("Autore:", authorEdit);
    bookLayout->addRow("Pagine:", pagesEdit);
    bookLayout->addRow("Editore:", publisherEdit);
    bookLayout->addRow("ISBN:", isbnEdit);

    QWidget* bookWidget = new QWidget();
    bookWidget->setLayout(bookLayout);
    mainLayout->addWidget(bookWidget);

    QVBoxLayout* finalLayout = new QVBoxLayout();
    finalLayout->addLayout(mainLayout);
    finalLayout->addWidget(createButtonWidget());

    bookPage->setLayout(finalLayout);
    widget = bookPage;
}


void InfoVisitor::visitPhotograph(Photograph& p) {

    QWidget* photographPage = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout();

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

    editableFields.append(authorEdit);
    editableFields.append(colourBox);
    editableFields.append(lengthEdit);
    editableFields.append(widthEdit);

    photographLayout->addRow("Autore:", authorEdit);
    photographLayout->addRow("Colorata?", colourBox);
    photographLayout->addRow("Lunghezza:", lengthEdit);
    photographLayout->addRow("Larghezza:", widthEdit);

    QWidget* photographWidget = new QWidget();
    photographWidget->setLayout(photographLayout);
    mainLayout->addWidget(photographWidget);

    QVBoxLayout* finalLayout = new QVBoxLayout();
    finalLayout->addLayout(mainLayout);
    finalLayout->addWidget(createButtonWidget());

    photographPage->setLayout(finalLayout);
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

QWidget* InfoVisitor::createButtonWidget(){
    QWidget* buttonWidget = new QWidget();
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);

    backButton = new QPushButton("Back");
    modifyButton = new QPushButton("Modify");
    saveButton = new QPushButton("Save");
    saveButton->setEnabled(false);

    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(modifyButton);
    buttonLayout->addWidget(saveButton);

    connect(backButton, &QPushButton::clicked, this, &InfoVisitor::backSignal);
    connect(modifyButton, &QPushButton::clicked, this, &InfoVisitor::enableEdit);
    connect(saveButton, &QPushButton::clicked, this, [this]() {
        applyEdits();
        emit modifiedSignal();
        saveButton->setEnabled(false);
    });


    return buttonWidget;
}

void InfoVisitor::enableEdit(){

    for (auto e : editableFields){
        if (auto* lineEdit = qobject_cast<QLineEdit*>(e)) {
            lineEdit->setReadOnly(false);
        } else if (auto* textEdit = qobject_cast<QTextEdit*>(e)){
            textEdit->setReadOnly(false);
        } else if (auto* checkBox = qobject_cast<QCheckBox*>(e)){
            checkBox->setEnabled(true);
        } else {
            qDebug() << "Type not valid";
        }
    }
    saveButton->setEnabled(true);
}

void InfoVisitor::setProduct(Product* p){
    product = p;

    if (p) {
        TypeVisitor visitor;
        p->accept(visitor);
        productType = visitor.getType();
    }
}

void InfoVisitor::applyEdits(){
    if (!product){
        return;
    }

    product->setName(qobject_cast<QLineEdit*>(editableFields[0])->text().toStdString());
    QTextEdit* descrEdit = qobject_cast<QTextEdit*>(editableFields[1]);
    if (descrEdit)
        product->setDescription(descrEdit->toPlainText().toStdString());

    product->setGenre(qobject_cast<QLineEdit*>(editableFields[2])->text().toStdString());
    product->setCountry(qobject_cast<QLineEdit*>(editableFields[3])->text().toStdString());
    product->setYear(qobject_cast<QLineEdit*>(editableFields[4])->text().toInt());
    product->setCost(qobject_cast<QLineEdit*>(editableFields[5])->text().toInt());
    product->setStars(qobject_cast<QLineEdit*>(editableFields[6])->text().toInt());

    if (productType == "Film") {
        Film* f = dynamic_cast<Film*>(product);
        if (f) {
            f->setDirector(qobject_cast<QLineEdit*>(editableFields[7])->text().toStdString());
            f->setActor(qobject_cast<QLineEdit*>(editableFields[8])->text().toStdString());
            f->setMinutes(qobject_cast<QLineEdit*>(editableFields[9])->text().toInt());
            f->setCompany(qobject_cast<QLineEdit*>(editableFields[10])->text().toStdString());
        }
    }
    else if (productType == "Music") {
        Music* m = dynamic_cast<Music*>(product);
        if (m) {
            m->setCompany(qobject_cast<QLineEdit*>(editableFields[7])->text().toStdString());
            m->setSinger(qobject_cast<QLineEdit*>(editableFields[8])->text().toStdString());
            m->setAlbum(qobject_cast<QLineEdit*>(editableFields[9])->text().toStdString());
            m->setMinutes(qobject_cast<QLineEdit*>(editableFields[10])->text().toInt());
        }
    }
    else if (productType == "Videogame") {
        Videogame* v = dynamic_cast<Videogame*>(product);
        if (v) {
            v->setCompany(qobject_cast<QLineEdit*>(editableFields[7])->text().toStdString());
            v->setPlatform(qobject_cast<QLineEdit*>(editableFields[8])->text().toStdString());
            v->setIsMultiplayer(qobject_cast<QCheckBox*>(editableFields[9])->isChecked());
        }
    }
    else if (productType == "Book") {
        Book* b = dynamic_cast<Book*>(product);
        if (b) {
            b->setAuthor(qobject_cast<QLineEdit*>(editableFields[7])->text().toStdString());
            b->setPages(qobject_cast<QLineEdit*>(editableFields[8])->text().toInt());
            b->setPublisher(qobject_cast<QLineEdit*>(editableFields[9])->text().toStdString());
            b->setISBN(qobject_cast<QLineEdit*>(editableFields[10])->text().toInt());
        }
    }
    else if (productType == "Photograph") {
        Photograph* p = dynamic_cast<Photograph*>(product);
        if (p) {
            p->setAuthor(qobject_cast<QLineEdit*>(editableFields[7])->text().toStdString());
            p->setIsColourful(qobject_cast<QCheckBox*>(editableFields[8])->isChecked());
            p->setLength(qobject_cast<QLineEdit*>(editableFields[9])->text().toInt());
            p->setWidth(qobject_cast<QLineEdit*>(editableFields[10])->text().toInt());
        }
    }

    for (auto e : editableFields) {
        if (auto* lineEdit = qobject_cast<QLineEdit*>(e)) {
            lineEdit->setReadOnly(true);
        } else if (auto* textEdit = qobject_cast<QTextEdit*>(e)) {
            textEdit->setReadOnly(true);
        } else if (auto* checkBox = qobject_cast<QCheckBox*>(e)) {
            checkBox->setEnabled(false);
        }
    }
}


QWidget* InfoVisitor::getWidget() const {
    return widget;
}
