#include "productmodel.h"

ProductModel::ProductModel(QObject* parent) : QAbstractTableModel(parent) {}

int ProductModel::rowCount(const QModelIndex& parent = QModelIndex()) const {

}

int ProductModel::columnCount(const QModelIndex& parent = QModelIndex()) const{

}

QVariant ProductModel::data(const QModelIndex& index, int role = Qt::DisplayRole) const {

}

QVariant ProductModel::headerData(int section, Qt::Orientation orientation, int role) const {

}

void ProductModel::setProducts(const QList<Product*>& products){

}

Product* ProductModel::getProducts(int row) const{

}
