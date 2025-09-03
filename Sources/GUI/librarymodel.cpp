#include "librarymodel.h"
#include <QString>
#include <QPixmap>
#include <QCoreApplication>
#include <QDir>

LibraryModel::LibraryModel(QObject* parent) : QAbstractTableModel(parent) {}

int LibraryModel::rowCount(const QModelIndex&) const {
    return products.size();
}

int LibraryModel::columnCount(const QModelIndex&) const{
    return 1;
}

QVariant LibraryModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    Product* p = products.at(index.row());

    if (role == Qt::DisplayRole) {
        return QString::fromStdString(p->getName());
    }

    if (role == Qt::DecorationRole) {

        QString path = QCoreApplication::applicationDirPath() + "/../../../Sources/IMG/";
        QString image = QString::fromStdString(p->getImage());
        QString fullPath = QDir(path).filePath(image);

        QPixmap pix(fullPath);

        if (pix.isNull()) {
            qDebug() << "Failed to load image from path:" << QString::fromStdString(p->getImage());
        }
        return pix.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }

    if (role == Qt::UserRole) {
        return QVariant::fromValue(static_cast<void*>(p));
    }
    return QVariant();
}

QVariant LibraryModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole && section == 0)
        return "Name";
    return QVariant();
}

void LibraryModel::setProducts(const QList<Product*>& product){
    beginResetModel();
    products = product;
    endResetModel();
}

void LibraryModel::addProduct(Product* newProduct) {
    if (!newProduct) {
        return;
    }

    int newRow = products.size();
    beginInsertRows(QModelIndex(), newRow, newRow);
    products.append(newProduct);
    endInsertRows();
}

/*Product* LibraryModel::getProducts(int row) const{
    if (row >= 0 && row < products.size()){
        return products[row];
    } else {
        return nullptr;
    }
}*/
