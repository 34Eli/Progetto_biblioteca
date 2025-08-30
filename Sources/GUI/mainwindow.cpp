#include "Sources/GUI/mainwindow.h"
#include "Sources/Data/JSON/jsonreader.h"
#include <QHBoxLayout>
#include <QLineEdit>

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), model(new LibraryModel(this)), proxymodel(new LibraryFilterProxyModel(this)){
    setWindowTitle("Digital Library");
    setupUI();
    loadProducts();
    proxymodel->setSourceModel(model);
    listView->setModel(proxymodel);
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
    listView->setViewMode(QListView::IconMode);  // vista a griglia
    listView->setIconSize(QSize(100, 100));      // dimensione immagine
    listView->setGridSize(QSize(120, 140));      // dimensione cella
    listView->setSpacing(10);                    // spazio tra elementi
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
}

void MainWindow::loadProducts(){
    JsonReader reader;
    QList<Product*> productList = reader.readAll("C://Users//39346//OneDrive//Desktop//Progetto_biblioteca//Progetto_biblioteca//Sources//Data//JSON//library.json");
    model->setProducts(productList);
}



