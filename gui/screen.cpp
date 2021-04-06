#include "screen.h"
#include "ui_screen.h"

screen::screen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::screen)
{
    ui->setupUi(this);
}

screen::~screen()
{
    delete ui;
}
