#include <iostream>
#include "databasemanager.h"

using namespace std;

int main() {
    cout << "Database main, for testing purposes only" << endl;

    DatabaseManager* dm = new DatabaseManager;

    Pet* pet = new Pet;
    pet->age = 2;
    pet->bio = "";
    pet->breed = "true";
    pet->color = "glue";
    pet->hypoallergenic = true;
    pet->image = "";
    pet->name = "myname";
    pet->sex = "male";
    pet->species = "epc";
    pet->weight = 2.0;
    dm->readInPets();
    cout << dm->findPet(1)->name << endl;
    cout << dm->findPet(2)->name << endl;
    dm->findPet(4)->name;
    cout << dm->findPet(5)->name << endl << endl;
    cout << dm->findPet(6)->name << endl << endl;
    cout << dm->findPet(12)->name << endl << endl;

    //cout << dm->isUsernameTaken("Glue") << endl << endl;
    vector<Adopter*> adopters = dm->findAdopterPet(1);
    for(Adopter* a : adopters) {
        cout << "User: " + a->username << endl;
    }
    cout << "User: " + dm->findAdopteePet(1)->username << endl << endl;

    vector<QString> vec = dm->messageParse("Kate: AHAHHHHHH|Glue: GIUDHGUIDGUI|Kate: SCREAMING|");
    for(QString i : vec) {
        cout << i.toStdString() << endl;
    }
}
