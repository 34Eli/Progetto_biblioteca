#include "addproductdialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

AddProductDialog::AddProductDialog(QWidget* parent)
    : QDialog(parent), newProduct(nullptr) {
    setupUI();
}

AddProductDialog::~AddProductDialog() {
    // Non distruggiamo newProduct qui: sarà gestito dal chiamante
}

void AddProductDialog::setupUI() {
    setWindowTitle("Add New Product");
    resize(400, 200);

    // Layout principale
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Campo nome
    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Enter product name...");
    mainLayout->addWidget(new QLabel("Name:"));
    mainLayout->addWidget(nameInput);

    // ComboBox per selezionare tipo
    QComboBox* typeComboBox = new QComboBox(this);
    typeComboBox->addItems({"Book", "Film", "Music", "Videogame", "Photograph"});
    mainLayout->addWidget(new QLabel("Type:"));
    mainLayout->addWidget(typeComboBox);

    // Bottone di conferma
    addButton = new QPushButton("Add Product", this);
    mainLayout->addWidget(addButton);

    // Connessioni
    connect(addButton, &QPushButton::clicked, this, &AddProductDialog::on_addProduct_clicked);
    connect(typeComboBox, &QComboBox::currentTextChanged, this, &AddProductDialog::on_typeComboBox_currentIndexChanged);
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

    // Imposta il nome scelto dall'utente nell'oggetto
    newProduct->setName(name.toStdString());

    accept(); // chiude la finestra con QDialog::Accepted
}

void AddProductDialog::on_typeComboBox_currentIndexChanged(const QString& type) {
    if (newProduct) {
        delete newProduct;
        newProduct = nullptr;
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
        // CORREZIONE QUI:
        // Passa valori interi (ad esempio 0) per length e width
        newProduct = new Photograph("", "", "", "", 0, 0, 0, "", "", false, 0, 0);
    }
}

Product* AddProductDialog::getNewProduct() const {
    return newProduct;
}
