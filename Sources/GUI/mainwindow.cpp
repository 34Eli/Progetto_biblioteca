#include "Sources/GUI/mainwindow.h"
#include "Sources/Data/JSON/jsonreader.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), model(new LibraryModel(this)), proxymodel(new LibraryFilterProxyModel(this)){
    setupUI();
    loadProducts();
    proxymodel->setSourceModel(model);
    tableView->setModel(proxymodel);
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
    tableView = new QTableView(this);

    btnAll = new QPushButton("Tutti", this);
    btnBook = new QPushButton("Book", this);
    btnFilm = new QPushButton("Film", this);
    btnMusic = new QPushButton("Music", this);
    btnVideogame = new QPushButton("Videogame", this);
    btnPhotograph = new QPushButton("Photograph", this);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(btnAll);
    buttonLayout->addWidget(btnBook);
    buttonLayout->addWidget(btnFilm);
    buttonLayout->addWidget(btnMusic);
    buttonLayout->addWidget(btnVideogame);
    buttonLayout->addWidget(btnPhotograph);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(tableView);

    centralWidget->setLayout(mainLayout);

    connect(btnAll, &QPushButton::clicked, this, &MainWindow::filterAll);    //singolare
    connect(btnBook, &QPushButton::clicked, this, &MainWindow::filterBooks);
    connect(btnFilm, &QPushButton::clicked, this, &MainWindow::filterFilms);
    connect(btnMusic, &QPushButton::clicked, this, &MainWindow::filterMusic);
    connect(btnVideogame, &QPushButton::clicked, this, &MainWindow::filterVideogames);
    connect(btnPhotograph, &QPushButton::clicked, this, &MainWindow::filterPhotograph);
}

void MainWindow::loadProducts(){
    JsonReader reader;
    QList<Product*> productList = reader.readAll("C://Users//39346//OneDrive//Desktop//Progetto_biblioteca//Progetto_biblioteca//Sources//Data//JSON//library.json");
    model->setProducts(productList);
}


