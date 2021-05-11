#ifndef PREFTAB_H
#define PREFTAB_H
#include "../databasemanager/databasemanager.h"
#include <QWidget>
#include "preftab.h"

namespace Ui {
class PrefTab;
}
class PetFinder;
class PrefTab : public QWidget
{
    Q_OBJECT

public:

    explicit PrefTab(QWidget *parent = 0);
    ~PrefTab();
    Adopter input;
    PetFinder *pnter;

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::PrefTab *ui;
};

#endif // PREFTAB_H
