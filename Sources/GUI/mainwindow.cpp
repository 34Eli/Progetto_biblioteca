#include "mainwindow.h"
#include "Sources/Data/JSON/jsonreader.h"
#include "Sources/Data/XML/xmlreader.h"
#include "Sources/GUI/infovisitor.h"
#include "Sources/GUI/menubar.h"
#include "Sources/GUI/addproductdialog.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QLineEdit>

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
    JsonReader reader;
    QList<Product*> productList = reader.readAll((QCoreApplication::applicationDirPath() + "/../../../Sources/Data/JSON/library.json").toStdString());
    model->setProducts(productList);
}

void MainWindow::loadFromXml(){
    XmlReader reader;
    QList<Product*> productList = reader.readAll(QCoreApplication::applicationDirPath() + "/../../../Sources/Data/XML/library.xml");
    model->setProducts(productList);
}

void MainWindow::showProductDetails(const QModelIndex& index) {
    QModelIndex sourceIndex = proxymodel->mapToSource(index);
    QVariant var = model->data(sourceIndex, Qt::UserRole);

    Product* p = reinterpret_cast<Product*>(var.value<void*>());
    if (!p)
        return;

    InfoVisitor* visitor = new InfoVisitor(this);
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

    //connect(visitor, &InfoVisitor::modifiedSignal, this, &MainWindow::saveProducts);

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

