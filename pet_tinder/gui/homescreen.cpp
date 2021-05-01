#include "homescreen.h"
#include "ui_homescreen.h"

HomeScreen::HomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen)
{
    ui->setupUi(this);

    petWindow = new PetFinder();
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::on_loginButton_clicked()
{
    this->hide();
    petWindow->showMaximized();
}
