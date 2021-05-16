#include "preftab.h"
#include "ui_preftab.h"

PrefTab::PrefTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrefTab)
{
    ui->setupUi(this);
    populateBoxes();

}

PrefTab::~PrefTab()
{
    delete ui;
}

void PrefTab::on_pushButton_2_clicked()
{
    this->close();
}

void PrefTab::populateBoxes()
{
    ui->comboBoxSpecies->itemText(0) = "hello world";
     ui->comboBoxSpecies->itemText(1) = "hello world2";
     ui->comboBoxSpecies->setItemText(0, "hello world3");
     ui->comboBoxSpecies->insertItem(0,"hello welcome to my hell");
   //  ui->comboBoxSpecies->item
}
