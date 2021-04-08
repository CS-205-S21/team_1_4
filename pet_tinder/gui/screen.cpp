#include "screen.h"
#include "ui_screen.h"

Screen::Screen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Screen)
{
    ui->setupUi(this);
}

void Screen::initialize(){
    QImage img("/home/demelfid/project/team_1_4/pet_tinder/gui/Duck_gui.jfif");
    QImage img2 = img.scaled(200, 300, Qt::KeepAspectRatio);
    QPixmap pic;
    pic.convertFromImage(img2, 0);
    ui->animalImage->setPixmap(pic);
}

Screen::~Screen()
{
    delete ui;
}
