#ifndef PETLIST_H
#define PETLIST_H

#include <QWidget>
#include "petfinder.h"
#include "petlist.h"

namespace Ui {
class PetList;
}

class PetFinder;
class ProfilePage;

class PetList : public QWidget
{
    Q_OBJECT

public:
    explicit PetList(QWidget *parent = nullptr);
    ~PetList();

    PetFinder *pfptr;
    ProfilePage *ppptr;

signals:

public slots:

private slots:
    void on_homeButton_clicked();

    void on_profileButton_clicked();

private:
    Ui::PetList *ui;
};

#endif // PETLIST_H
