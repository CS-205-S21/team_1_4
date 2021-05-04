#ifndef MATCHMAKER_H
#define MATCHMAKER_H
#include <string>
#include <iostream>
#include <stdlib.h>
#include "../databasemanager/databasemanager.h"
#include <vector>
using namespace std;

class Matchmaker{
public:
    Matchmaker();
    void innit();
    vector<Pet> DatabaseInterface(string username, string passwords);
    void refreshPetList();
     DatabaseManager *DM;
     Adopter *currentUser;
     vector<Pet> sortablePets;
     vector<int> discardedPetIds;
     vector<Pet> Queue;



















};

#endif // MATCHMAKER_H


