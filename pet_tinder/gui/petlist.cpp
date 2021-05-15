#include "petlist.h"
#include "ui_petlist.h"

PetList::PetList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PetList)
{
    ui->setupUi(this);
    messageWindow = new MessageScreen();
    messageWindow->plptr = this;
    pfptr = NULL;
    ppptr = NULL;

    validMessage = false;
    ui->invalidWarning->setVisible(false);
}

PetList::~PetList()
{
    delete ui;
}

void PetList::on_homeButton_clicked()
{
    this->hide();
    pfptr->showMaximized();
}

void PetList::on_profileButton_clicked()
{
    this->hide();
    ppptr->showMaximized();
}

void PetList::on_chatButton1_clicked()
{
    this->hide();
    messageWindow->showMaximized();
}

void PetList::on_lineEdit_textEdited(const QString &arg1)
{
    //Checks if typed message is valid
    //Must have at least one character
    if(arg1.length() > 0) {
        //Can't contain the character '|'
        if(!arg1.contains('|')) {
            typedMessage = arg1;
            validMessage = true;
            ui->invalidWarning->setVisible(false);
        } else {
            ui->invalidWarning->setVisible(true);
            validMessage = false;
        }
    } else {
        validMessage = false;
    }
}

void PetList::on_sendButton_clicked()
{
    if(validMessage) {

    }
}
