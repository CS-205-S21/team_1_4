#include "homescreen.h"
#include "ui_homescreen.h"

HomeScreen::HomeScreen(QWidget *parent):QWidget(parent), ui(new Ui::HomeScreen) {
    ui->setupUi(this);

    petWindow = new PetFinder();

    username = "";
    password = "";
}

HomeScreen::~HomeScreen() {
    delete ui;
}

void HomeScreen::on_loginButton_clicked() {
    //if(petWindow->matchmaker.DM->readInAdoptee(username, password));
    this->hide();
    petWindow->showMaximized();
}

void HomeScreen::on_usernameInput_textEdited(const QString &arg1) {
    username = arg1.toStdString();
}
void HomeScreen::on_passwordInput_textEdited(const QString &arg1) {
    password = arg1.toStdString();
}
