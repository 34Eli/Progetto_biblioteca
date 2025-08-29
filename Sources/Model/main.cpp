#include "Sources/GUI/mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    //Creo una palette di colori per l'applicazione
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53,53,53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25,25,25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53,53,53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Highlight, QColor(42,130,218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    a.setPalette(darkPalette);

    MainWindow w;
    w.show();
    return a.exec();
}



/*#include <QCoreApplication>
#include <QDebug>
#include "json\jsonreader.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    JsonReader reader;

    // Percorso del file JSON (assicurati che il file esista)
    std::string filename = "C:\\Users\\39346\\OneDrive\\Desktop\\Progetto_biblioteca\\Progetto_biblioteca\\library.json";

    // Legge tutti i prodotti
    QList<Product*> library = reader.readAll(filename);

    // Stampa base per vedere se funziona
    qDebug() << "Numero prodotti caricati:" << library.size();

    for (Product* p : library) {
        qDebug() << "Nome prodotto:" << QString::fromStdString(p->getName());
    }

    return 0;
}*/

