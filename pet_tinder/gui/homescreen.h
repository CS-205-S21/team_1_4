#ifndef HOMESCREEN_H
#define HOMESCREEN_H
#include "addaccount.h"
#include "petfinder.h"
#include <QWidget>
#include <string>
//#include "../databasemanager/databasemanager.h"

namespace Ui {
class HomeScreen;
}
class AddAccount;
class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    string username;
    string password;
    AddAccount *AApointer;
    PetFinder* petWindow;
    explicit HomeScreen(QWidget *parent = 0);
    ~HomeScreen();
    void login();

    void closeEvent(QCloseEvent* event);

    //DatabaseManager* databaseManager;

private slots:
    void on_loginButton_clicked();

    void on_usernameInput_textEdited(const QString &arg1);

    void on_passwordInput_textEdited(const QString &arg1);

    void on_newAccount_clicked();

    void on_usernameInput_returnPressed();

    void on_passwordInput_returnPressed();

private:
    Ui::HomeScreen* ui;
};

#endif // HOMESCREEN_H
