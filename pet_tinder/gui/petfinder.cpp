
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
    petIndex = 0;
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
        displayPet(petList.front());
    } else {
        displayEmptyPet();
    }
}

void PetFinder::setup() {
    if(isUserAdopter == true) {
        ui->deleteButton->setVisible(false);
        QPalette test;
        test.setColor(QPalette::Button, QColor(140,0,0,255));
        ui->likeButton->setText("like");
        ui->dislikeButton->setText("X");
        ui->dislikeButton->setPalette(test);
        test.setColor(QPalette::Button, QColor(0,140,0,255));
        ui->likeButton->setPalette(test);
    } else {
        ui->deleteButton->setVisible(true);
        QPalette test;
        test.setColor(QPalette::Button, QColor(0,140,0,255));
        ui->likeButton->setText("->");
        ui->dislikeButton->setText("<-");
        ui->dislikeButton->setPalette(test);
        ui->likeButton->setPalette(test);
    }
}

PetFinder::~PetFinder() {
    delete ui;
}

//Displays passed-in pet on screen
void PetFinder::displayPet(Pet *pet) {
    //Displays name, sex, and age
    ui->nameSexAge->setText(QString::fromStdString(pet->name + ", " + pet->sex + ", " + to_string(pet->age)));
    //Displays species and breed
    ui->speciesBreed->setText(QString::fromStdString(pet->species + " - " + pet->breed));
    //Checks if pet is hypoallergenic, then displays that
    if(pet->hypoallergenic == 1) {
        ui->hypoallergenic->setText("Hypoallergenic");
    } else {
        ui->hypoallergenic->setText("Not hypoallergenic");
    }
    //Displays bio
    ui->animalCustomBio->setText(QString::fromStdString(pet->bio));
}

//Displays passed-in pet on screen
void PetFinder::displayEmptyPet() {
    //Displays name, sex, and age
    ui->nameSexAge->setText("No more pets match your preferences!");
    //Displays species and breed
    ui->speciesBreed->clear();
    //Checks if pet is hypoallergenic, then displays that
    ui->hypoallergenic->clear();
    //Displays bio
    ui->animalCustomBio->setText("Update your preferences in the Profile "
                                 "or wait around for new pets to be added!");
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

        deleteClicked = false;
    } else {
        //Iterates one up through the petList
        if(petList.size() > 0 && petIndex + 1 < (int)petList.size()) {
            cout << "GUI PetFinder screen: Like button clicked, next pet displayed" << endl;
            //Adds pet id to user info's liked pet list
            profileWindow->userInfoAdopter->likedPetIds.push_back(petList.at(petIndex)->id);
            petIndex++;
            displayPet(petList.at(petIndex));
        } else {
            cout << "GUI PetFinder screen: Like button clicked, no more pets to display" << endl;
            displayEmptyPet();
        }
    }

}

void PetFinder::on_dislikeButton_clicked()
{
    if(deleteClicked == true){
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
    } else {
        //Iterates one up through the petList
        if(petList.size() > 0 && petIndex + 1 < (int)petList.size()) {
            cout << "GUI PetFinder screen: Like button clicked, next pet displayed" << endl;
            //Adds pet id to user info's liked pet list
            profileWindow->userInfoAdopter->dislikedPetIds.push_back(petList.at(petIndex)->id);
            petIndex++;
            displayPet(petList.at(petIndex));
        } else {
            cout << "GUI PetFinder screen: Like button clicked, no more pets to display" << endl;
            displayEmptyPet();
        }
    }
}
