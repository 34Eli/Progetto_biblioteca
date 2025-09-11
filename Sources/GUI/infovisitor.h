#ifndef INFOVISITOR_H
#define INFOVISITOR_H

#include "Sources/Model/visitor.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>

class InfoVisitor : public QObject, public Visitor{
    Q_OBJECT

    private:
        QWidget* widget = nullptr;
        QList<QWidget*> editableFields;
        QPushButton* backButton;
        QPushButton* modifyButton;
        QPushButton* saveButton;
        Product* product = nullptr;
        QString productType;

    signals:
        void backSignal();
        void modifiedSignal();

    public:
        explicit InfoVisitor(QObject* parent = nullptr);
        ~InfoVisitor() override = default;

        void visitFilm(Film& f) override;
        void visitBook(Book& b) override;
        void visitMusic(Music& m) override;
        void visitPhotograph(Photograph& p) override;
        void visitVideogame(Videogame& v) override;

        QFormLayout* commonSetUp(Product& p);

        QWidget* getWidget() const;

        QWidget* createImageWidget(Product& p);
        QWidget* createButtonWidget();
        void enableEdit();
        void setProduct(Product* p);
        void applyEdits();

};

#endif // INFOVISITOR_H
