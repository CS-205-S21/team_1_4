#include "screen.h"
#include "ui_screen.h"

Screen::Screen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Screen)
{
    ui->setupUi(this);
    initialize();
    profileWindow = new ProfilePage();
    petListWindow = new PetList();

    profileWindow->scrptr = this;
    profileWindow->plptr = petListWindow;
    petListWindow->scrptr = this;
    petListWindow->ppptr = profileWindow;
}

void Screen::initialize(){
    QImage img("/home/demelfid/project/team_1_4/pet_tinder/gui/Duck_gui.jfif");
    QPixmap pic;
    pic.convertFromImage(img.scaled(200, 300, Qt::KeepAspectRatio), 0);
    ui->animalImage->setPixmap(pic);
}

Screen::~Screen()
{
    delete ui;
}

void Screen::on_profileButton_clicked()
{
    this->hide();
    profileWindow->showMaximized();
}


void Screen::on_petListButton_clicked()
{
    this->hide();
    petListWindow->showMaximized();
}
