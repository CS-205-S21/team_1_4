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

    cout << "Message test: " << endl;
    vector<string> messageTest;
    messageTest = dm->messageParse("S:Hello my name is kate|R:Kate is a stupid name|S:Well that's rude"
                                   "|R:I'm sorry I was bullied as a child|R:But that's a secret "
                                   "don't tell anyone.|S:Okey dokey artichokey|");
    cout << "Returned vector text: " << endl;
    for(string i : messageTest) {
        cout << i << endl;
    }
}
