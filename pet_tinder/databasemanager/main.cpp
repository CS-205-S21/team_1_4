#include <iostream>
#include "databasemanager.h"

using namespace std;

int main() {
    DatabaseManager* dm = new DatabaseManager;
    dm->readInPets();
    cout << dm->findPet(1)->name << endl;
    cout << dm->findPet(2)->name << endl;
    dm->findPet(4)->name;
    cout << dm->findPet(5)->name << endl;

    dm->messageParse("S:Hello my is kate|R:Go fuck yourself|S:Well that's rude|R:Well suck my dick and call me sally");
}
