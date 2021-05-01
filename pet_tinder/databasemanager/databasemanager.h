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

    /**
     * @brief PetsManager::readInPets - Reads in all pets from pet database
     */
    void readInPets();

    /**
     * @brief DatabaseManager::readInAdopter - Finds adopter with matching username
     *  and password
     * @param username - Username of adopter to search for
     * @param password - Password of adopter to search for
     * @return Pointer to Pref struct of adopter's preferences and other info.
     *  If adopter is not found, a nullptr is returned.
     */
    Pref* readInAdopter(string username, string password);

    /**
     * @brief DatabaseManager::readInAdoptee - Finds adoptee with matching username
     *  and password
     * @param username - Username of adoptee to search for
     * @param password - Password of adoptee to search for
     * @return Pointer to Pref struct of adoptee's information.
     *  If adoptee is not found, a nullptr is returned.
     */
    AdopteeInfo* readInAdoptee(string username, string password);

    /**
     * @brief DatabaseManager::findPet - Finds pet with given id from vector
     * @param findId - Id of pet to search for
     * @return Pointer to Pet struct of pet's info. If no pet is found,
     *  returns a nullptr
     */
    Pet* findPet(int id);

    /**
     * @brief getNumPets - Finds number of pets
     * @return Number of pets currently in Pets vector
     */
    int getNumPets();
};

#endif // DATABASEMANAGER_H
