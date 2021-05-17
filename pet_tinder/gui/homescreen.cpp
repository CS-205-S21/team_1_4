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

    //databaseManager = new DatabaseManager();
}

HomeScreen::~HomeScreen() {
    delete ui;
}

void HomeScreen::on_loginButton_clicked() {
    //Tests if user in an adopter
    Adopter* userInfoAdopter = petWindow->matchmaker->DM->readInAdopter(username, password);
    //Checks if this adopter exists
    if(userInfoAdopter != nullptr) {
        //Lets rest of gui know that user is an adopter
        petWindow->isUserAdopter = true;
        //Passes adopter to database to begin matchmaking
        petWindow->petList = petWindow->matchmaker->DatabaseInterface(username, password);

        //Passes adopter to profileWindow and displays their info
        petWindow->profileWindow->userInfoAdopter = userInfoAdopter;
        petWindow->profileWindow->displayUserInfo(true);
        petWindow->petListWindow->initialize();

        //Initialize pet window's display
        petWindow->initialize();

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

            //Passes adoptee to profileWindow and displays their info
            petWindow->profileWindow->userInfoAdoptee = userInfoAdoptee;
            petWindow->profileWindow->displayUserInfo(false);

            //Initialize pet window's display
            petWindow->initialize();

            //Change window to pet window
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

void HomeScreen::on_newAccount_clicked()
{
    AApointer->PfPnter = petWindow;
    AApointer->show();
}
