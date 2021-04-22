#include "databasemanager.h"

DatabaseManager::DatabaseManager() {
    db.setDatabaseName(QString::fromStdString("./mydatabase.sqlite"));
}

/**
 * @brief PetsManager::readInPets - Reads in all pets from pet database
 */
void DatabaseManager::readInPets() {
    //Prepares a query that will read in all pets ordered by id.
    QSqlQuery query;
    query.prepare("SELECT id, name, species, breed, age, weight,"
                    "color, hypoallergenic, sex, bio FROM pet ORDER BY id;");

    if(query.exec()) {
        while(query.next()) {
            Pet pet;
            pet.id = query.value("id").toInt();
            pet.name = query.value("name").toString().toStdString();
            pet.species = query.value("species").toString().toStdString();
            pet.breed = query.value("breed").toString().toStdString();
            pet.age = query.value("age").toInt();
            pet.weight = query.value("weight").toDouble();
            pet.color = query.value("color").toString().toStdString();
            pet.hypoallergenic = query.value("hypoallergenic").toBool();
            pet.sex = query.value("sex").toString().toStdString();
            pet.bio = query.value("bio").toString().toStdString();

            pets.push_back(pet);
        }
    }
}

/**
 * @brief DatabaseManager::findPet - Finds pet with given id from vector
 * @param findId - Id of pet to search for
 * @return Pointer to Pet struct of pet's info. If no pet is found,
 *  returns a nullptr
 */
Pet* DatabaseManager::findPet(int findId) {
    if(pets.size() > 0) {
        cout << "Error: Vector is empty\n";
        return nullptr;
    }
    for(int i = 0; i < pets.size(); i++) {
        if(pets.at(i).id == findId) {
            return &pets.at(i);
        }
    }
    cout << "Error: Pet not found\n";
    return nullptr;
}

/**
 * @brief DatabaseManager::readInAdopter - Finds adopter with matching username
 *  and password
 * @param username - Username of adopter to search for
 * @param password - Password of adopter to search for
 * @return Pointer to Pref struct of adopter's preferences and other info.
 *  If adopter is not found, a nullptr is returned.
 */
Pref* DatabaseManager::readInAdopter(string username, string password) {
    QString qUsername;
    qUsername.fromStdString(username);
    QString qPassword;
    qPassword.fromStdString(password);

    QSqlQuery query;
    query.prepare("SELECT usernameAdopter, likedPetIds, dislikedPetIds,"
                  " prefSpecies, prefSpeciesReq, prefBreed, prefBreedReq,"
                  "prefAge, prefAgeReq, prefWeight, prefWeightReq,"
                  "prefColor, prefColorReq, prefHypoallergenic, prefHypoallergenicReq,"
                  "prefSex, prefSexReq FROM adopter"
                  "WHERE usernameAdopter = \"" + qUsername + "\" AND password = \"" + qPassword + "\";");

    if(query.exec()) {
        Pref pref;
        pref.username = query.value("usernameAdopter").toString().toStdString();
        pref.likedPetIds = query.value("likedPetIds").toString().toStdString();
        pref.dislikedPetIds = query.value("dislikedPetIds").toString().toStdString();
        pref.prefSpecies = query.value("prefSpecies").toString().toStdString();
        pref.prefSpeciesReq = query.value("prefSpeciesReq").toBool();
        pref.prefBreed = query.value("prefBreed").toString().toStdString();
        pref.prefBreedReq = query.value("prefBreedReq").toBool();
        pref.prefAge = query.value("prefBreed").toInt();
        pref.prefAgeReq = query.value("prefBreedReq").toBool();
        pref.prefWeight = query.value("prefWeight").toDouble();
        pref.prefWeightReq = query.value("prefWeightReq").toBool();
        pref.prefColor = query.value("prefColor").toString().toStdString();
        pref.prefColorReq = query.value("prefColorReq").toBool();
        pref.prefHypoallergenic = query.value("prefHypoallergenic").toBool();
        pref.prefHypoallergenicReq = query.value("prefHypoallergenicReq").toBool();
        pref.prefSex = query.value("prefSex").toString().toStdString();
        pref.prefSexReq = query.value("prefSexReq").toBool();

        cout << "Adopter: " + pref.username + "\n";

        return &pref;
    } else {
        cout << "Error: Adopter does not exist\n";
        return nullptr;
    }
}

/**
 * @brief DatabaseManager::readInAdoptee - Finds adoptee with matching username
 *  and password
 * @param username - Username of adoptee to search for
 * @param password - Password of adoptee to search for
 * @return Pointer to Pref struct of adoptee's information.
 *  If adoptee is not found, a nullptr is returned.
 */
AdopteeInfo* DatabaseManager::readInAdoptee(string username, string password) {
    QString qUsername;
    qUsername.fromStdString(username);
    QString qPassword;
    qPassword.fromStdString(password);

    QSqlQuery query;
    query.prepare("SELECT usernameAdoptee, group, petIds,"
                  "WHERE usernameAdoptee = \"" + qUsername + "\" AND password = \"" + qPassword + "\";");

    if(query.exec()) {
        AdopteeInfo info;
        info.username = query.value("usernameAdoptee").toString().toStdString();
        info.group = query.value("group").toString().toStdString();
        info.OwnedPetIds = query.value("petIds").toString().toStdString();

        cout << "Adoptee: " + info.username + info.group + info.OwnedPetIds + "\n";

        return &info;
    } else {
        cout << "Error: Adoptee does not exist\n";
        return nullptr;
    }
}

