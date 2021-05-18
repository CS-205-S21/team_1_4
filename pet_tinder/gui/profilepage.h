#ifndef PROFILEPAGE_H
#define PROFILEPAGE_H

#include <QWidget>
#include "petfinder.h"
#include "petlist.h"
#include "adopteeaddpet.h"
#include "preftab.h"
#include "../databasemanager/databasemanager.h"

namespace Ui {
class ProfilePage;
}
class PrefTab;
class Screen;
class PetFinder;
class PetList;
class AdopteeAddPet;
class ProfilePage : public QWidget
{
    Q_OBJECT

public:
    explicit ProfilePage(QWidget *parent = 0);
    ~ProfilePage();
    AdopteeAddPet *aap;
    Screen *scrptr;
    PetFinder *pfptr;
    PetList *plptr;
    PrefTab *ptpnter;
    Adopter* userInfoAdopter;
    Adoptee* userInfoAdoptee;

    bool editingBio;
    QString bioText;

    void displayUserInfo(bool adopter);

    void closeEvent(QCloseEvent *event);

signals:

public slots:

private slots:
    void on_homeButton_clicked();

    void on_petListButton_clicked();

    void on_pushButton_2_clicked();

    void on_PrefsButton_clicked();

    void on_addPetButton_clicked();

    void on_editBioButton_clicked();

    void on_bioEdit_textEdited(const QString &arg1);

private:
    Ui::ProfilePage *ui;
};

#endif // PROFILEPAGE_H
