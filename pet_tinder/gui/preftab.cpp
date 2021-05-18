#include "preftab.h"
#include "ui_preftab.h"

PrefTab::PrefTab(QWidget *parent) : QWidget(parent), ui(new Ui::PrefTab) {
    ui->setupUi(this);
    ui->pushButton_2->setVisible(false);
    ui->ageInput->setValidator( new QIntValidator(0, 1000, this) );
     ui->weightInput->setValidator( new QDoubleValidator(0, 10000, 5, this) );
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

}
void PrefTab::on_prefSaveButton_clicked()
{



    this->close();

}
void PrefTab::on_speciesInput_textChanged(const QString &arg1)
{
     pnter->profileWindow->userInfoAdopter->prefSpecies = arg1.toStdString();
}
void PrefTab::on_breedInput_textChanged(const QString &arg1)
{
    pnter->profileWindow->userInfoAdopter->prefBreed = arg1.toStdString();
}
void PrefTab::on_ageInput_textChanged(const QString &arg1)
{
     pnter->profileWindow->userInfoAdopter->prefAge = arg1.toInt();
}
void PrefTab::on_weightInput_textChanged(const QString &arg1)
{
    pnter->profileWindow->userInfoAdopter->prefWeight = arg1.toDouble();
}
void PrefTab::on_colorInput_textChanged(const QString &arg1)
{
    pnter->profileWindow->userInfoAdopter->prefColor = arg1.toStdString();
}
void PrefTab::on_comboBoxSex_currentIndexChanged(const QString &arg1)
{
    pnter->profileWindow->userInfoAdopter->prefSex = arg1.toStdString();
}
void PrefTab::on_comboBoxHypo_currentIndexChanged(int index)
{
    pnter->profileWindow->userInfoAdopter->prefHypoallergenic = index;
}
void PrefTab::on_speciesReqInput_stateChanged(int arg1)
{
       pnter->profileWindow->userInfoAdopter->prefSpeciesReq = arg1;
}
void PrefTab::on_breedReqInput_stateChanged(int arg1)
{
     pnter->profileWindow->userInfoAdopter->prefBreedReq = arg1;
}
void PrefTab::on_ageReqInput_stateChanged(int arg1)
{
     pnter->profileWindow->userInfoAdopter->prefAgeReq = arg1;
}
void PrefTab::on_weightReqInput_stateChanged(int arg1)
{
    pnter->profileWindow->userInfoAdopter->prefWeightReq = arg1;
}
void PrefTab::on_colorReqIput_stateChanged(int arg1)
{
     pnter->profileWindow->userInfoAdopter->prefColorReq = arg1;
}
void PrefTab::on_sexReqInput_stateChanged(int arg1)
{
    pnter->profileWindow->userInfoAdopter->prefSexReq = arg1;
}
void PrefTab::on_hypoReqInput_stateChanged(int arg1)
{
    pnter->profileWindow->userInfoAdopter->prefHypoallergenicReq = arg1;
}
