#include "homescreen.h"
#include "ui_homescreen.h"

HomeScreen::HomeScreen(QWidget *parent):QWidget(parent), ui(new Ui::HomeScreen) {
    ui->setupUi(this);

    petWindow = new PetFinder();

    username = "";
    password = "";
    AApointer = new AddAccount();
    QImage img(":/claws.png");
    QPixmap pic2;
    pic2.convertFromImage(img.scaled(829, 786, Qt::KeepAspectRatio), 0);
    ui->logo->setPixmap(pic2);
    ui->loginFailedLabel->setVisible(false);

    //databaseManager = new DatabaseManager();
}

HomeScreen::~HomeScreen() {
    delete ui;
}

void HomeScreen::login() {
    //Tests if user in an adopter
    Adopter* userInfoAdopter = petWindow->matchmaker->DM->readInAdopter(username, password);
    //Checks if this adopter exists
    if(userInfoAdopter != nullptr) {
        //Lets rest of gui know that user is an adopter
        petWindow->isUserAdopter = true;
        //Passes adopter to database to begin matchmaking
        petWindow->petList = petWindow->matchmaker->DatabaseInterface(userInfoAdopter);

        //Passes adopter to profileWindow and displays their info
        petWindow->profileWindow->userInfoAdopter = userInfoAdopter;
        petWindow->profileWindow->displayUserInfo(true);

        //Initialize pet window & pet list window's displays
        petWindow->initialize();
        petWindow->petListWindow->initialize();

        //Change window to pet window
        this->hide();
        petWindow->showMaximized();

    } else {
        //Tests if user in an adoptee
        Adoptee* userInfoAdoptee = petWindow->matchmaker->DM->readInAdoptee(username, password);
        //Tests if this adoptee exists
        if(userInfoAdoptee != nullptr) {
            cout << "Adoptee Login Successful!" << endl;
            //Lets rest of gui know that user is an adoptee
            petWindow->isUserAdopter = false;

            //Reads in pets (normally happens automatically,
            // but matchmaking is not required for adoptees)
            petWindow->matchmaker->DM->readInPets();

            //Passes adoptee's pets to the pet list window's petList
            for(int i : userInfoAdoptee->ownedPetIds) {
                if(petWindow->matchmaker->DM->getNumPets() > 0) {
                    petWindow->petList.push_back(petWindow->matchmaker->DM->findPet(i));
                } else {
                    cout << "Adoptee's pet id: " + to_string(i) + " does not exist"
                            " or was not read in properly" << endl;
                }
            }
            remove(petWindow->petList.begin(), petWindow->petList.end(), nullptr);

            //Passes adoptee to profileWindow and displays their info
            petWindow->profileWindow->userInfoAdoptee = userInfoAdoptee;
            petWindow->profileWindow->displayUserInfo(false);

            //Initialize pet window & pet list window's displays
            petWindow->initialize();
            petWindow->petListWindow->initialize();

            //Change window to pet window
            this->hide();
            petWindow->showMaximized();
        } else {
            ui->loginFailedLabel->setVisible(true);
            cout << "Login failed!" << endl; //DISPLAY ON SCREEN LATER
        }
    }
}

void HomeScreen::closeEvent(QCloseEvent *event) {
    petWindow->closeEvent(event);
}

void HomeScreen::on_loginButton_clicked() {
    login();
}

void HomeScreen::on_usernameInput_textEdited(const QString &arg1) {
    username = arg1.toStdString();
}
void HomeScreen::on_passwordInput_textEdited(const QString &arg1) {
    password = arg1.toStdString();
}

void HomeScreen::on_newAccount_clicked() {
    AApointer->PfPnter = petWindow;
    AApointer->show();
}

void HomeScreen::on_usernameInput_returnPressed() {
    login();
}

void HomeScreen::on_passwordInput_returnPressed() {
    login();
}
