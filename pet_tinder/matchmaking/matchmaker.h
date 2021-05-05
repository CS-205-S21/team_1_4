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
    Matchmaker();
    void innit();
    void sortPrefs();
    vector<Pet> DatabaseInterface(string username, string passwords);
    void refreshPetList();
     DatabaseManager *DM;
     Adopter *currentUser;
     vector<Pet> sortablePets;
     vector<int> discardedPetIds;
     vector<Pet> Queue;
     AllPrefs total;


















};

#endif // MATCHMAKER_H


