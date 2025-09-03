#ifndef ADDPRODUCTDIALOG_H
#define ADDPRODUCTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFormLayout>
#include <QSpinBox>
#include "Sources/Headers/product.h"
#include "Sources/Headers/book.h"
#include "Sources/Headers/film.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"
#include "Sources/Headers/photograph.h"

class AddProductDialog : public QDialog {
    Q_OBJECT

private:
    void setupUI();
    QLineEdit* nameInput;
    QPushButton* addButton;
    Product* newProduct = nullptr;

private slots:
    void on_addProduct_clicked();
    void updateUIForProductType(const QString& type);

public:
    explicit AddProductDialog(QWidget* parent = nullptr);
    ~AddProductDialog();
    Product* getNewProduct() const;
};

#endif // ADDPRODUCTDIALOG_H
