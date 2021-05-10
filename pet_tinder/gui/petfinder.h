#ifndef PETFINDER_H
#define PETFINDER_H

#include "profilepage.h"
#include "petlist.h"
#include <QMainWindow>
#include <QWidget>

#include "../matchmaking/matchmaker.h"
#include "../databasemanager/databasemanager.h"

namespace Ui {
class PetFinder;
}

class ProfilePage;
class PetList;

class PetFinder : public QMainWindow
{
    Q_OBJECT

public:
    explicit PetFinder(QWidget *parent = 0);
    ~PetFinder();
    void initialize();

    Matchmaker *matchmaker;
    ProfilePage *profileWindow;
    PetList *petListWindow;

    bool isUserAdopter;

private slots:

    void on_profileButton_clicked();
    void on_petListButton_clicked();

private:
    Ui::PetFinder *ui;
};

#endif //PETFINDER_H
