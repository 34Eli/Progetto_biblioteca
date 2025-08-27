#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include "Sources/GUI/librarymodel.h"
#include "Sources/GUI/libraryfilterproxymodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    LibraryModel* model;
    LibraryFilterProxyModel* proxymodel;
    QTableView* tableView;

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
};
#endif // MAINWINDOW_H
