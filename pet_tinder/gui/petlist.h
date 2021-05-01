#ifndef PETLIST_H
#define PETLIST_H

#include <QWidget>
#include "petfinder.h"
#include "petlist.h"

namespace Ui {
class PetList;
}

<<<<<<< HEAD
class Screen;
=======
class PetFinder;
>>>>>>> 9f62d6c7fa5d73a41bdadbc20d72cc5fe6724d63
class ProfilePage;

class PetList : public QWidget
{
    Q_OBJECT

public:
    explicit PetList(QWidget *parent = nullptr);
    ~PetList();

<<<<<<< HEAD
    Screen *scrptr;
=======
    PetFinder *pfptr;
>>>>>>> 9f62d6c7fa5d73a41bdadbc20d72cc5fe6724d63
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
