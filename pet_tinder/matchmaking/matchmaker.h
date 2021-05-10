#ifndef MATCHMAKER_H
#define MATCHMAKER_H
#include <string>
#include <iostream>
#include <stdlib.h>
#include "../databasemanager/databasemanager.h"
#include <vector>

using namespace std;

struct AllPrefs {
    vector<string> species;
    vector<string> breeds;
    vector<int> ages;
    vector<double> weights;
    vector<string> colors;

};

class Matchmaker{
public:
    /**
     * @brief Matchmaker- Sets up database
     */
    Matchmaker();

    /**
     * @brief innit- Reads in Pets and calls the sortPrefs
     */
    void innit();

    /**
     * @brief sortPrefs- sorts all available preferencs for use in
     * comboboxes
     */
    void sortPrefs();

    /**
     * @brief DatabaseInterface- interfaces with the database to sort viable
     * pets for the user
     * @param username- given by GUI passed to databasemanager
     * @param passwords- given by GUI passed to databasemanager
     * @return Returns a vector of pets that is ready to be shown at the GUI
     */
    vector<Pet> DatabaseInterface(string username, string passwords);

    /**
     * @brief refreshPetList- Sorts pets into discarded and sortable pets
     * based on whether they have been disliked/liked or not interfaced
     * with yet
     */
    void refreshPetList();

    /**
     * @brief arrangePrefs- arranages available user preferences
     * alphabetically
     */
    void arrangePrefs();

    DatabaseManager *DM;
    Adopter *currentUser;
    vector<Pet> sortablePets;
    vector<int> discardedPetIds;
    vector<Pet> Queue;
    AllPrefs total;
};

#endif // MATCHMAKER_H
