#include "petlist.h"
#include "ui_petlist.h"

PetList::PetList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PetList)
{
    ui->setupUi(this);
    scrptr = NULL;
    ppptr = NULL;
}

PetList::~PetList()
{
    delete ui;
}

void PetList::on_homeButton_clicked()
{
    this->hide();
    scrptr->showMaximized();
}

void PetList::on_profileButton_clicked()
{
    this->hide();
    ppptr->showMaximized();
}
