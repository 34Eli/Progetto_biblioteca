#include "mainwindow.h"
#include "Sources/Data/JSON/jsonreader.h"
#include "Sources/Data/XML/xmlreader.h"
#include "Sources/GUI/infovisitor.h"
#include "Sources/GUI/menubar.h"
#include "Sources/GUI/addproductdialog.h"
#include "Sources/GUI/jsonwritervisitor.h"
#include "Sources/GUI/xmlwritervisitor.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), model(new LibraryModel(this)), proxymodel(new LibraryFilterProxyModel(this)){
    setWindowTitle("Digital Library");
    setupUI();

    proxymodel->setSourceModel(model);
    listView->setModel(proxymodel);

    MenuBar* bar = new MenuBar(this);
    setMenuBar(bar);

    connect(bar, &MenuBar::loadJsonSignal, this, &MainWindow::loadFromJson);
    connect(bar, &MenuBar::loadXmlSignal, this, &MainWindow::loadFromXml);
    connect(bar, &MenuBar::addProductSignal, this, &MainWindow::openAddProductDialog);
}

MainWindow::~MainWindow() {}

void MainWindow::filterAll(){
    proxymodel->setFilter("All");
}

void MainWindow::filterBooks(){
    proxymodel->setFilter("Book");
}

void MainWindow::filterFilms(){
    proxymodel->setFilter("Film");
}

void MainWindow::filterMusic(){
    proxymodel->setFilter("Music");
}

void MainWindow::filterVideogames(){
    proxymodel->setFilter("Videogame");
}

void MainWindow::filterPhotograph(){
    proxymodel->setFilter("Photograph");
}

void MainWindow::setupUI(){
    QWidget* centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    listView = new QListView(this);
    listView->setViewMode(QListView::IconMode);
    listView->setIconSize(QSize(100, 100));
    listView->setGridSize(QSize(120, 140));
    listView->setSpacing(10);
    listView->setResizeMode(QListView::Adjust);
    listView->setMovement(QListView::Static);

    btnAll = new QPushButton("All", this);
    btnBook = new QPushButton("Book", this);
    btnFilm = new QPushButton("Film", this);
    btnMusic = new QPushButton("Music", this);
    btnVideogame = new QPushButton("Videogame", this);
    btnPhotograph = new QPushButton("Photograph", this);

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(btnAll);
    buttonLayout->addWidget(btnBook);
    buttonLayout->addWidget(btnFilm);
    buttonLayout->addWidget(btnMusic);
    buttonLayout->addWidget(btnVideogame);
    buttonLayout->addWidget(btnPhotograph);
    buttonLayout->addStretch();

    QWidget* buttonWidget = new QWidget(this);
    buttonWidget->setLayout(buttonLayout);

    searchBar = new QLineEdit(this);
    searchBar->setPlaceholderText("Search by name...");

    QVBoxLayout* listLayout = new QVBoxLayout;
    listLayout->addWidget(searchBar);
    listLayout->addWidget(listView);
    QWidget* listWidget = new QWidget(this);
    listWidget->setLayout(listLayout);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(buttonWidget);
    mainLayout->addWidget(listWidget);

    mainPage = new QWidget;
    mainPage->setLayout(mainLayout);
    infoPage = new QWidget;
    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(mainPage); //pagina 0
    stackedWidget->addWidget(infoPage); //pagina 1

    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->addWidget(stackedWidget);
    centralWidget->setLayout(centralLayout);

    connect(btnAll, &QPushButton::clicked, this, &MainWindow::filterAll);    //singolare
    connect(btnBook, &QPushButton::clicked, this, &MainWindow::filterBooks);
    connect(btnFilm, &QPushButton::clicked, this, &MainWindow::filterFilms);
    connect(btnMusic, &QPushButton::clicked, this, &MainWindow::filterMusic);
    connect(btnVideogame, &QPushButton::clicked, this, &MainWindow::filterVideogames);
    connect(btnPhotograph, &QPushButton::clicked, this, &MainWindow::filterPhotograph);


    connect(searchBar, &QLineEdit::textChanged, proxymodel, &LibraryFilterProxyModel::setSearchFilter);

    connect(listView, &QListView::clicked, this, &MainWindow::showProductDetails);
}

void MainWindow::loadFromJson(){
    filePath = QCoreApplication::applicationDirPath() + "/../../../Sources/Data/JSON/library.json";
    JsonReader reader;
    productList = reader.readAll(filePath.toStdString());
    model->setProducts(productList);
}

void MainWindow::loadFromXml(){
    filePath = QCoreApplication::applicationDirPath() + "/../../../Sources/Data/XML/library.xml";
    XmlReader reader;
    productList = reader.readAll(filePath);
    model->setProducts(productList);
}

void MainWindow::showProductDetails(const QModelIndex& index) {
    QModelIndex sourceIndex = proxymodel->mapToSource(index);
    QVariant var = model->data(sourceIndex, Qt::UserRole);

    Product* p = reinterpret_cast<Product*>(var.value<void*>());
    if (!p)
        return;

    InfoVisitor* visitor = new InfoVisitor(this);
    visitor->setProduct(p);
    p->accept(*visitor);
    QWidget* productWidget = visitor->getWidget();

    QLayout* layout = infoPage->layout();
    if (!layout) {
        layout = new QVBoxLayout(infoPage);
    } else {
        clearLayout(layout);
    }

    layout->addWidget(productWidget);

    connect(visitor, &InfoVisitor::backSignal, this, [this](){
        stackedWidget->setCurrentWidget(mainPage);
    });

    connect(visitor, &InfoVisitor::modifiedSignal, this, &MainWindow::saveProducts);

    stackedWidget->setCurrentWidget(infoPage);
}

void MainWindow::clearLayout(QLayout* layout) {
    if (!layout) {
        return;
    }
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        } else if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout);
        }
        delete item;
    }
}

void MainWindow::openAddProductDialog() {
    AddProductDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Product* newProduct = dialog.getNewProduct();
        if (newProduct) {
            if (model) {
                model->addProduct(newProduct);
            }
        }
    }
}

void MainWindow::saveProducts(){
    if (model->rowCount() > 0) {
        Product* test = model->getProducts(0);
        if (test) {
            qDebug() << "DEBUG nome prodotto [prima di scrivere]:"
                     << QString::fromStdString(test->getName());
            qDebug() << "DEBUG descrizione:"
                     << QString::fromStdString(test->getDescription());
        }
    }
    if (filePath.endsWith(".json")) {
        saveToJson();
    } else if (filePath.endsWith(".xml")) {
        saveToXml();
    } else {
        QMessageBox::warning(this, "Errore", "Formato di file non supportato.");
    }
    qDebug() << "Salvataggio in corso su:" << filePath;
}

void MainWindow::saveToJson(){

    QJsonArray array;

    for (int row = 0; row < model->rowCount(); ++row) {
        Product* p = model->getProducts(row);
        if (p) {
            JsonWriterVisitor writer;
            p->accept(writer);
            array.append(writer.getJsonObject());
        }
    }

    qDebug() << "Numero prodotti salvati:" << array.size();
    QJsonDocument doc(array);
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Errore", "Impossibile scrivere nel file JSON.");
        return;
    }

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
}

void MainWindow::saveToXml(){

    /*QDomDocument doc("Library");
    QDomElement root = doc.createElement("Products");
    doc.appendChild(root);

    for (int row = 0; row < model->rowCount(); ++row) {
        Product* p = model->getProducts(row);
        if (p) {
            XmlWriterVisitor writer(doc);
            p->accept(writer);
            root.appendChild(writer.getXmlDocument());
        }
    }
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Errore", "Impossibile scrivere nel file XML.");
        return;
    }

    QTextStream stream(&file);
    stream << doc.toString(4);  // 4 = indentazione
    file.close();*/
    filePath = QCoreApplication::applicationDirPath() + "/../../../Sources/Data/XML/library.xml";
    XmlWriterVisitor writer;
    if (!writer.writeAll(filePath, productList)) {
        qWarning() << "Errore nel salvataggio del file XML";
    } else {
        qDebug() << "File XML salvato correttamente in" << filePath;
    }
}



