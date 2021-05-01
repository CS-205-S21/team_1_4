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
    void make();
    int DatabaseInterface(string what, string whatTheUserWants);





















};

#endif // MATCHMAKER_H
