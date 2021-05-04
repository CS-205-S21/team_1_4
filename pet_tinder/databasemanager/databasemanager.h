#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QCoreApplication>
#include <QtSql>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>

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
struct Adopter {
    string username;
    vector<int> likedPetIds;
    vector<int> dislikedPetIds;

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
struct Adoptee {
    string username;
    string shelter;
    vector<int> ownedPetIds;
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
     * @brief DatabaseManager::readInusername;
    string likedPeAdopter - Finds adopter with matching username
     *  and password
     * @param username - Username of adopter to search for
     * @param password - Password of adopter to search for
     * @return Pointer to Pref struct of adopter's preferences and other info.
     *  If adopter is not found, a nullptr is returned.
     */
    Adopter* readInAdopter(string username, string password);

    /**
     * @brief DatabaseManager::readInAdoptee - Finds adoptee with matching username
     *  and password
     * @param username - Username of adoptee to search for
     * @param password - Password of adoptee to search for
     * @return Pointer to Pref struct of adoptee's information.
     *  If adoptee is not found, a nullptr is returned.
     */
    Adoptee* readInAdoptee(string username, string password);

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

    /**
     * @brief getNumAdopters - Finds number of registered adopters in the database
     * @return Number of adopters currently in database, returns -1 if search fails
     */
    int getNumAdopters();

    /**
     * @brief getNumAdoptees - Finds number of registered adoptees in the database
     * @return Number of adoptees currently in database, returns -1 if search fails
     */
    int getNumAdoptees();

    /**
     * @brief addPet - Adds a pet to the database of pets and to the vector of pets
     * @param p - the pet that will be added to the database
     * @return True or false depending on if the pet was successfully added.
     */
    bool addPet(Pet p);

    /**
     * @brief removePet - Removes a pet from the database of pets
     * @param p - the pet that will be removed from the database
     * @return True or false depending on if the pet was successfully removed.
     */
    bool removePet(int petId);

    /**
     * @brief addAdopter - Adds an adopter to the database of adopters, using the pref struct
     * @param p - the adopter (pref) that will be added to the database.
     * @return True or false depending on if the adopter was successfully added.
     */
    bool addAdopter(Adopter p, string password);

    /**
     * @brief removeAdopter - Removes an adopter from the database of adopters
     * @param p - the adopter that will be removed from the database
     * @return True or false depending on if the adopter was successfully removed.
     */
    bool removeAdopter(string username);

    /**
     * @brief addAdoptee - Adds an "adoptee" to the database of adoptees, using the adoptee info struct
     * @param p - the adoptee that will be added to the database.
     * @return True or false depending on if the adoptee was successfully added.
     */
    bool addAdoptee(Adoptee p, string password);

    /**
     * @brief removeAdoptee - Removes an adoptee from the database of adoptees
     * @param p - the adoptee that will be removed from the database
     * @return True or false depending on if the adoptee was successfully removed.
     */
    bool removeAdoptee(string username);

    /**
     * @brief stringToIntVector
     * @return
     */
    vector<int> stringToIntVector(string str);

    /**
     * @brief intVectorToQString
     * @return
     */
    QString intVectorToQString(vector<int> vec);
};

#endif // DATABASEMANAGER_H
