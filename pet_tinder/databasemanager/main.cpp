#include <iostream>
#include "databasemanager.h"

using namespace std;

int main() {
    cout << "Database main, for testing purposes only" << endl;

    DatabaseManager* dm = new DatabaseManager;
    dm->readInPets();
    cout << dm->findPet(1)->name << endl;
    cout << dm->findPet(2)->name << endl;
    dm->findPet(4)->name;
    cout << dm->findPet(5)->name << endl << endl;

    //cout << dm->isUsernameTaken("Glue") << endl << endl;

    cout << "User: " + dm->findAdopterPet(1)->username << endl;
    cout << "User: " + dm->findAdopteePet(1)->username << endl << endl;

    vector<QString> vec = dm->messageParse("Kate: AHAHHHHHH|Glue: GIUDHGUIDGUI|Kate: SCREAMING|");
    for(QString i : vec) {
        cout << i.toStdString() << endl;
    }
}
