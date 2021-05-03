#include "databasemanager.h"

DatabaseManager::DatabaseManager() {
    db.setDatabaseName(QString::fromStdString("./mydatabase.sqlite"));
    if(!db.open()) {
        cerr << "Database does not open -- " << db.lastError().text().toStdString()
             << std::endl;
        exit(0);
    }
}

//Reads in all pets from database
void DatabaseManager::readInPets() {
    //Prepares a query that will read in all pets ordered by id.
    QSqlQuery query;
    query.prepare("SELECT petId, name, species, breed, age, weight,"
                    "color, hypoallergenic, sex, bio FROM pet ORDER BY petId;");

    if(query.exec()) {
        while(query.next()) {
            //Creates and fills pet struct
            Pet pet;
            pet.id = query.value("petId").toInt();
            pet.name = query.value("name").toString().toStdString();
            pet.species = query.value("species").toString().toStdString();
            pet.breed = query.value("breed").toString().toStdString();
            pet.age = query.value("age").toInt();
            pet.weight = query.value("weight").toDouble();
            pet.color = query.value("color").toString().toStdString();
            pet.hypoallergenic = query.value("hypoallergenic").toBool();
            pet.sex = query.value("sex").toString().toStdString();
            pet.bio = query.value("bio").toString().toStdString();

            pets.push_back(pet); //Adds pet struct to pets vector
        }
    }
}

//Reads in adopter from database with given username and password
Pref* DatabaseManager::readInAdopter(string username, string password) {
    //Prepares username and password for use in query
    QString qUsername;
    qUsername.fromStdString(username);
    QString qPassword;
    qPassword.fromStdString(password);

    //Prepares a query that will read in all pets ordered by id.
    QSqlQuery query;
    query.prepare("SELECT usernameAdopter, likedPetIds, dislikedPetIds,"
                  " prefSpecies, prefSpeciesReq, prefBreed, prefBreedReq,"
                  "prefAge, prefAgeReq, prefWeight, prefWeightReq,"
                  "prefColor, prefColorReq, prefHypoallergenic, prefHypoallergenicReq,"
                  "prefSex, prefSexReq FROM adopter"
                  "WHERE usernameAdopter = \"" + qUsername + "\" AND password = \"" + qPassword + "\";");

    if(query.exec()) {
        //Creates and fills pref struct
        Pref *pref;
        pref->username = query.value("usernameAdopter").toString().toStdString();
        pref->likedPetIds = query.value("likedPetIds").toString().toStdString();
        pref->dislikedPetIds = query.value("dislikedPetIds").toString().toStdString();

        pref->prefSpecies = query.value("prefSpecies").toString().toStdString();
        pref->prefSpeciesReq = query.value("prefSpeciesReq").toBool();
        pref->prefBreed = query.value("prefBreed").toString().toStdString();
        pref->prefBreedReq = query.value("prefBreedReq").toBool();
        pref->prefAge = query.value("prefBreed").toInt();
        pref->prefAgeReq = query.value("prefBreedReq").toBool();
        pref->prefWeight = query.value("prefWeight").toDouble();
        pref->prefWeightReq = query.value("prefWeightReq").toBool();
        pref->prefColor = query.value("prefColor").toString().toStdString();
        pref->prefColorReq = query.value("prefColorReq").toBool();
        pref->prefHypoallergenic = query.value("prefHypoallergenic").toBool();
        pref->prefHypoallergenicReq = query.value("prefHypoallergenicReq").toBool();
        pref->prefSex = query.value("prefSex").toString().toStdString();
        pref->prefSexReq = query.value("prefSexReq").toBool();

        cout << "Adopter: " + pref->username + "\n";

        return pref; //Returns pref struct
    } else {
        cout << "Error: Adopter does not exist\n";
        return nullptr;
    }
}

AdopteeInfo* DatabaseManager::readInAdoptee(string username, string password) {
    //Prepares username and password for use in query
    QString qUsername;
    qUsername.fromStdString(username);
    QString qPassword;
    qPassword.fromStdString(password);

    //Prepares a query that will read in all pets ordered by id.
    QSqlQuery query;
    query.prepare("SELECT usernameAdoptee, group, petIds,"
                  "WHERE usernameAdoptee = \"" + qUsername + "\" AND password = \"" + qPassword + "\";");

    if(query.exec()) {
        //Creates and fills info struct
        AdopteeInfo *info;
        info->username = query.value("usernameAdoptee").toString().toStdString();
        info->group = query.value("group").toString().toStdString();
        info->OwnedPetIds = query.value("petIds").toString().toStdString();

        cout << "Adoptee: " + info->username + info->group + info->OwnedPetIds + "\n";

        return info; //Returns info struct
    } else {
        cout << "Error: Adoptee does not exist\n";
        return nullptr;
    }
}

//Finds pet with given id
Pet* DatabaseManager::findPet(int findId) {
    //If pets vector isn't empty...
    if(pets.size() <= 0) {
        cout << "Error: Vector is empty\n";
        return nullptr;
    }
    //Searches through pets vector to find pet with given id
    for(int i = 0; i < pets.size(); i++) {
        //When pet with matching id is found, return it
        if(pets.at(i).id == findId) {
            return &pets.at(i);
        }
    }
    cout << "Error: Pet not found\n";
    return nullptr;
}

//Returns number of pets in pets vector
int DatabaseManager::getNumPets() {
    return pets.size();
}

//Finds number of registered adopters in the database
int DatabaseManager::getNumAdopters(){
    return -1;
}

//Finds number of registered adoptees in the database
int DatabaseManager::getNumAdoptees(){
    return -1;
}

//Adds a pet to the database of pets and to the vector pf pets
bool DatabaseManager::addPet(Pet p){
    return false;
}

//Removes a pet from the database of pets
bool DatabaseManager::removePet(Pet p){
    return false;
}

//Adds an adopter to the database of adopters, using the pref struct
bool DatabaseManager::addAdopter(Pref p){
    return false;
}

//Removes an adopter from the database of adopters
bool DatabaseManager::removeAdopter(Pref p){
    return false;
}

//Adds an "adoptee" to the database of adoptees, using the adoptee info struct
bool DatabaseManager::addAdoptee(AdopteeInfo p){
    return false;
}

//Removes an adoptee from the database of adoptees
bool DatabaseManager::removeAdoptee(AdopteeInfo p){
    return false;
}
