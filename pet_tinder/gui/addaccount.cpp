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


    }

}

bool AddAccount::validate(){
    if(PfPnter->matchmaker->DM->isUsernameTaken("kate")){

        ui->errorBox->setText("Sorry Username is already taken");
        return false;
    }
    if(password != confirmPassword){
        ui->errorBox->setText("Passwords do not match");
        return false;
    }
    else{
        ui->errorBox->setText("");

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

}
