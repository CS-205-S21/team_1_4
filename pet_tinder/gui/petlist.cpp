#include "petlist.h"
#include "ui_petlist.h"

PetList::PetList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PetList)
{
    ui->setupUi(this);
    messageWindow = new MessageScreen();
    messageWindow->plptr = this;
    pfptr = NULL;
    ppptr = NULL;
    msptr = NULL;
}

PetList::~PetList()
{
    delete ui;
}

void PetList::on_homeButton_clicked()
{
    this->hide();
    pfptr->showMaximized();
}

void PetList::on_profileButton_clicked()
{
    this->hide();
    ppptr->showMaximized();
}

void PetList::on_chatButton1_clicked()
{
    this->hide();
    msptr->showMaximized();
}
