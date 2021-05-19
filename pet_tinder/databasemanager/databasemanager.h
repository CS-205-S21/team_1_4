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
    int hypoallergenic;
    string sex;
    string bio;
    QByteArray image;
};
struct Adopter {
    string username;            //PUBLIC
    vector<int> likedPetIds;
    vector<int> dislikedPetIds;
    string bio;                 //PUBLIC

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
    int prefHypoallergenic;
    bool prefHypoallergenicReq;
    string prefSex;
    bool prefSexReq;
};
struct Adoptee {
    string username;         //PUBLIC
    string shelter;          //PUBLIC
    vector<int> ownedPetIds;
    string bio;              //PUBLIC
};
struct Conversation {
    string usernameAdopter;
    int petId;
    string usernameAdoptee;
    vector<QString> messages;
};

class DatabaseManager
{
public:
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    //Vector which holds all current pets. Ordered by id, but with possible gaps
    vector<Pet*> pets;

    DatabaseManager();
    ~DatabaseManager();

    /**
     * @brief PetsManager::readInPets - Reads in all pets from pet database
     *  Should only be read in once near beggining of run
     */
    void readInPets();

    /**
     * @brief DatabaseManager::readInAdopter - Reads in adopter from adopter database
     *  with matching username and password
     * @param username - Username of adopter to search for
     * @param password - Password of adopter to search for
     * @return Pointer to Pref struct of adopter's preferences and other info.
     *  If adopter is not found, a nullptr is returned.
     */
    Adopter* readInAdopter(string username, string password);
    
    /**
     * @brief DatabaseManager::readInAdopterPublic - Reads in public adopter
     *  info from database with matching username
     * @param username - Username of adopter to search for
     * @return Pointer to Pref struct of adopter's public info only.
     *  If adopter is not found, a nullptr is returned.
     */
    Adopter* readInAdopterPublic(string username);

    /**
     * @brief DatabaseManager::readInAdoptee - Reads in adoptee from adopter database
     *  with matching username and password
     * @param username - Username of adoptee to search for
     * @param password - Password of adoptee to search for
     * @return Pointer to Pref struct of adoptee's information.
     *  If adoptee is not found, a nullptr is returned.
     */
    Adoptee* readInAdoptee(string username, string password);
    
    /**
     * @brief DatabaseManager::readInAdopteePublic - Reads in public adoptee
     *  info from database with matching username
     * @param username - Username of adoptee to search for
     * @return Pointer to Pref struct of adoptee's public info only.
     *  If adoptee is not found, a nullptr is returned.
     */
    Adoptee* readInAdopteePublic(string username);

    /**
     * @brief DatabaseManager::readInMessages - Reads in conversation from
     *  messages database with adopter's username and the id
     *  of the pet they liked to begin the conversation
     * @param usernameAdopter - Username of adopter involved
     * @param petId - id of pet adopter had liked
     * @return Pointer to Conversation struct of conversation info.
     *  If conversation is not found, a nullptr is returned.
     */
    Conversation* readInConversation(string usernameAdopter, int petId);

    /**
     * @brief checkUsernames - Checks given username against usernames
     *  of all adopters and adoptees
     * @param username - Username to check for
     * @return bool - true if username is taken, false otherwise
     */
    bool isUsernameTaken(string username);

    /**
     * @brief findAdopterPet - Finds all adopters who have liked the pet
     *  with the given id
     * @param id - id for pet to look for among adopters' liked pets lists
     * @return vector<Adopter*> - a vector containing adopter structs
     *  for all adopters who liked this pet. Will return an empty
     *  vector if no adopters liked this pet or if the code otherwise fails.
     */
    vector<Adopter*> findAdopterPet(int id);

    /**
     * @brief findAdopteePet - Finds adoptee who has owned pet with given id
     * @param id - id for pet to look for among adoptees
     * @return Adoptee - struct of adoptee's info or nullptr
     *  if no adopter was found (though that shouldn't happen)
     */
    Adoptee* findAdopteePet(int id);

    /**
     * @brief DatabaseManager::findPet - Finds pet with given id from vector
     * @param findId - Id of pet to search for
     * @return Pet* - Pointer to Pet struct of pet's info. If no pet is found,
     *  returns a nullptr
     */
    Pet* findPet(int id);

    /**
     * @brief getNumPets - Finds number of pets
     * @return int - Number of pets currently in Pets vector
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
     * @param p - The pet that will be added to the database
     * @return True or false depending on if the pet was successfully added.
     */
    bool addPet(Pet* p);

    /**
     * @brief updatePet - Updates pet with given information
     * @param pet - Struct of info to update pet with
     * @return bool - True if pet successfully updated
     */
    bool updatePet(Pet* pet);

    /**
     * @brief addPet - Adds a pet to the database of pets and to the vector of pets
     * @param id - id of pet you're trying to remove
     * @return True or false depending on if the pet was successfully added.
     */
    bool removePet(int id);

    /**
     * @brief addAdopter - Adds an adopter to the database of adopters, using the pref struct
     * @param p - the adopter (pref) that will be added to the database.
     * @param password - password of adopter to add to the database
     * @return  bool - True or false depending on if the adopter was successfully added.
     */
    bool addAdopter(Adopter* p, string password);

    /**
     * @brief updateAdopter - Updates adopter with given struct of info
     * @param adopter - Adopter to find & update
     * @return bool - True if updated successfully
     */
    bool updateAdopter(Adopter* adopter);

    /**
     * @brief removeAdopter - Removes an adopter from the database of adopters
     * @param username - username of adopter you're trying to remove
     * @return bool - True or false depending on if the adopter was successfully removed.
     */
    bool removeAdopter(string username);

    /**
     * @brief addAdoptee - Adds an "adoptee" to the database of adoptees, using the adoptee info struct
     * @param p - the adoptee that will be added to the database.
     * @param password - password of adoptee to add to the database
     * @return bool - True or false depending on if the adoptee was successfully added.
     */
    bool addAdoptee(Adoptee* p, string password);

    /**
     * @brief updateAdoptee - Updates adoptee with given struct of info
     * @param adoptee - Adoptee to find & update
     * @return bool - True if updated successfully
     */
    bool updateAdoptee(Adoptee* adoptee);

    /**
     * @brief removeAdoptee - Removes an adoptee from the database of adoptees
     * @param username - username of adoptee you're trying to remove
     * @return bool - True or false depending on if the adoptee was successfully removed.
     */
    bool removeAdoptee(string username);

    /**
     * @brief addConversation - Adds a conversation to the database of conversations
     *  using the conversation struct
     * @param convo - Conversation struct
     * @return bool - Whether or not conversation was succesfully added
     */
    bool addConversation(Conversation* convo);

    /**
     * @brief updateConversation - Updates conversation with given struct of info
     * @param convo - Conversation to find & update
     * @return bool - True if updated successfully
     */
    bool updateConversation(Conversation* convo);

    /**
     * @brief removeConversation - Removes found conversation from database
     * @param usernameAdopter - Username of adopter involved in conversation
     * @param petId - id of pet involved in conversation
     * @return bool - Whether or not conversation was succesfully deleted
     */
    bool removeConversation(string usernameAdopter, int petId);

    /**
     * @brief stringToIntVector - Turns a string of ints seperated by ' ' characters
     *  into a vector of those ints
     * @param str - String to make into a vector. Must contain only integers seperated
     *  by single ' ' characters, e.g. "1 3 5 12 543"
     * @return vector<int> - Vector of ints from the passed string
     */
    vector<int> stringToIntVector(string str);

    /**
     * @brief intVectorToQString - Takes a vector of ints and converts it to
     *  a QString of numbers seperated by ' ' characters
     * @param vec - Vector of integers
     * @return QString - QString of numbers seperated by ' ' characters,
     *  e.g. "1 3 5 12 543". If a standard string is desired instead, use the
     *  QString's .toStdString function on the return value.
     */
    QString intVectorToQString(vector<int> vec);

    /**
     * @brief messageParse - Parses user message strings into a vector
     *  of seperated messages
     * @param message - A string holding all messages between the user
     *  and one other, formatted ONLY like:
     *  "senderName:Sender's message|otherSenderName:Other sender's message|", etc.
     *  Typically only used on message strings read in straight from the database
     * @return vector<QString> - A vector of individual messages, with
     *  sender's name attached to the front of each message of the
     */
    vector<QString> messageParse(string message);

    /**
     * @brief messageUnparse - Turns a vector of QStrings into a single QString
     *  seperated by '|' characters
     * @param message - A vector of QStrings
     * @return QString - Single QString of QStrings from vector
     */
    QString messageUnparse(vector<QString> message);

    /**
     * @brief getPetIdMax - Getter method for petIdMax
     * @return int - petIdMax
     */
    int getPetIdMax();

private:
    //Tracks the maximum pet id, given to new pets to avoid repeat ids
    //Maximum value of 18,446,744,073,709,551,615
    unsigned long long int petIdMax;
};

#endif // DATABASEMANAGER_H
