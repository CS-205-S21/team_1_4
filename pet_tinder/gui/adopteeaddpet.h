#ifndef ADOPTEEADDPET_H
#define ADOPTEEADDPET_H

#include <QWidget>
#include <QFileDialog>
#include "petfinder.h"
#include "../databasemanager/databasemanager.h"
namespace Ui {
class AdopteeAddPet;
}
class PetFinder;
class AdopteeAddPet : public QWidget
{
    Q_OBJECT

public:
    explicit AdopteeAddPet(QWidget *parent = 0);
    ~AdopteeAddPet();
    Pet input;
    PetFinder *pnter;
private slots:
    void on_btn_image_clicked();

   // void on_pushButton_2_clicked();

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

    void on_bioBox_textChanged(const QString &arg1);

private:
    Ui::AdopteeAddPet *ui;
};

#endif // ADOPTEEADDPET_H
