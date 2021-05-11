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
    QImage img(":/Duck_gui.jfif");
    QPixmap pic;
    pic.convertFromImage(img.scaled(200, 300, Qt::KeepAspectRatio), 0);
    ui->animalImage->setPixmap(pic);

    isUserAdopter = false;
    ui->homeButton->setEnabled(false);
    if(isUserAdopter == true){
        ui->deleteButton->setVisible(false);
    }
    if(isUserAdopter == false){
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

void PetFinder::on_profileButton_clicked() {
    this->hide();
    profileWindow->showMaximized();
}


void PetFinder::on_petListButton_clicked() {
    this->hide();
    petListWindow->showMaximized();
}

void PetFinder::on_deleteButton_clicked()
{
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

void PetFinder::on_likeButton_clicked()
{
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
    }

}

void PetFinder::on_dislikeButton_clicked()
{
    if(deleteClicked == true){
         ui->deleteWarning->setText("");
       // ui->deleteButton->setEnabled(true);
        ui->deleteButton->setVisible(true);
        QPalette test;
       test.setColor(QPalette::Button, QColor(0,140,0,255));
       ui->likeButton->setText("->");
       ui->dislikeButton->setText("<-");
       ui->dislikeButton->setPalette(test);
       ui->likeButton->setPalette(test);

        deleteClicked = false;

    }
}
