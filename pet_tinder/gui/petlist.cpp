#include "petlist.h"
#include "ui_petlist.h"

petList::petList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::petList)
{
    ui->setupUi(this);
}

petList::~petList()
{
    delete ui;
}

void petList::on_homeButton_clicked()
{

}

void petList::on_profileButton_clicked()
{

}
