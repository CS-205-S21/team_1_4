#include "homescreen.h"
#include "ui_homescreen.h"

HomeScreen::HomeScreen(QWidget *parent):QWidget(parent), ui(new Ui::HomeScreen) {
    ui->setupUi(this);

    petWindow = new PetFinder();

    username = "";
    password = "";
}

HomeScreen::~HomeScreen() {
    delete ui;
}

void HomeScreen::on_loginButton_clicked() {
    //Tests if user in an adopter
    Adopter* userInfoAdopter = petWindow->matchmaker->DM->readInAdopter(username, password);
    //Checks if this adopter exists
    if(userInfoAdopter != nullptr) {
        cout << "Test1" << endl;
        //Passes adopter to database to begin matchmaking
        //petWindow->matchmaker->DatabaseInterface(username, password);
        //Passes adopter to profileWindow to display their info
        petWindow->profileWindow->userInfoAdopter = userInfoAdopter;
        this->hide();
        petWindow->showMaximized();
    } else {
        //Tests if user in an adoptee
        Adoptee* userInfoAdoptee = petWindow->matchmaker->DM->readInAdoptee(username, password);
        if(userInfoAdoptee != nullptr) {
            //Passes adoptee to profileWindow to display their info
            petWindow->profileWindow->userInfoAdoptee = userInfoAdoptee;
            this->hide();
            petWindow->showMaximized();
        } else {
            cout << "Login failed!" << endl; //DISPLAY ON SCREEN LATER
        }
    }
}

void HomeScreen::on_usernameInput_textEdited(const QString &arg1) {
    username = arg1.toStdString();
}
void HomeScreen::on_passwordInput_textEdited(const QString &arg1) {
    password = arg1.toStdString();
}
