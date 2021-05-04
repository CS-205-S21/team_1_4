#include <iostream>
#include "databasemanager.h"

using namespace std;

int main() {
    DatabaseManager* dm = new DatabaseManager;
    dm->readInPets();
    cout << dm->findPet(0)->name << endl;
}
