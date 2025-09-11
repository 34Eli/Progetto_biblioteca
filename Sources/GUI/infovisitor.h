#ifndef INFOVISITOR_H
#define INFOVISITOR_H

#include <QObject>
#include <QList>
#include <QPushButton>
#include <QFormLayout>

#include "Sources/Headers/product.h"
#include "Sources/Headers/film.h"
#include "Sources/Headers/book.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"
#include "Sources/Headers/photograph.h"
#include "Sources/GUI/typevisitor.h"
#include "Sources/Model/visitor.h"

class InfoVisitor : public QObject, public Visitor
{
    Q_OBJECT

private:
    QWidget* widget = nullptr;
    Product* product = nullptr;
    QString productType;

    QPushButton* backButton;
    QPushButton* modifyButton;
    QPushButton* saveButton;
    QPushButton* deleteButton;

    QList<QWidget*> editableFields;

private slots:
    void enableEdit();
    void deleteProduct();

signals:
    void modifiedSignal();
    void backSignal();
    void deleteSignal(Product* p);

public:
    explicit InfoVisitor(QObject* parent = nullptr);
    QFormLayout* commonSetUp(Product& p);

    void visitFilm(Film& f) override;
    void visitVideogame(Videogame& v) override;
    void visitMusic(Music& m) override;
    void visitBook(Book& b) override;
    void visitPhotograph(Photograph& p) override;

    void setProduct(Product* p);
    void applyEdits();
    QWidget* getWidget() const;

private:
    QWidget* createImageWidget(Product& p);
    QWidget* createButtonWidget();
};

#endif // INFOVISITOR_H
