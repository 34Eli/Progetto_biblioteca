#include "Sources/Headers/mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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

