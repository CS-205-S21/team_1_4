#include "adopteeaddpet.h"
#include "ui_adopteeaddpet.h"

AdopteeAddPet::AdopteeAddPet(QWidget *parent) : QWidget(parent), ui(new Ui::AdopteeAddPet) {
    ui->setupUi(this);

    ui->invalidImageLabel->setVisible(false);

    isNewPet = true;
    input = new Pet;
    pnter = NULL;
}

AdopteeAddPet::~AdopteeAddPet() {
    delete ui;
}

//Sets up pet's information ahead of time
void AdopteeAddPet::setupPet(Pet* pet) {
    //If a nullptr is passed, assume no prepared pet is available
    // and fill input with base pet info.
    input = new Pet;
    if(pet == nullptr) {
        input->name = "";
        input->species = "";
        input->breed = "";
        input->age = 0;
        input->weight = 0;
        input->color = "";
        input->hypoallergenic = false;
        input->sex = "Male";
        input->bio = "";
        QImage img(":/claws.png");
        QPixmap pic;
        pic.convertFromImage(img.scaled(829, 786, Qt::KeepAspectRatio), 0);
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        pic.save(&buffer, "png");
        input->image = byteArray;
    } else {
        input = pet;
        ui->nameInput->setText(QString::fromStdString(input->name));
        ui->speciesInput->setText(QString::fromStdString(input->species));
        ui->breedInput->setText(QString::fromStdString(input->breed));
        ui->ageInput->setText(QString::number(input->age));
        ui->weightInput->setText(QString::number(input->weight));
        ui->colorInput->setText(QString::fromStdString(input->color));
        ui->bioBox->setText(QString::fromStdString(input->bio));

        if(input->hypoallergenic == true) {
            ui->comboBox->setCurrentIndex(0);
        } else {
            ui->comboBox->setCurrentIndex(1);

        }
        if(input->sex.compare("Male") == 0) {
            ui->comboBox->setCurrentIndex(0);
        } else {
            ui->comboBox->setCurrentIndex(1);
        }

        QPixmap pic;
        pic.loadFromData(pet->image);
        ui->lbl_image->setPixmap(pic);
    }
}

void AdopteeAddPet::on_btn_image_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.gif)"));
    if(QString::compare(filename, QString()) != 0) {
        QImage image;
        bool valid = image.load(filename);
        if(valid){
            ui->invalidImageLabel->setVisible(false);
            QPixmap pic;
            image = image.scaled(200, 300, Qt::KeepAspectRatio);
            pic.convertFromImage(image);
            ui->lbl_image->setPixmap(pic);
            
            QByteArray byteArray;
            QBuffer buffer(&byteArray);
            buffer.open(QIODevice::WriteOnly);
            pic.save(&buffer, "png");
            input->image = byteArray;
            cout << byteArray.toStdString() << endl;
        }
        else {
            ui->invalidImageLabel->setVisible(true);
        }
    }
}

//broken DO NOT DELETE I AM TOO LAZY TO DEAL WITH THE ISSUES THAT WILL OCCUR
void AdopteeAddPet::on_pushButton_2_clicked()
{

}

void AdopteeAddPet::on_discardButton_clicked()
{
    ui->ageInput->setText("");
    ui->speciesInput->setText("");
    ui->breedInput->setText("");
    ui->colorInput->setText("");
    ui->weightInput->setText("");
    ui->bioBox->setText("");
    this->close();
}

void AdopteeAddPet::on_saveButton_clicked()
{
    input->bio = ui->bioBox->toPlainText().toStdString();
    ui->invalidImageLabel->setVisible(false);
    //If user is creating a new pet...
    if(isNewPet) {
        //Add pet to database
        pnter->pfptr->matchmaker->DM->addPet(input);
        //Add pet to adoptee's owned pet list
        pnter->userInfoAdoptee->ownedPetIds.push_back
                (pnter->pfptr->matchmaker->DM->getPetIdMax() + 1);
        pnter->pfptr->petList.push_back(input);
        if(pnter->pfptr->petList.size() <= 0) {
            pnter->pfptr->setup();
        }
    } else { //If user is editing an old pet...
        pnter->pfptr->editPet(input);
    }

    this->close();
}

void AdopteeAddPet::on_nameInput_textChanged(const QString &arg1)
{
    input->name = arg1.toStdString();
}

void AdopteeAddPet::on_speciesInput_textChanged(const QString &arg1)
{
    input->species = arg1.toStdString();
}

void AdopteeAddPet::on_breedInput_textChanged(const QString &arg1)
{
    input->breed = arg1.toStdString();
}

void AdopteeAddPet::on_ageInput_textChanged(const QString &arg1)
{
    input->age = arg1.toInt();

}

void AdopteeAddPet::on_weightInput_textChanged(const QString &arg1)
{
    input->weight = arg1.toDouble();
}

void AdopteeAddPet::on_colorInput_textChanged(const QString &arg1)
{
    input->color = arg1.toStdString();
}


void AdopteeAddPet::on_comboBox_currentIndexChanged(int index)
{
    if(index == 0){
        input->hypoallergenic = true;
    }
    else{
        input->hypoallergenic = false;
    }
}

void AdopteeAddPet::on_comboBox_2_currentIndexChanged(int index)
{
    if(index == 0){
        input->sex = "Male";
    }
    else{
        input->sex = "Female";
    }
}
