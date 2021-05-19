#include "petlist.h"
#include "ui_petlist.h"

PetList::PetList(QWidget *parent) : QWidget(parent), ui(new Ui::PetList) {
    ui->setupUi(this);
    pfptr = NULL;
    ppptr = NULL;
    ciptr = new ChatInfo();
    ciptr->petListWindow = this;
    comboNum = 0;

    validMessage = false;
    noMessagesDisplay = "This is where your messages will appear!";
    ui->pushButton->setEnabled(false);
    ui->invalidWarning->setVisible(false);
    convoIndex = ui->otherConvos->currentIndex();
}

PetList::~PetList() {
    delete ui;
}

//Initializes conversations, call from login not constructor
void PetList::initialize() {
    adoptersChatting.clear();
    adopteesChatting.clear();
    petsChatting.clear();
    textboxes.clear();
    //ui->otherConvos->clear();
    //Reads in messages from database
    //If user is adopter...
    if(pfptr->isUserAdopter) {
        ui->chatTitle->setText("You haven't liked any pets yet!");
        ui->chatbox->setText("This is where you will be able to chat "
                             "with the shelters whose pets you've liked.");

        Adopter* user = ppptr->userInfoAdopter;
        for(int i : user->likedPetIds) {
            Conversation* convo = pfptr->matchmaker->DM->readInConversation
                    (user->username, i);
            adopteesChatting.push_back(pfptr->matchmaker->DM->readInAdopteePublic
                                       (convo->usernameAdoptee));
            petsChatting.push_back(pfptr->matchmaker->DM->findPet(i));
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
            comboNum++;
        }
    } else { //If user is adoptee
        ui->chatTitle->setText("None of your pets have been liked yet!");
        ui->chatbox->setText("This is where you will be able to chat "
                             "with the users who have liked your pets.");

        Adoptee* user = ppptr->userInfoAdoptee;
        for(int i : user->ownedPetIds) {
            vector<Adopter*> adopters = pfptr->matchmaker->DM->findAdopterPet(i);
            for(Adopter* adopter : adopters) {
                Conversation* convo = pfptr->matchmaker->DM->readInConversation
                        (adopter->username, i);
                if(convo != nullptr) {
                    adoptersChatting.push_back(adopter);
                    petsChatting.push_back(pfptr->matchmaker->DM->findPet(i));
                    textboxes.push_back(convo->messages);
                    if(adoptersChatting.back() != nullptr && petsChatting.back() != nullptr) {
                        ui->otherConvos->addItem(QString::fromStdString
                                                 (adoptersChatting.back()->username + " who is interested in "
                                                  + petsChatting.back()->name));
                    }
                }
                comboNum++;
            }
        }
    }
}

void PetList::reset() {
    ui->otherConvos->clear();
    for(int i = 0; i < textboxes.size(); i++) {
        ui->otherConvos->addItem(QString::fromStdString
                                 (adoptersChatting.at(i)->username +
                                  " who is interested in " +
                                  petsChatting.at(i)->name));
    }
}

void PetList::sendMessage() {
    //Doesn't send a message if you have no conversations
    if(textboxes.size() > 0) {
        //Finds current conversation index
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

void PetList::newConvo(Pet* pet, Adoptee *adoptee) {
    Conversation* convo = new Conversation;
    convo->usernameAdopter = pfptr->profileWindow->userInfoAdopter->username;
    convo->petId = pet->id;
    convo->usernameAdoptee = adoptee->username;
    vector<QString> empty;
    convo->messages = empty;
    if(pfptr->matchmaker->DM->addConversation(convo)) {
        adopteesChatting.push_back(adoptee);
        petsChatting.push_back(pet);
        vector<QString> vec;
        textboxes.push_back(vec);
        //If adoptee doesn't have an associated shelter, display their username instead
        if(adoptee->shelter.compare("") == 0) {
            ui->otherConvos->addItem(QString::fromStdString(pet->name + " from " + adoptee->username));
        } else {
            ui->otherConvos->addItem(QString::fromStdString(pet->name + " from " + adoptee->shelter));
        }
        comboNum++;
    } else {
        cout << "New conversation failed" << endl;
    }
}

Adopter* PetList::getAdopterChatting(int index) {
    return adoptersChatting.at(index);
}

void PetList::deleteIndex(int petId) {
    for(int i = 0; i < comboNum; i++) {
        if(petId == ui->otherConvos->itemData(i)) {
            ui->otherConvos->removeItem(i);
        }
    }
}

void PetList::closeEvent(QCloseEvent* event) {
    pfptr->closeEvent(event);
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

    /*for(Pet* p : petsChatting) {
        int flag = 0;
        for(Pet* pp : pfptr->petList) {
            if(p->id != pp->id) {
                flag++;
            }
        }
        if(flag == pfptr->petList.size() - 1) {
            ui->otherConvos->removeItem(index);
            return;
        }
    }*/

    QString text = "";
    for(QString i : textboxes.at(convoIndex)) {
        text.append(i + "\n");
    }
    ui->chatbox->setText(text);
    if(pfptr->isUserAdopter && adopteesChatting.size() > 0) {
        ui->chatTitle->setText
                (QString::fromStdString("Chatting with " + adopteesChatting.at(convoIndex)->username +
                                        " from " + adopteesChatting.at(convoIndex)->shelter));
    } else if (!pfptr->isUserAdopter && adoptersChatting.size() > 0) {
        ui->chatTitle->setText
                (QString::fromStdString("Chatting with " + adoptersChatting.at(convoIndex)->username));
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
