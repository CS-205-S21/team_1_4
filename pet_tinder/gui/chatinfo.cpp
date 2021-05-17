#include "chatinfo.h"
#include "ui_chatinfo.h"

ChatInfo::ChatInfo(QWidget *parent) : QWidget(parent), ui(new Ui::ChatInfo) {
    ui->setupUi(this);

    petListWindow = NULL;
}

ChatInfo::~ChatInfo() {
    delete ui;
}

void ChatInfo::display(bool isPet) {
    //If pet is being displayed...
    if(isPet) {
        Pet* pet = petListWindow->petsChatting.at(petListWindow->convoIndex);

        ui->speciesBreed->setVisible(true);
        ui->hypoallergenic->setVisible(true);
        ui->pic->setVisible(true);
        //Displays image
        /*QImage img(":/Duck_gui.jfif");
        QPixmap pic;
        pic.convertFromImage(img.scaled(200, 300, Qt::KeepAspectRatio), 0);
        ui->pic->setPixmap(pic);*/
        //Displays name, sex, and age
        ui->nameSexAgeShelter->setText(QString::fromStdString(pet->name + ", " + pet->sex + ", " + to_string(pet->age)));
        //Displays species and breed
        ui->speciesBreed->setText(QString::fromStdString(pet->species + " - " + pet->breed));
        //Checks if pet is hypoallergenic, then displays that
        if(pet->hypoallergenic == true) {
            ui->hypoallergenic->setText("Hypoallergenic");
        } else {
            ui->hypoallergenic->setText("Not hypoallergenic");
        }
        //Displays bio
        ui->bio->setText(QString::fromStdString(pet->bio));
        //Displays image
        QPixmap pic;
        pic.loadFromData(pet->image);
        pic.scaled(200, 300, Qt::KeepAspectRatio);
        ui->pic->setPixmap(pic);
    //If not pet is being displayed...
    } else {
        ui->speciesBreed->setVisible(false);
        ui->hypoallergenic->setVisible(false);
        ui->pic->setVisible(false);
        //If adoptee is being displayed...
        if(petListWindow->pfptr->isUserAdopter == true) {
            Adoptee* adoptee = petListWindow->adopteesChatting.at(petListWindow->convoIndex);
            ui->nameSexAgeShelter->setText(QString::fromStdString(adoptee->username + " from " + adoptee->shelter));
                    ui->bio->setText(QString::fromStdString(adoptee->bio));
        //If adopter is being displayed...
        } else {
            Adopter* adopter = petListWindow->adoptersChatting.at(petListWindow->convoIndex);
            ui->nameSexAgeShelter->setText(QString::fromStdString(adopter->username));
            ui->bio->setText(QString::fromStdString(adopter->bio));
        }
    }
}

void ChatInfo::on_backButton_clicked() {
    this->close();
}
