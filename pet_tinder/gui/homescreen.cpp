#include "homescreen.h"
#include "ui_homescreen.h"

HomeScreen::HomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen)
{
    ui->setupUi(this);

    petWindow = new Screen();
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::on_pushButton_clicked()
{
    this->hide();
    petWindow->showMaximized();
}
