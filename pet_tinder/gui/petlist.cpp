#include "petlist.h"
#include "ui_petlist.h"

PetList::PetList(QWidget *parent) : QWidget(parent), ui(new Ui::PetList) {
    ui->setupUi(this);
    pfptr = NULL;
    ppptr = NULL;
    ciptr = new ChatInfo();

    validMessage = false;
    noMessagesDisplay = "This is where your messages will appear!";
    ui->invalidWarning->setVisible(false);

    for(int i = 0; i < textboxes.size(); i++) {
        textboxes.at(i) = noMessagesDisplay;
        ui->chatbox->setText(noMessagesDisplay);
    }
}

PetList::~PetList() {
    delete ui;
}

void PetList::sendMessage() {
    //Doesn't send a message if you have no conversations
    if(textboxes.size() > 0) {
        //Finds current conversation index
        int convoIndex = ui->otherConvos->currentIndex();
        //If this is the first message, clear no messages display
        if(textboxes.at(convoIndex).compare(noMessagesDisplay) == 0) {
            textboxes.at(convoIndex).clear();
        }
        if(validMessage) {
            if(pfptr->isUserAdopter) {
                textboxes.at(convoIndex).append
                    (QString::fromStdString(ppptr->userInfoAdopter->username) + ": " + typedMessage + "\n");
            } else {
                textboxes.at(convoIndex).append
                    (QString::fromStdString(ppptr->userInfoAdoptee->username) + ": " + typedMessage + "\n");
            }
            ui->chatbox->setText(textboxes.at(convoIndex));
            ui->lineEdit->clear();
        }
    }
}

void PetList::newConvo(Pet* pet, Adopter *adopter) {

}

void PetList::newConvo(Pet* pet, Adoptee *adoptee) {
    adopteesChatting.push_back(adoptee);
    petsChatting.push_back(pet);
    textboxes.push_back(noMessagesDisplay);
    //If adoptee doesn't have an associated shelter, display their username instead
    if(adoptee->shelter.compare("") == 0) {
        ui->otherConvos->addItem(QString::fromStdString(pet->name + " from " + adoptee->username));
    } else {
        ui->otherConvos->addItem(QString::fromStdString(pet->name + " from " + adoptee->shelter));
    }
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

void PetList::on_lineEdit_returnPressed() {
    sendMessage();
}

void PetList::on_otherConvos_currentIndexChanged(int index) {
    ui->chatbox->setText(textboxes.at(index));
    if(pfptr->isUserAdopter && adoptersChatting.size() > 0) {
        ui->chatTitle->setText
                (QString::fromStdString("Chatting with " + adoptersChatting.at(index)->username));
    } else if (adopteesChatting.size() > 0) {
        ui->chatTitle->setText
                (QString::fromStdString("Chatting with " + adopteesChatting.at(index)->username +
                                        " from " + adopteesChatting.at(index)->shelter));
    }
}

void PetList::on_petInfoButton_clicked() {
    ciptr->show();
}
