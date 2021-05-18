#ifndef ADOPTEEADDPET_H
#define ADOPTEEADDPET_H

#include <QWidget>
#include <QFileDialog>
#include "profilepage.h"
#include "../databasemanager/databasemanager.h"

class ProfilePage;

namespace Ui {
class AdopteeAddPet;
}

class PetFinder;

class AdopteeAddPet : public QWidget
{
    Q_OBJECT

public:
    //True if user is creating a new pet, false if editing an old one
    bool isNewPet;

    explicit AdopteeAddPet(QWidget *parent = 0);
    ~AdopteeAddPet();
    Pet *input;
    ProfilePage *pnter;

    void setupPet(Pet* pet);


private slots:
    void on_btn_image_clicked();

    void on_pushButton_2_clicked();

    void on_discardButton_clicked();

    void on_saveButton_clicked();

    void on_nameInput_textChanged(const QString &arg1);

    void on_speciesInput_textChanged(const QString &arg1);

    void on_breedInput_textChanged(const QString &arg1);

    void on_ageInput_textChanged(const QString &arg1);

    void on_weightInput_textChanged(const QString &arg1);

    void on_colorInput_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);



private:
    Ui::AdopteeAddPet *ui;
};

#endif // ADOPTEEADDPET_H
