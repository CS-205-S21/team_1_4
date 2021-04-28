#include "profilepage.h"
#include "ui_profilepage.h"

profilePage::profilePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profilePage)
{
    ui->setupUi(this);
    scrptr = NULL;
    plptr = NULL;
}

profilePage::~profilePage()
{
    delete ui;
}

void profilePage::on_homeButton_clicked()
{
    this->hide();
    scrptr->showMaximized();
}

void profilePage::on_petListButton_clicked()
{
    this->hide();
    plptr->showMaximized();
}
