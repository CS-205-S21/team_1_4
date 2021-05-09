#ifndef PROFILEPAGE_H
#define PROFILEPAGE_H

#include <QWidget>
#include "petfinder.h"
#include "petlist.h"

#include "../databasemanager/databasemanager.h"

namespace Ui {
class ProfilePage;
}

class Screen;
class PetFinder;
class PetList;

class ProfilePage : public QWidget
{
    Q_OBJECT

public:
    explicit ProfilePage(QWidget *parent = 0);
    ~ProfilePage();

    Screen *scrptr;
    PetFinder *pfptr;
    PetList *plptr;

    Adopter* userInfoAdopter;
    Adoptee* userInfoAdoptee;

signals:

public slots:

private slots:
    void on_homeButton_clicked();

    void on_petListButton_clicked();

private:
    Ui::ProfilePage *ui;
};

#endif // PROFILEPAGE_H
