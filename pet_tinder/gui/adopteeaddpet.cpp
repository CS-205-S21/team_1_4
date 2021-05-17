#include "adopteeaddpet.h"
#include "ui_adopteeaddpet.h"

AdopteeAddPet::AdopteeAddPet(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdopteeAddPet)
{
    ui->setupUi(this);

}

AdopteeAddPet::~AdopteeAddPet()
{
    delete ui;
}

void AdopteeAddPet::on_btn_image_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg *.jpeg *.gif)"));
    if(QString::compare(filename, QString()) != 0){
        QImage image;
        bool valid = image.load(filename);
        if(valid){
            QPixmap pic;
            image = image.scaled(200, 300, Qt::KeepAspectRatio);
            ui->lbl_image->setPixmap(pic.fromImage(image));
            
            QByteArray byteArray;
            QBuffer buffer(&byteArray);
            buffer.open(QIODevice::WriteOnly);
            pic.save(&buffer, "PNG");
            input->image = byteArray;
            cout << byteArray.toStdString() << endl;
        }
        else{

        }
    }
}

//broken DO NOT DELETE I AM TOO LAZY TO DEAL WITH THE ISSUES THAT WILL OCCUR
//void AdopteeAddPet::on_pushButton_2_clicked()
//{

//}

void AdopteeAddPet::on_discardButton_clicked()
{
    this->close();
}

void AdopteeAddPet::on_saveButton_clicked()
{
    //Add pet to database
    pnter->matchmaker->DM->addPet(input);
    //Add pet to adoptee's owned pet list
    pnter->profileWindow->userInfoAdoptee->ownedPetIds.push_back
            (pnter->matchmaker->DM->getPetIdMax() + 1);
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
    input->age =  arg1.toInt();

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
        input->sex = "male";
    }
    else{
        input->sex = "female";
    }
}

void AdopteeAddPet::on_bioBox_textChanged(const QString &arg1)
{
    input->bio = arg1.toStdString();
}
