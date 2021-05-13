#ifndef PETFINDER_H
#define PETFINDER_H

#include "profilepage.h"
#include "petlist.h"
#include <QMainWindow>
#include <QWidget>

#include "../matchmaking/matchmaker.h"

namespace Ui {
class PetFinder;
}

class ProfilePage;
class PetList;

class PetFinder : public QMainWindow {
    Q_OBJECT

public:
    explicit PetFinder(QWidget *parent = 0);
    ~PetFinder();
    void initialize();
    void setup();
    void displayPet(Pet *pet);
    void displayEmptyPet();

    Matchmaker *matchmaker;
    ProfilePage *profileWindow;
    PetList *petListWindow;

    bool isUserAdopter;
    bool deleteClicked = false;

    vector<Pet*> petList; //Holds all pets pet finder can display
    int petIndex; //Current pet index in petList

private slots:

    void on_profileButton_clicked();
    void on_petListButton_clicked();

    void on_deleteButton_clicked();

    void on_likeButton_clicked();

    void on_dislikeButton_clicked();

private:
    Ui::PetFinder *ui;
};

#endif //PETFINDER_H
