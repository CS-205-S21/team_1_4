#ifndef MATCHMAKER_H
#define MATCHMAKER_H
#include <string>
#include <iostream>
#include <stdlib.h>
#include "../databasemanager/databasemanager.h"

using namespace std;

class Matchmaker{
public:
    Matchmaker();
    //Matchmaker(bool hard,)
    void innit();
    int DatabaseInterface(string what, string whatTheUserWants);
     DatabaseManager *DM;




















};

#endif // MATCHMAKER_H
