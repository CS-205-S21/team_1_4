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
    string username;
    string password;

    explicit HomeScreen(QWidget *parent = 0);
    ~HomeScreen();

private slots:
    void on_loginButton_clicked();

    void on_usernameInput_textEdited(const QString &arg1);

    void on_passwordInput_textEdited(const QString &arg1);

private:
    Ui::HomeScreen* ui;
    PetFinder* petWindow;
};

#endif // HOMESCREEN_H
