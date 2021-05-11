#include "preftab.h"
#include "ui_preftab.h"

PrefTab::PrefTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrefTab)
{
    ui->setupUi(this);

}

PrefTab::~PrefTab()
{
    delete ui;
}

void PrefTab::on_pushButton_2_clicked()
{
    this->close();
}
