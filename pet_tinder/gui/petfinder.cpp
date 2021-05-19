#include "petfinder.h"
#include "ui_petfinder.h"

PetFinder::PetFinder(QWidget *parent) : QMainWindow(parent), ui(new Ui::PetFinder) {
    ui->setupUi(this);
    profileWindow = new ProfilePage();
    petListWindow = new PetList();
    matchmaker = new Matchmaker();

    profileWindow->pfptr = this;
    profileWindow->plptr = petListWindow;
    petListWindow->pfptr = this;
    petListWindow->ppptr = profileWindow;

    isUserAdopter = true;
    deleteClicked = false;
    loggingOut = false;
    petIndex = -1;
}

//Initializes most variables and display
void PetFinder::initialize() {
    QImage img(":/Duck_gui.jfif");
    QPixmap pic;
    pic.convertFromImage(img.scaled(200, 300, Qt::KeepAspectRatio), 0);
    ui->animalImage->setPixmap(pic);
    ui->homeButton->setEnabled(false);

    setup();

    if(petList.size() > 0) {
        cout << "PetFinder screen display first pet!" << endl;

        if(petList.front() != nullptr) {
            displayPet(petList.front());
            petIndex = 0;
        } else {
            petIndex = 1;
        }
    } else {
        displayEmptyPet();
    }
}

//Sets up visible components of screen depending on type of user
void PetFinder::setup() {
    //If user is adopter
    if(isUserAdopter == true) {
        ui->deleteButton->setVisible(false);
        ui->editPetButton->setVisible(false);
        QPalette test;
        test.setColor(QPalette::Button, QColor(140,0,0,255));
        ui->likeButton->setText("like");
        ui->dislikeButton->setText("X");
        ui->dislikeButton->setPalette(test);
        test.setColor(QPalette::Button, QColor(0,140,0,255));
        ui->likeButton->setPalette(test);
    } else { //If user is adoptee
        ui->deleteButton->setVisible(true);
        ui->editPetButton->setVisible(true);
        QPalette test;
        test.setColor(QPalette::Button, QColor(0,140,0,255));
        ui->likeButton->setText("->");
        ui->dislikeButton->setText("<-");
        ui->dislikeButton->setPalette(test);
        ui->likeButton->setPalette(test);
    }
    //If there are no pets to display
    if(petList.size() <= 0) {
        ui->deleteButton->setVisible(false);
        ui->likeButton->setVisible(false);
        ui->dislikeButton->setVisible(false);
        ui->animalImage->setVisible(false);
        ui->editPetButton->setVisible(false);
    }
}

PetFinder::~PetFinder() {
    delete ui;
}

//Displays passed-in pet on screen
void PetFinder::displayPet(Pet *pet) {
    ui->likeButton->setVisible(true);
    ui->dislikeButton->setVisible(true);
    ui->animalImage->setVisible(true);
    if(!isUserAdopter) {
        ui->deleteButton->setVisible(true);
        ui->editPetButton->setVisible(true);
    }

    //Displays name, sex, and age
    ui->nameSexAge->setText(QString::fromStdString(pet->name + ", " + pet->sex + ", " +
                                                   to_string(pet->age) + " years old"));
    //Displays species and breed
    ui->speciesBreed->setText(QString::fromStdString(pet->species + " - " + pet->breed));
    //Checks if pet is hypoallergenic, then displays that
    if(pet->hypoallergenic == 1) {
        ui->hypoallergenicWeight->setText
                ("Hypoallergenic & weighs " + QString::number(pet->weight) + " pounds");
    } else {
        ui->hypoallergenicWeight->setText
                ("Not hypoallergenic & weighs " + QString::number(pet->weight) + " pounds");
    }
    //Displays bio
    ui->animalCustomBio->setText(QString::fromStdString(pet->bio));
    //Displays image
    QPixmap pic;
    pic.loadFromData(pet->image);
    pic.scaled(200, 300, Qt::KeepAspectRatio);
    ui->animalImage->setPixmap(pic);
}

//Displays passed-in pet on screen
void PetFinder::displayEmptyPet() {
    ui->deleteButton->setVisible(false);
    ui->likeButton->setVisible(false);
    ui->dislikeButton->setVisible(false);
    ui->animalImage->setVisible(false);
    ui->editPetButton->setVisible(false);
    //Empty pet for adopter
    if(isUserAdopter) {
        //Displays name, sex, and age
        ui->nameSexAge->setText("No more pets match your preferences!");
        //Displays species and breed
        ui->speciesBreed->clear();
        //Checks if pet is hypoallergenic, then displays that
        ui->hypoallergenicWeight->clear();
        //Displays bio
        ui->animalCustomBio->setText("Update your preferences in the Profile "
                                     "or wait around for new pets to be added!");
        //Empty pet for adoptee
    } else {
        //Displays name, sex, and age
        ui->nameSexAge->setText("You haven't created any pet profiles yet!");
        //Displays species and breed
        ui->speciesBreed->clear();
        //Checks if pet is hypoallergenic, then displays that
        ui->hypoallergenicWeight->clear();
        //Displays bio
        ui->animalCustomBio->setText("You can add new pet profiles "
                                     "in the profile screen!");
    }
}

void PetFinder::editPet(Pet* pet) {
    if(petList.size() > 0) {
        pet->id = petList.at(petIndex)->id;
        petList.at(petIndex) = pet;
        displayPet(pet);
        matchmaker->DM->updatePet(pet);
    }
}

void PetFinder::closeEvent(QCloseEvent *event) {
    //Creates & displays exit pop-up screen
    QMessageBox::StandardButton exitButton =
            QMessageBox::question(this, "Claws n' Paws", tr("Are you sure you wish to exit?\n"),
                                  QMessageBox::Cancel | QMessageBox::No
                                  | QMessageBox::Yes, QMessageBox::No);
    //If exit is confirmed...
    if(exitButton == QMessageBox::Yes) {
        //Read out user info
        //If user is adopter
        if(isUserAdopter) {
            matchmaker->DM->updateAdopter(profileWindow->userInfoAdopter);
        } else { //If user is adoptee
            matchmaker->DM->updateAdoptee(profileWindow->userInfoAdoptee);
        }

        //Read out conversations
        for(int i = 0; i < (int)petListWindow->textboxes.size(); i++) {
            Conversation* convo = new Conversation;
            if(isUserAdopter) {
                convo->usernameAdopter = profileWindow->userInfoAdopter->username;
                convo->usernameAdoptee = petListWindow->adopteesChatting.at(i)->username;
            } else {
                convo->usernameAdoptee = profileWindow->userInfoAdoptee->username;
                convo->usernameAdopter = petListWindow->adoptersChatting.at(i)->username;
            }
            convo->petId = petListWindow->petsChatting.at(i)->id;
            if(petListWindow->textboxes.size() > 0) {
                convo->messages = petListWindow->textboxes.at(i);
            } else {
                convo->messages.push_back("");
            }

            matchmaker->DM->updateConversation(convo);
        }

        event->accept();
        if(loggingOut) {
            loggingOut = false;
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        }
    } else {
        event->ignore();
    }
}

void PetFinder::on_profileButton_clicked() {
    this->hide();
    profileWindow->showMaximized();
}


void PetFinder::on_petListButton_clicked() {
    this->hide();
    petListWindow->showMaximized();
}

void PetFinder::on_deleteButton_clicked() {
    deleteClicked = true;
    // ui->deleteButton->setEnabled(false);
    ui->deleteButton->setVisible(false);
    ui->deleteWarning->setText("Are you sure you want to delete this pet?");
    QPalette test;
    test.setColor(QPalette::Button, QColor(0,140,0,255));
    ui->dislikeButton->setText("NO");
    ui->dislikeButton->setPalette(test);
    test.setColor(QPalette::Button, QColor(140,0,0,255));
    ui->likeButton->setPalette(test);
    ui->likeButton->setText("YES");

}

void PetFinder::on_likeButton_clicked() {
    //likeButton = delete confirm
    if(deleteClicked == true){
        ui->deleteWarning->setText("");
        //  ui->deleteButton->setEnabled(true);
        ui->deleteButton->setVisible(true);
        QPalette test;
        test.setColor(QPalette::Button, QColor(0,140,0,255));
        ui->likeButton->setText("->");
        ui->dislikeButton->setText("<-");
        ui->dislikeButton->setPalette(test);
        ui->likeButton->setPalette(test);

        //Ask user to confirm their deletion
        //Creates & displays confirmation pop-up screen
        QMessageBox::StandardButton exitButton =
                QMessageBox::question(this, "Claws n' Paws", tr("Deleting this pet will require you to "
                                                                "re-enter your credentials. Delete anyway?\n"),
                                      QMessageBox::Cancel | QMessageBox::No
                                      | QMessageBox::Yes, QMessageBox::No);
        if(exitButton == QMessageBox::Yes) {
            //DELETING PET
            Pet* deletedPet = petList.at(petIndex);
            if(matchmaker->DM->removePet(deletedPet->id)) {
                //Delete pet from pet database
                vector<Adopter*> petLikers = matchmaker->DM->findAdopterPet(deletedPet->id);
                //Delete conversations about pet from conversation database
                for(Adopter* petLiker : petLikers) {
                    matchmaker->DM->removeConversation(petLiker->username, deletedPet->id);
                }

                //Delete ongoing conversation from PetList window
                for(int i = 0; i < petListWindow->petsChatting.size(); i++) {
                    if(petListWindow->petsChatting.at(i)->id == deletedPet->id) {
                        petListWindow->petsChatting.erase(petListWindow->petsChatting.begin() + i);
                        petListWindow->adoptersChatting.erase(petListWindow->adoptersChatting.begin() + i);
                        petListWindow->textboxes.erase(petListWindow->textboxes.begin() + i);
                    }
                }

                //Delete pet from petList
                petList.erase(petList.begin() + petIndex);
                //Delete pet id from owned pet list for current user
                for(int i = 0; i < profileWindow->userInfoAdoptee->ownedPetIds.size(); i++) {
                    if(profileWindow->userInfoAdoptee->ownedPetIds.at(i) == deletedPet->id) {
                        profileWindow->userInfoAdoptee->ownedPetIds.erase
                                (profileWindow->userInfoAdoptee->ownedPetIds.begin() + i);
                    }
                }
                //Delete pet id from liked pet list for all users
                for(Adopter* petLiker : petLikers) {
                    for(int i = 0; i < petLiker->likedPetIds.size(); i++) {
                        if(petLiker->likedPetIds.at(i) == deletedPet->id) {
                            petLiker->likedPetIds.erase(petLiker->likedPetIds.begin() + i);
                        }
                    }
                    //remove(petLiker->likedPetIds.begin(), petLiker->likedPetIds.end(), deletedPet->id);
                    matchmaker->DM->updateAdopter(petLiker);
                }

                loggingOut = true;
                QWidget::close();

                /*
                if(petIndex >= petList.size() - 1) {
                    petIndex--;
                }
                displayPet(petList.at(petIndex));
                //petListWindow->reset();
                //petListWindow->deleteIndex(deletedPet->id);
                petListWindow->initialize();*/
            }
        }
        deleteClicked = false;

    } else { //likeButton = like/right arrow
        Pet* likedPet = petList.at(petIndex);
        //Iterates one up through the petList
        if(petList.size() > 0 && petIndex + 1 < (int)petList.size()) {
            cout << "GUI PetFinder screen: Like button clicked, next pet displayed" << endl;
            //Adds pet id to user info's liked pet list
            petIndex++;
            if(petList.at(petIndex) != nullptr) {
                displayPet(petList.at(petIndex));
            }
        } else if(isUserAdopter) {
            cout << "GUI PetFinder screen: Like button clicked, no more pets to display" << endl;
            displayEmptyPet();
        }

        //If user is adopter, like pet
        if(isUserAdopter) {
            //Find adoptee who owns liked pet
            Adoptee* adoptee = matchmaker->DM->findAdopteePet(likedPet->id);
            if(adoptee != nullptr) {
                //Adds this pet to user's list of liked pets
                profileWindow->userInfoAdopter->likedPetIds.push_back(likedPet->id);
                //Begins conversation with adoptee who owns pet
                petListWindow->newConvo(likedPet, adoptee);
            } else {
                cout << "ERROR: Pet doesn't have an owner, that shouldn't be a thing" << endl;
            }
        }
    }

}

void PetFinder::on_dislikeButton_clicked()
{
    //dislikeButton = delete cancel
    if(deleteClicked == true) {
        ui->deleteWarning->setText("");
        //ui->deleteButton->setEnabled(true);
        ui->deleteButton->setVisible(true);
        QPalette test;
        test.setColor(QPalette::Button, QColor(0,140,0,255));
        ui->likeButton->setText("->");
        ui->dislikeButton->setText("<-");
        ui->dislikeButton->setPalette(test);
        ui->likeButton->setPalette(test);

        deleteClicked = false;
    } else if(isUserAdopter) { //dislikeButton = dislike (adopter)
        //Iterates one up through the petList
        if(petList.size() > 0 && petIndex + 1 < (int)petList.size()) {
            cout << "GUI PetFinder screen: Like button clicked, next pet displayed" << endl;
            profileWindow->userInfoAdopter->dislikedPetIds.push_back(petList.at(petIndex)->id);
            petIndex++;
            if(petList.at(petIndex) != nullptr) {
                displayPet(petList.at(petIndex));
            }
        } else {
            cout << "GUI PetFinder screen: Like button clicked, no more pets to display" << endl;
            displayEmptyPet();
        }
    } else { //dislikeButton = left arrow (adoptee)
        //Iterates one up through the petList
        if(petList.size() > 0 && petIndex - 1 >= 0) {
            cout << "GUI PetFinder screen: left arrow clicked, previous pet displayed" << endl;
            petIndex--;
            if(petList.at(petIndex) != nullptr) {
                displayPet(petList.at(petIndex));
            }
        }
    }
}

void PetFinder::on_editPetButton_clicked() {
    profileWindow->aap->setupPet(petList.at(petIndex));
    profileWindow->aap->isNewPet = false;
    profileWindow->aap->show();
}
