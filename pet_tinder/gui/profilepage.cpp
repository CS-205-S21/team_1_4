#include "profilepage.h"
#include "ui_profilepage.h"

ProfilePage::ProfilePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProfilePage) {
        ui->setupUi(this);
        pfptr = NULL;
        plptr = NULL;
    }

ProfilePage::~ProfilePage()
{
    delete ui;
}

void ProfilePage::on_homeButton_clicked()
{
    this->hide();
    pfptr->showMaximized();
}

void ProfilePage::on_petListButton_clicked()
{
    this->hide();
    plptr->showMaximized();
}
