#include "profilepage.h"
#include "ui_profilepage.h"

profilePage::profilePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::profilePage)
{
    ui->setupUi(this);
}

profilePage::~profilePage()
{
    delete ui;
}
