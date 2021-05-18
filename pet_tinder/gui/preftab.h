#ifndef PREFTAB_H
#define PREFTAB_H
#include "../databasemanager/databasemanager.h"
#include <QWidget>
#include "preftab.h"
#include "petfinder.h"

namespace Ui {
class PrefTab;
}
class PetFinder;
class PrefTab : public QWidget
{
    Q_OBJECT

public:
    void populateBoxes();
    explicit PrefTab(QWidget *parent = 0);
    ~PrefTab();
    Adopter input;
    PetFinder *pnter;
    void userProofing();

private slots:
    void on_pushButton_2_clicked();

    void on_prefSaveButton_clicked();

    void on_speciesInput_textChanged(const QString &arg1);

    void on_breedInput_textChanged(const QString &arg1);

    void on_ageInput_textChanged(const QString &arg1);

    void on_weightInput_textChanged(const QString &arg1);

    void on_colorInput_textChanged(const QString &arg1);

    void on_comboBoxSex_currentIndexChanged(const QString &arg1);

    void on_comboBoxHypo_currentIndexChanged(int index);

    void on_speciesReqInput_stateChanged(int arg1);

    void on_breedReqInput_stateChanged(int arg1);

    void on_ageReqInput_stateChanged(int arg1);

    void on_weightReqInput_stateChanged(int arg1);

    void on_colorReqIput_stateChanged(int arg1);

    void on_sexReqInput_stateChanged(int arg1);

    void on_hypoReqInput_stateChanged(int arg1);

private:
    Ui::PrefTab *ui;
};

#endif // PREFTAB_H
