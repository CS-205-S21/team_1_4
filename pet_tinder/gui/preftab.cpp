#include "preftab.h"
#include "ui_preftab.h"

PrefTab::PrefTab(QWidget *parent) : QWidget(parent), ui(new Ui::PrefTab) {
    ui->setupUi(this);
    ui->pushButton_2->setVisible(false);
    ui->ageInput->setValidator( new QIntValidator(1, 1000, this) );
    ui->weightInput->setValidator( new QDoubleValidator(1, 10000, 5, this) );
}

PrefTab::~PrefTab()
{
    delete ui;
}
//not shown because it is useless
void PrefTab::on_pushButton_2_clicked()
{
    this->close();
}
void PrefTab::populateBoxes()
{
}

void PrefTab::userProofing(){

    if(pnter->profileWindow->userInfoAdopter->prefSpecies == "" && pnter->profileWindow->userInfoAdopter->prefSpeciesReq ==1){
        ui->speciesReqInput->setChecked(false);

    }
    if(pnter->profileWindow->userInfoAdopter->prefBreed == "" && pnter->profileWindow->userInfoAdopter->prefBreedReq ==1){
         ui->breedReqInput->setChecked(false);

    }
    if(pnter->profileWindow->userInfoAdopter->prefAge == 0 && pnter->profileWindow->userInfoAdopter->prefAgeReq ==1){
         ui->ageReqInput->setChecked(false);
    }
    if(pnter->profileWindow->userInfoAdopter->prefWeight == 0.0 && pnter->profileWindow->userInfoAdopter->prefWeightReq ==1){
         ui->weightReqInput->setChecked(false);
    }
    if(pnter->profileWindow->userInfoAdopter->prefColor == "" && pnter->profileWindow->userInfoAdopter->prefColorReq ==1){
         ui->colorReqIput->setChecked(false);
    }



}
void PrefTab::on_prefSaveButton_clicked()
{
         userProofing();
        pnter->petList = pnter->matchmaker->DatabaseInterface(pnter->profileWindow->userInfoAdopter);
        pnter->initialize();
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
    if(arg1 == ""){
        pnter->profileWindow->userInfoAdopter->prefAge = 0;

    }
    else{
        pnter->profileWindow->userInfoAdopter->prefAge = arg1.toInt();
    }
}
void PrefTab::on_weightInput_textChanged(const QString &arg1)
{
    if(arg1 == ""){
        pnter->profileWindow->userInfoAdopter->prefWeight = 0.0;
    }
    else{
        pnter->profileWindow->userInfoAdopter->prefWeight = arg1.toDouble();
    }
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
