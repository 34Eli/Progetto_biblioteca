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
#include <QFileDialog>
#include <QMessageBox>

//scroll bar (anche per descrizioni lunghe)
//limiti anni
//togliere limite descrizione (renderlo flessibile)
//stile

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

    /*editableFields.append(titleEdit);
    editableFields.append(descrEdit);
    editableFields.append(genreEdit);
    editableFields.append(countryEdit);
    editableFields.append(yearEdit);
    editableFields.append(costEdit);
    editableFields.append(starsEdit);*/

    editableMap["name"] = titleEdit;
    editableMap["description"] = descrEdit;
    editableMap["genre"] = genreEdit;
    editableMap["country"] = countryEdit;
    editableMap["year"] = yearEdit;
    editableMap["cost"] = costEdit;
    editableMap["stars"] = starsEdit;

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

    editableMap["director"] = directorEdit;
    editableMap["actor"] = actorEdit;
    editableMap["minutes"] = minutesEdit;
    editableMap["company"] = companyEdit;

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

    editableMap["company"] = companyEdit;
    editableMap["platform"] = platformEdit;
    editableMap["isMultiplayer"] = multiplayerBox;

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

    editableMap["company"] = companyEdit;
    editableMap["singer"] = singerEdit;
    editableMap["album"] = albumEdit;
    editableMap["minutes"] = minutesEdit;

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

    editableMap["author"] = authorEdit;
    editableMap["pages"] = pagesEdit;
    editableMap["publisher"] = publisherEdit;
    editableMap["ISBN"] = isbnEdit;

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

    editableMap["author"] = authorEdit;
    editableMap["isColourful"] = colourBox;
    editableMap["length"] = lengthEdit;
    editableMap["width"] = widthEdit;

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

    QWidget* container = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(container);

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

    QPushButton* changeImageButton = new QPushButton("Cambia Immagine");

    imageEdit = new QLineEdit(image);
    imageEdit->setReadOnly(true);
    editableMap["image"] = imageEdit;
    connect(changeImageButton, &QPushButton::clicked, this, [this, imageLabel]() {
        QString srcPath = QFileDialog::getOpenFileName(nullptr, "Seleziona Immagine", "", "Immagini (*.png *.jpg *.jpeg)");
        if (!srcPath.isEmpty()) {

            QString extension = QFileInfo(srcPath).suffix();
            QString uniqueName = "img_" + QString::number(QDateTime::currentMSecsSinceEpoch()) + "." + extension;
            QString destDir = QCoreApplication::applicationDirPath() + "/../../../Sources/IMG/";
            QString destPath = QDir(destDir).filePath(uniqueName);

            if (QFile::copy(srcPath, destPath)) {
                QPixmap newPix(destPath);
                imageLabel->setPixmap(newPix.scaled(200, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                imageEdit->setText(uniqueName);
                saveButton->setEnabled(true);
            } else {
                QMessageBox::warning(nullptr, "Errore", "Errore durante la copia dell'immagine.");
            }
        }
    });

    layout->addWidget(imageLabel);
    layout->addWidget(imageEdit);
    layout->addWidget(changeImageButton);

    return container;
}

QWidget* InfoVisitor::createButtonWidget(){
    QWidget* buttonWidget = new QWidget();
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonWidget);

    backButton = new QPushButton("Back");
    modifyButton = new QPushButton("Modify");
    saveButton = new QPushButton("Save");
    saveButton->setEnabled(false);

    deleteButton = new QPushButton("Delete");
    deleteButton->setStyleSheet("background-color: red; color: white; font-weight: bold;");

    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(modifyButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(deleteButton);

    connect(backButton, &QPushButton::clicked, this, &InfoVisitor::backSignal);
    connect(modifyButton, &QPushButton::clicked, this, &InfoVisitor::enableEdit);
    connect(saveButton, &QPushButton::clicked, this, &InfoVisitor::applyEdits);
    connect(deleteButton, &QPushButton::clicked, this, &InfoVisitor::deleteProduct);

    return buttonWidget;
}

void InfoVisitor::enableEdit(){

    for (auto m : editableMap) {
        if (auto* lineEdit = qobject_cast<QLineEdit*>(m)) lineEdit->setReadOnly(false);
        else if (auto* textEdit = qobject_cast<QTextEdit*>(m)) textEdit->setReadOnly(false);
        else if (auto* checkBox = qobject_cast<QCheckBox*>(m)) checkBox->setEnabled(true);
    }
    if (saveButton) saveButton->setEnabled(true);
}

void InfoVisitor::deleteProduct() {
    if (product) {
        emit deleteSignal(product);
    }
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

    if (!product) return;

    if (editableMap.contains("image")) {
        QLineEdit* imgEdit = qobject_cast<QLineEdit*>(editableMap["image"]);
        if (imgEdit) {
            product->setImage(imgEdit->text().toStdString());
        }
    }

    if (auto* title = qobject_cast<QLineEdit*>(editableMap["name"]))
        product->setName(title->text().toStdString());

    if (auto* descr = qobject_cast<QTextEdit*>(editableMap["description"]))
        product->setDescription(descr->toPlainText().toStdString());

    product->setGenre(qobject_cast<QLineEdit*>(editableMap["genre"])->text().toStdString());
    product->setCountry(qobject_cast<QLineEdit*>(editableMap["country"])->text().toStdString());
    product->setYear(qobject_cast<QLineEdit*>(editableMap["year"])->text().toInt());
    product->setCost(qobject_cast<QLineEdit*>(editableMap["cost"])->text().toInt());
    product->setStars(qobject_cast<QLineEdit*>(editableMap["stars"])->text().toInt());

    if (productType == "Film") {
        Film* f = dynamic_cast<Film*>(product);
        if (f) {
            f->setDirector(qobject_cast<QLineEdit*>(editableMap["director"])->text().toStdString());
            f->setActor(qobject_cast<QLineEdit*>(editableMap["actor"])->text().toStdString());
            f->setMinutes(qobject_cast<QLineEdit*>(editableMap["minutes"])->text().toInt());
            f->setCompany(qobject_cast<QLineEdit*>(editableMap["company"])->text().toStdString());
        }
    }

    else if (productType == "Music") {
        Music* m = dynamic_cast<Music*>(product);
        if (m) {
            m->setCompany(qobject_cast<QLineEdit*>(editableMap["company"])->text().toStdString());
            m->setSinger(qobject_cast<QLineEdit*>(editableMap["singer"])->text().toStdString());
            m->setAlbum(qobject_cast<QLineEdit*>(editableMap["album"])->text().toStdString());
            m->setMinutes(qobject_cast<QLineEdit*>(editableMap["minutes"])->text().toInt());
        }
    }
    else if (productType == "Videogame") {
        Videogame* v = dynamic_cast<Videogame*>(product);
        if (v) {
            v->setCompany(qobject_cast<QLineEdit*>(editableMap["company"])->text().toStdString());
            v->setPlatform(qobject_cast<QLineEdit*>(editableMap["platform"])->text().toStdString());
            v->setIsMultiplayer(qobject_cast<QCheckBox*>(editableMap["isMultiplayer"])->isChecked());
        }
    }
    else if (productType == "Book") {
        Book* b = dynamic_cast<Book*>(product);
        if (b) {
            b->setAuthor(qobject_cast<QLineEdit*>(editableMap["author"])->text().toStdString());
            b->setPages(qobject_cast<QLineEdit*>(editableMap["pages"])->text().toInt());
            b->setPublisher(qobject_cast<QLineEdit*>(editableMap["publisher"])->text().toStdString());
            b->setISBN(qobject_cast<QLineEdit*>(editableMap["ISBN"])->text().toInt());
        }
    }
    else if (productType == "Photograph") {
        Photograph* p = dynamic_cast<Photograph*>(product);
        if (p) {
            p->setAuthor(qobject_cast<QLineEdit*>(editableMap["author"])->text().toStdString());
            p->setIsColourful(qobject_cast<QCheckBox*>(editableMap["isColourful"])->isChecked());
            p->setLength(qobject_cast<QLineEdit*>(editableMap["length"])->text().toInt());
            p->setWidth(qobject_cast<QLineEdit*>(editableMap["width"])->text().toInt());
        }
    }

    for (auto w : editableMap) {
        if (auto* lineEdit = qobject_cast<QLineEdit*>(w)) lineEdit->setReadOnly(true);
        else if (auto* textEdit = qobject_cast<QTextEdit*>(w)) textEdit->setReadOnly(true);
        else if (auto* checkBox = qobject_cast<QCheckBox*>(w)) checkBox->setEnabled(false);
    }

    emit modifiedSignal();
    if (saveButton) saveButton->setEnabled(false);
}

QWidget* InfoVisitor::getWidget() const {
    return widget;
}
