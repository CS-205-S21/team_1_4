#include "petlist.h"
#include "ui_petlist.h"

PetList::PetList(QWidget *parent) : QWidget(parent), ui(new Ui::PetList) {
    ui->setupUi(this);
    pfptr = NULL;
    ppptr = NULL;

    validMessage = false;
    noMessages = false;
    ui->invalidWarning->setVisible(false);

    textbox = "This is where your messages will appear!";
    ui->chatbox->setText(textbox);
}

PetList::~PetList() {
    delete ui;
}

void PetList::sendMessage() {
    if(noMessages == false) {
        textbox.clear();
    }
    if(validMessage) {
        if(pfptr->isUserAdopter) {
            noMessages = true;
            textbox.append(QString::fromStdString(ppptr->userInfoAdopter->username)
                           + ": " + typedMessage + "\n");
        } else {
            textbox.append(QString::fromStdString(ppptr->userInfoAdoptee->username)
                           + ": " + typedMessage + "\n");
        }
        ui->chatbox->setText(textbox);
        ui->lineEdit->clear();
    }
}

void PetList::updateConvos(Pet* pet, Adopter *adopter) {
}

void PetList::updateConvos(Pet* pet, Adoptee *adoptee) {
    adopteesChatting.push_back(adoptee);
    petsChatting.push_back(pet);
    ui->otherConvos->addItem(QString::fromStdString(pet->name + " from " + adoptee->username));


}

void PetList::on_homeButton_clicked() {
    this->hide();
    pfptr->showMaximized();
}

void PetList::on_profileButton_clicked() {
    this->hide();
    ppptr->showMaximized();
}

void PetList::on_lineEdit_textEdited(const QString &arg1) {
    //Checks if typed message is valid
    //Must have at least one character
    if(arg1.length() > 0) {
        //Can't contain the character '|'
        if(!arg1.contains('|')) {
            typedMessage = arg1;
            validMessage = true;
            ui->invalidWarning->setVisible(false);
        } else {
            ui->invalidWarning->setVisible(true);
            validMessage = false;
        }
    } else {
        validMessage = false;
    }
}

void PetList::on_sendButton_clicked() {
    sendMessage();
}

void PetList::on_otherConvos_currentIndexChanged(const QString &arg1) {

}

void PetList::on_lineEdit_returnPressed() {
    sendMessage();
}
