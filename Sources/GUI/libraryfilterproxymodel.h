#ifndef LIBRARYFILTERPROXYMODEL_H
#define LIBRARYFILTERPROXYMODEL_H
#include <QSortFilterProxyModel>

class LibraryFilterProxyModel : QSortFilterProxyModel {
    Q_OBJECT

private:
    QString filterType = "All";

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

public:
    explicit LibraryFilterProxyModel(QObject* parent = nullptr);
    void setFilter(const QString& type);
};

#endif // LIBRARYFILTERPROXYMODEL_H
