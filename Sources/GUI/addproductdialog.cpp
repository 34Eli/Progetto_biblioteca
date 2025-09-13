#include "Sources/GUI/addproductdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "Sources/Headers/film.h"
#include "Sources/Headers/book.h"
#include "Sources/Headers/music.h"
#include "Sources/Headers/videogame.h"
#include "Sources/Headers/photograph.h"

AddProductDialog::AddProductDialog(QWidget* parent)
    : QDialog(parent), newProduct(nullptr) {
    setupUI();
}

AddProductDialog::~AddProductDialog() {
}

void AddProductDialog::setupUI() {
    setWindowTitle("Add New Product");
    resize(400, 200);

    //Layout principale
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    //Campo nome
    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Enter product name...");
    mainLayout->addWidget(new QLabel("Name:"));
    mainLayout->addWidget(nameInput);

    //ComboBox per selezionare tipo
    QComboBox* typeComboBox = new QComboBox(this);
    typeComboBox->addItems({"-- Select a product type --","Book", "Film", "Music", "Videogame", "Photograph"});
    mainLayout->addWidget(new QLabel("Type:"));
    mainLayout->addWidget(typeComboBox);

    //Bottone di conferma
    addButton = new QPushButton("Add Product", this);
    mainLayout->addWidget(addButton);

    //Connessioni
    connect(addButton, &QPushButton::clicked, this, &AddProductDialog::on_addProduct_clicked);
    connect(typeComboBox, &QComboBox::currentTextChanged, this, &AddProductDialog::updateUIForProductType);
}

void AddProductDialog::on_addProduct_clicked() {
    QString name = nameInput->text().trimmed();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Error", "Product name cannot be empty!");
        return;
    }

    if (!newProduct) {
        QMessageBox::warning(this, "Error", "Please select a product type!");
        return;
    }

    newProduct->setName(name.toStdString());

    accept();
}

void AddProductDialog::updateUIForProductType(const QString& type) {
    if (type == "-- Select a product type --") {
        if (newProduct) {
            delete newProduct;
            newProduct = nullptr;
        }
        return;
    }

    if (type == "Book") {
        newProduct = new Book("", "", "", "", 0, 0, 0, "", "", 0, "", 0);
    } else if (type == "Film") {
        newProduct = new Film("", "", "", "", 0, 0, 0, "", "", "", "", 0);
    } else if (type == "Music") {
        newProduct = new Music("", "", "", "", 0, 0, 0, "", "", "", "", 0);
    } else if (type == "Videogame") {
        newProduct = new Videogame("", "", "", "", 0, 0, 0, "", "", "", 0);
    } else if (type == "Photograph") {
        newProduct = new Photograph("", "", "", "", 0, 0, 0, "", "", false, 0, 0);
    }
}

Product* AddProductDialog::getNewProduct() const {
    return newProduct;
}
