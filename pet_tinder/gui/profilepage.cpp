#include "profilepage.h"
#include "ui_profilepage.h"

ProfilePage::ProfilePage(QWidget *parent) : QWidget(parent), ui(new Ui::ProfilePage) {
    ui->setupUi(this);
    pfptr = NULL;
    plptr = NULL;
    aap = new AdopteeAddPet();
    aap->pnter = this;
    ptpnter = new PrefTab();

    ui->pushButton->setEnabled(false);
    ui->bioEdit->setVisible(false);
    editingBio = false;
    bioText = "";
}

ProfilePage::~ProfilePage()
{
    delete ui;
}

void ProfilePage::displayUserInfo(bool adopter) {
    if(adopter) {
        ui->userName->setText(QString::fromStdString(userInfoAdopter->username));
        ui->userBio->setText(QString::fromStdString(userInfoAdopter->bio));
        ui->PrefsButton->setVisible(true);
        ui->addPetButton->setVisible(false);
    } else {
        ui->userName->setText(QString::fromStdString(userInfoAdoptee->username));
        ui->userBio->setText(QString::fromStdString(userInfoAdoptee->bio));
        ui->PrefsButton->setVisible(false);
        ui->addPetButton->setVisible(true);
    }
}

void ProfilePage::closeEvent(QCloseEvent *event) {
    pfptr->closeEvent(event);
}

void ProfilePage::on_homeButton_clicked()
{
    this->hide();
    pfptr->showMaximized();
}

void ProfilePage::on_petListButton_clicked()
{
    this->hide();
    plptr->showMaximized();
}

void ProfilePage::on_pushButton_2_clicked()
{
}

void ProfilePage::on_PrefsButton_clicked()
{
    ptpnter->pnter = pfptr;
    ptpnter->show();
}

void ProfilePage::on_addPetButton_clicked()
{
    aap->setupPet(nullptr);
    aap->isNewPet = true;
    aap->show();
}

void ProfilePage::on_editBioButton_clicked()
{
    if(!editingBio) {
        ui->bioEdit->setVisible(true);
        ui->editBioButton->setText("Save");
        editingBio = true;
    } else {
        ui->userBio->setText(bioText);
        if(pfptr->isUserAdopter) {
            userInfoAdopter->bio = bioText.toStdString();
        } else {
            userInfoAdoptee->bio = bioText.toStdString();
        }
        ui->bioEdit->setVisible(false);
        ui->editBioButton->setText("Edit bio");
        editingBio = false;
    }
}

void ProfilePage::on_bioEdit_textEdited(const QString &arg1)
{
    bioText = arg1;
}
