#ifndef MENUBAR_H
#define MENUBAR_H

#include <QObject>
#include <QMenuBar>

class MenuBar : public QMenuBar {
    Q_OBJECT

private:
    void setUpMenu(); //su private perchè la chiamo nel costruttore

signals:
    void loadJsonSignal();
    void loadXmlSignal();

public:
    explicit MenuBar(QWidget* parent = nullptr);
};

#endif // MENUBAR_H
