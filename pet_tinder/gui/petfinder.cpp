#include "petfinder.h"
#include "ui_petfinder.h"

PetFinder::PetFinder(QWidget *parent) : QMainWindow(parent), ui(new Ui::PetFinder) {
    ui->setupUi(this);
    initialize();
    profileWindow = new ProfilePage();
    petListWindow = new PetList();

    profileWindow->pfptr = this;
    profileWindow->plptr = petListWindow;
    petListWindow->pfptr = this;
    petListWindow->ppptr = profileWindow;
}

void PetFinder::initialize() {
    QImage img("/home/demelfid/project/team_1_4/pet_tinder/gui/Duck_gui.jfif");
    QPixmap pic;
    pic.convertFromImage(img.scaled(200, 300, Qt::KeepAspectRatio), 0);
    ui->animalImage->setPixmap(pic);
    //matchmaker = new Matchmaker();
    //matchmaker->DatabaseInterface("")
}

PetFinder::~PetFinder() {
    delete ui;
}

void PetFinder::on_profileButton_clicked() {
    this->hide();
    profileWindow->showMaximized();
}


void PetFinder::on_petListButton_clicked() {
    this->hide();
    petListWindow->showMaximized();
}
