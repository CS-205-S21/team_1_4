#include "petlist.h"
#include "ui_petlist.h"

petList::petList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::petList)
{
    ui->setupUi(this);
    scrptr = NULL;
    ppptr = NULL;
}

petList::~petList()
{
    delete ui;
}

void petList::on_homeButton_clicked()
{
    this->hide();
    scrptr->showMaximized();
}

void petList::on_profileButton_clicked()
{
    this->hide();
    ppptr->showMaximized();
}
