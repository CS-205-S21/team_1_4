#ifndef PETFINDER_H
#define PETFINDER_H

#include "profilepage.h"
#include "petlist.h"
#include <QMainWindow>

#include "../matchmaking/matchmaker.h"

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

private slots:

    void on_profileButton_clicked();

    void on_petListButton_clicked();

private:
    Ui::PetFinder *ui;
    ProfilePage *profileWindow;
    PetList *petListWindow;
};

#endif //PETFINDER_H
