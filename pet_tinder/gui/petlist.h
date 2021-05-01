#ifndef PETLIST_H
#define PETLIST_H

#include <QWidget>
#include "petfinder.h"
#include "petlist.h"
#include "messagescreen.h"

namespace Ui {
class PetList;
}

class PetFinder;
class ProfilePage;
class MessageScreen;

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

    void on_chatButton1_clicked();

private:
    Ui::PetList *ui;
    MessageScreen *messageWindow;
};

#endif // PETLIST_H
