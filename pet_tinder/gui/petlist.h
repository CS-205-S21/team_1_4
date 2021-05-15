#ifndef PETLIST_H
#define PETLIST_H

#include <QWidget>
#include "vector"
#include "petfinder.h"
#include "petlist.h"
#include "messagescreen.h"

#include "../matchmaking/matchmaker.h"

namespace Ui {
class PetList;
}

class PetFinder;
class ProfilePage;

class PetList : public QWidget {
    Q_OBJECT

public:
    explicit PetList(QWidget *parent = nullptr);
    ~PetList();
    void sendMessage();
    void updateConvos(Pet* pet, Adopter* adopter);
    void updateConvos(Pet* pet, Adoptee* adoptee);

    PetFinder *pfptr;
    ProfilePage *ppptr;

    //Adopters user is chatting (used only if they are an adoptee)
    std::vector<Adopter*> adoptersChatting;
    //Adoptees user is chatting (used only if they are an adopter)
    std::vector<Adoptee*> adopteesChatting;
    //Pets user is chatting, location should always be lined up with adopter
    // or adoptee who likes/owns the pet
    std::vector<Pet*> petsChatting;

    QString textbox;
    QString typedMessage;
    bool validMessage;
    bool noMessages;


signals:

public slots:

private slots:
    void on_homeButton_clicked();

    void on_profileButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_sendButton_clicked();

    void on_otherConvos_currentIndexChanged(const QString &arg1);

    void on_lineEdit_returnPressed();

private:
    Ui::PetList *ui;
};

#endif // PETLIST_H
