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
    cout << "User: " + dm->findAdopteePet(1)->username << endl;

    /*
    cout << "Message test: " << endl;
    vector<string> messageTest;
    messageTest = dm->messageParse("S:Hello my na:me is kate|R:Kate is a st:::upid name|S:Well that's rude"
                                   "|R:I'm sorry I was bullied as a child|R:But t::hat's a secret "
                                   "don't tell anyone.|S:Okey dokey artichokey");
    cout << "RETURNED VECTOR TEXT: " << endl;
    for(string i : messageTest) {
        cout << i << endl;
    }*/

}
