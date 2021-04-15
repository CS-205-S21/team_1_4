#include "screen.h"
#include "ui_screen.h"

Screen::Screen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Screen)
{
    ui->setupUi(this);
    initialize();
}

void Screen::initialize(){
    QImage img("/home/wandt/Project/team_1_4/pet_tinder/gui/Duck_gui.jfif");
    QPixmap pic;
    pic.convertFromImage(img.scaled(200, 300, Qt::KeepAspectRatio), 0);
    ui->animalImage->setPixmap(pic);
}

Screen::~Screen()
{
    delete ui;
}
