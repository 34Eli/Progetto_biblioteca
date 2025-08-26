#include "libraryfilterproxymodel.h"
#include "Sources/Headers/product.h"
#include "Sources/GUI/typevisitor.h"

LibraryFilterProxyModel::LibraryFilterProxyModel(QObject* parent) : QSortFilterProxyModel(parent) {}

bool LibraryFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const {
    if (filterType == "All" || filterType.isEmpty()){
        return true;
    }
    QModelIndex idx = sourceModel()->index(sourceRow, 0, sourceParent);
    QVariant var = sourceModel()->data(idx, Qt::UserRole);
    Product* p = reinterpret_cast<Product*>(var.value<void*>());
    if (!p) {
        return false;
    }
    TypeVisitor visitor;
    p->accept(visitor);
    return visitor.getType() == filterType;
}

void LibraryFilterProxyModel::setFilter(const QString& type){
    filterType = type;
    invalidateFilter();
}
