#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QCoreApplication>
#include <QtSql>
#include <string>
#include <iostream>

using namespace std;

struct Pet {
    int id;
    string name;
    string species;
    string breed;
    int age;
    double weight;
    string color;
    bool hypoallergenic;
    string sex;
    string bio;
};
struct Pref {
    string username;
    string likedPetIds;
    string dislikedPetIds;

    string prefSpecies;
    bool prefSpeciesReq;
    string prefBreed;
    bool prefBreedReq;
    int prefAge;
    bool prefAgeReq;
    double prefWeight;
    bool prefWeightReq;
    string prefColor;
    bool prefColorReq;
    bool prefHypoallergenic;
    bool prefHypoallergenicReq;
    string prefSex;
    bool prefSexReq;
};
struct AdopteeInfo {
    string username;
    string group;
    string OwnedPetIds;
};

class DatabaseManager
{
public:
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    //Vector which holds all current pets. Ordered by id, but with possible gaps
    vector<Pet> pets;

    //Current highest pet id. Maximum value of 18,446,744,073,709,551,615
    unsigned long long int maxId;

    DatabaseManager();

    void readInPets();
    Pet* findPet(int id);
    Pref* readInAdopter(string username, string password);
    AdopteeInfo* readInAdoptee(string username, string password);
};

#endif // DATABASEMANAGER_H
