#include "petlist.h"
#include "ui_petlist.h"

PetList::PetList(QWidget *parent) : QWidget(parent), ui(new Ui::PetList) {
    ui->setupUi(this);
    pfptr = NULL;
    ppptr = NULL;
    ciptr = new ChatInfo();
    ciptr->petListWindow = this;

    validMessage = false;
    noMessagesDisplay = "This is where your messages will appear!";
    ui->invalidWarning->setVisible(false);
    convoIndex = ui->otherConvos->currentIndex();
}

PetList::~PetList() {
    delete ui;
}

//Initializes conversations, call from login not constructor
void PetList::initialize() {
    //Reads in messages frmo database
    if(pfptr->isUserAdopter) {
        Adopter* user = ppptr->userInfoAdopter;
        for(int i = 0; i < (int)user->likedPetIds.size(); i++) {
            Conversation* convo = pfptr->matchmaker->DM->readInConversation
                                   (user->username, pfptr->matchmaker->DM->findAdopteePet
                                    (user->likedPetIds.at(i))->username);
            adopteesChatting.push_back(pfptr->matchmaker->DM->readInAdopteePublic
                                       (convo->usernameAdoptee));
            petsChatting.push_back(pfptr->matchmaker->DM->findPet
                                   (user->likedPetIds.at(i)));
            textboxes.push_back(convo->messages);
            //If adoptee doesn't have an associated shelter, display their username instead
            if(adopteesChatting.back()->shelter.compare("") == 0) {
                ui->otherConvos->addItem(QString::fromStdString
                                         (petsChatting.back()->name +
                                          " from " + adopteesChatting.back()->username));
            } else {
                ui->otherConvos->addItem(QString::fromStdString
                                         (petsChatting.back()->name +
                                          " from " + adopteesChatting.back()->shelter));
            }
        }
    }
}

void PetList::sendMessage() {
    //Doesn't send a message if you have no conversations
    if(textboxes.size() > 0) {
        //Finds current conversation index
        //If this is the first message, clear no messages display
        if(textboxes.at(convoIndex).size() == 0) {
            textboxes.at(convoIndex).clear();
        }
        if(validMessage) {
            if(pfptr->isUserAdopter) {
                textboxes.at(convoIndex).push_back
                    (QString::fromStdString(ppptr->userInfoAdopter->username) + ": " + typedMessage);
            } else {
                textboxes.at(convoIndex).push_back
                    (QString::fromStdString(ppptr->userInfoAdoptee->username) + ": " + typedMessage);
            }
            QString text;
            for(QString i : textboxes.at(convoIndex)) {
                text.append(i + "\n");
            }
            ui->chatbox->setText(text);
            ui->lineEdit->clear();
        }
    }
}

void PetList::newConvo(Pet* pet, Adopter *adopter) {

}

void PetList::newConvo(Pet* pet, Adoptee *adoptee) {
    adopteesChatting.push_back(adoptee);
    petsChatting.push_back(pet);
    vector<QString> vec;
    vec.push_back(noMessagesDisplay);
    textboxes.push_back(vec);
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
    convoIndex = index;
    QString text;
    for(QString i : textboxes.at(convoIndex)) {
        text.append(i + "\n");
    }
    ui->chatbox->setText(text);
    if(pfptr->isUserAdopter && adoptersChatting.size() > 0) {
        ui->chatTitle->setText
                (QString::fromStdString("Chatting with " + adoptersChatting.at(convoIndex)->username));
    } else if (adopteesChatting.size() > 0) {
        ui->chatTitle->setText
                (QString::fromStdString("Chatting with " + adopteesChatting.at(convoIndex)->username +
                                        " from " + adopteesChatting.at(convoIndex)->shelter));
    }
}

void PetList::on_petInfoButton_clicked() {
    //Button only works if user has liked pets
    if(textboxes.size() > 0) {
        ciptr->display(true);
        ciptr->show();
    }
}

void PetList::on_shelterInfoButton_clicked() {
    //Button only works if user has liked pets
    if(textboxes.size() > 0) {
        ciptr->display(false);
        ciptr->show();
    }
}

