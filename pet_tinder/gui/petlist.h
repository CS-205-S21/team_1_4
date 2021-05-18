#ifndef PETLIST_H
#define PETLIST_H

#include <QWidget>
#include "vector"
#include "petfinder.h"
#include "petlist.h"
#include "messagescreen.h"
#include "chatinfo.h"

#include "../matchmaking/matchmaker.h"

namespace Ui {
class PetList;
}

class ChatInfo;
class PetFinder;
class ProfilePage;

class PetList : public QWidget {
    Q_OBJECT

public:
    explicit PetList(QWidget *parent = nullptr);
    ~PetList();
    void initialize();
    void sendMessage();
    void newConvo(Pet* pet, Adoptee* adoptee);
    Adopter* getAdopterChatting(int index);
    void reset();
    void deleteIndex(int petId);

    void closeEvent(QCloseEvent* event);

    PetFinder* pfptr;
    ProfilePage* ppptr;
    ChatInfo* ciptr;

    //Adopters user is chatting (used only if they are an adoptee)
    std::vector<Adopter*> adoptersChatting;
    //Adoptees user is chatting (used only if they are an adopter)
    std::vector<Adoptee*> adopteesChatting;
    //Pets user is chatting, location should always be lined up with adopter
    // or adoptee who likes/owns the pet
    std::vector<Pet*> petsChatting;

    //Textboxes containing conversations between user and other, should
    // always line up with adoptersChatting or adopteesChatting
    vector<vector<QString>> textboxes;
    QString typedMessage;
    bool validMessage;
    int convoIndex;
    int comboNum;

    //String to display when no messages have been sent
    QString noMessagesDisplay;


signals:

public slots:

private slots:
    void on_homeButton_clicked();

    void on_profileButton_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_sendButton_clicked();

    void on_lineEdit_returnPressed();

    void on_otherConvos_currentIndexChanged(int index);

    void on_petInfoButton_clicked();

    void on_shelterInfoButton_clicked();

private:
    Ui::PetList *ui;
};

#endif // PETLIST_H
