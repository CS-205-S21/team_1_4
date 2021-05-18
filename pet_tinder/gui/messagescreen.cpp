#include "messagescreen.h"
#include "ui_messagescreen.h"

MessageScreen::MessageScreen(QWidget *parent): QWidget(parent), ui(new Ui::MessageScreen) {
    ui->setupUi(this);
    plptr = NULL;
}

MessageScreen::~MessageScreen()
{
    delete ui;
}

void MessageScreen::on_backButton_clicked()
{
    this->hide();
    plptr->showMaximized();
}

