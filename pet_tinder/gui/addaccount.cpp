#include "addaccount.h"
#include "ui_addaccount.h"

AddAccount::AddAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddAccount)
{
    ui->setupUi(this);
}

AddAccount::~AddAccount()
{
    delete ui;
}

void AddAccount::on_cancelbutton_clicked()
{
    this->close();

}

void AddAccount::on_saveNewAccount_clicked()
{
    if(validate()){
        //adopter
        if(ui->roleChooser->currentIndex() == 1){
            Adopter *temp = new Adopter;
            temp->username = username.toStdString();
            temp->prefAgeReq = false;
            temp->prefBreedReq = false;
            temp->prefSexReq = false;
            temp->prefHypoallergenicReq = false;
            temp->prefSpeciesReq = false;
            temp->prefColorReq = false;
            temp->prefWeightReq = false;






            PfPnter->matchmaker->DM->addAdopter(temp,password.toStdString());

        }
        //adoptee
        if(ui->roleChooser->currentIndex() == 2){
            Adoptee *temp = new Adoptee;
            temp->username = username.toStdString();
            PfPnter->matchmaker->DM->addAdoptee(temp,password.toStdString());

        }

    }

}

bool AddAccount::validate(){
    if(PfPnter->matchmaker->DM->isUsernameTaken(username.toStdString())){

        ui->errorBox->setText("Sorry Username is already taken");
        return false;
    }
    if(password != confirmPassword){
        ui->errorBox->setText("Passwords do not match");
        return false;
    }
    if(ui->roleChooser->currentIndex() == 0){
        ui->errorBox->setText("Please select a role");
        return false;
    }
    else{
        ui->errorBox->setText("");
        return true;
    }




}

void AddAccount::on_newUsernameInput_textChanged(const QString &arg1)
{
        username = arg1;
}

void AddAccount::on_newPasswordInput_textChanged(const QString &arg1)
{
     password = arg1;
}

void AddAccount::on_newConfirmPasswordInput_textChanged(const QString &arg1)
{
    confirmPassword = arg1;
}

void AddAccount::on_roleChooser_currentIndexChanged(int index)
{
    role = index;
}
