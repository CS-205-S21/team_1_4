#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "petfinder.h"
#include <QWidget>

namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = 0);
    ~HomeScreen();

private slots:
    void on_loginButton_clicked();

private:
    Ui::HomeScreen* ui;
    PetFinder* petWindow;
};

#endif // HOMESCREEN_H
