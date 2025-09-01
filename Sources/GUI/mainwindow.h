#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListView>
#include <QPushButton>
#include "Sources/GUI/librarymodel.h"
#include "Sources/GUI/libraryfilterproxymodel.h"
#include <QStackedWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    LibraryModel* model;
    LibraryFilterProxyModel* proxymodel;
    QListView* listView;
    QStackedWidget* stackedWidget;
    QWidget* mainPage;
    QWidget* infoPage;
    QLineEdit* searchBar;

    QPushButton* btnAll;
    QPushButton* btnBook;
    QPushButton* btnFilm;
    QPushButton* btnMusic;
    QPushButton* btnVideogame;
    QPushButton* btnPhotograph;

private slots:
    void filterAll();
    void filterBooks();
    void filterFilms();
    void filterMusic();
    void filterVideogames();
    void filterPhotograph();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupUI();
    void loadProducts();
    void showProductDetails(const QModelIndex& index);
    void clearLayout(QLayout* layout);
};
#endif // MAINWINDOW_H
