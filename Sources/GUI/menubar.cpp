#include "menubar.h"
#include <QMenu>

MenuBar::MenuBar(QWidget* parent) : QMenuBar(parent) {
    setUpMenu();
}

void MenuBar::setUpMenu(){
    QMenu* menu = this->addMenu("File");

    QAction* jsonAction = new QAction("Load from JSON", this);
    QAction* xmlAction = new QAction("Load from XML", this);

    menu->addAction(jsonAction);
    menu->addAction(xmlAction);

    connect(jsonAction, &QAction::triggered, this, &MenuBar::loadJsonSignal);
    connect(xmlAction, &QAction::triggered, this, &MenuBar::loadXmlSignal);
}
