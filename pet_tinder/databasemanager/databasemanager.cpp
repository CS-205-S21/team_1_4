#include "databasemanager.h"

DatabaseManager::DatabaseManager() {
    db.setDatabaseName(QString::fromStdString("../../pet_tinder/database/mydatabase.sqlite"));
    if(!db.open()) {
        cerr << "Database does not open -- " << db.lastError().text().toStdString()
             << std::endl;
        exit(0);
    }
    petIdMax = 0;
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

            //Tracks pet ids, will hold highest current pet id by end of while loop
            if(pet.id > (int)petIdMax) {
                petIdMax = pet.id;
            }

            pets.push_back(pet); //Adds pet struct to pets vector
        }
    }
}

//Reads in adopter from database with given username and password
Adopter* DatabaseManager::readInAdopter(string username, string password) {
    //Prepares username and password for use in query
    QString qUsername = QString::fromStdString(username);
    QString qPassword = QString::fromStdString(password);

    //Prepares a query that will read in all pets ordered by id.
    QSqlQuery query;
    query.prepare("SELECT usernameAdopter, likedPetIds, dislikedPetIds, "
                  "prefSpecies, prefSpeciesReq, prefBreed, prefBreedReq, "
                  "prefAge, prefAgeReq, prefWeight, prefWeightReq, "
                  "prefColor, prefColorReq, prefHypoallergenic, prefHypoallergenicReq, "
                  "prefSex, prefSexReq FROM adopter "
                  "WHERE usernameAdopter = '" + qUsername + "' AND password = '" + qUsername + "';");

    if(query.exec()) {
        //Creates and fills adopter struct
        Adopter *adopter = new Adopter;
        adopter->username = query.value("usernameAdopter").toString().toStdString();
        adopter->likedPetIds = stringToIntVector(query.value("likedPetIds").toString().toStdString());
        adopter->dislikedPetIds = stringToIntVector(query.value("dislikedPetIds").toString().toStdString());

        adopter->prefSpecies = query.value("prefSpecies").toString().toStdString();
        adopter->prefSpeciesReq = query.value("prefSpeciesReq").toBool();
        adopter->prefBreed = query.value("prefBreed").toString().toStdString();
        adopter->prefBreedReq = query.value("prefBreedReq").toBool();
        adopter->prefAge = query.value("prefBreed").toInt();
        adopter->prefAgeReq = query.value("prefBreedReq").toBool();
        adopter->prefWeight = query.value("prefWeight").toDouble();
        adopter->prefWeightReq = query.value("prefWeightReq").toBool();
        adopter->prefColor = query.value("prefColor").toString().toStdString();
        adopter->prefColorReq = query.value("prefColorReq").toBool();
        adopter->prefHypoallergenic = query.value("prefHypoallergenic").toBool();
        adopter->prefHypoallergenicReq = query.value("prefHypoallergenicReq").toBool();
        adopter->prefSex = query.value("prefSex").toString().toStdString();
        adopter->prefSexReq = query.value("prefSexReq").toBool();

        cout << "Adopter: " + adopter->username + "\n";

        return adopter; //Returns adopter struct
    } else {
        cout << "Error: Adopter does not exist\n";
        return nullptr;
    }
}

Adoptee* DatabaseManager::readInAdoptee(string username, string password) {
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
        Adoptee *adoptee = new Adoptee;
        adoptee->username = query.value("usernameAdoptee").toString().toStdString();
        adoptee->shelter = query.value("shelter").toString().toStdString();
        adoptee->ownedPetIds = stringToIntVector(query.value("petIds").toString().toStdString());

        return adoptee; //Returns adoptee struct
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
    for(int i = 0; i < (int)pets.size(); i++) {
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
int DatabaseManager::getNumAdopters() {
    //Prepares a query to run in Sql
    //Finds number of unique usernames in the adopter database
    QSqlQuery query;
    query.prepare("SELECT COUNT(usernameAdopter) FROM adopter;");

    if(query.exec()) {
        //Returns value found
        return query.value(0).toInt();
    }
    cout << "Error: Cannot find number of adopters, you really screwed the pooch on this one\n";
    return -1;
}

//Finds number of registered adoptees in the database
int DatabaseManager::getNumAdoptees() {
    //Prepares a query to run in Sql
    //Finds number of unique usernames in the adoptee database
    QSqlQuery query;
    query.prepare("SELECT COUNT(usernameAdoptee) FROM adoptee;");

    if(query.exec()) {
        //Returns value found
        return query.value(0).toInt();
    }
    cout << "Error: Cannot find number of adoptees, you really screwed the pooch on this one\n";
    return -1;
}

//Adds a pet to the database of pets and to the vector pf pets
bool DatabaseManager::addPet(Pet pet) {
    petIdMax++;
    pet.id = petIdMax; //Sets given pet's id to max id + 1
    //cout << pet.id << std::endl;

    //Tests for bad data
    if(pet.age <= 0 || pet.weight <= 0) {
        return false;
    }

    //Prepares a query that inserts all pet info from pet struct
    QSqlQuery q;
        q.prepare("INSERT INTO pet (petId, name, species, breed,"
                  "age, weight, color, hypoallergenic, sex, bio)"
                  "VALUES (:petId, :name, :species, :breed, :age,"
                  ":weight, :color, :hypoallergenic, :sex, :bio)");
        q.bindValue(":petId", pet.id);
        QString name = QString::fromStdString(pet.name);
        q.bindValue(":name", name);
        QString species = QString::fromStdString(pet.species);
        q.bindValue(":species", species);
        QString breed = QString::fromStdString(pet.breed);
        q.bindValue(":breed", breed);
        q.bindValue(":age", pet.age);
        q.bindValue(":weight", pet.weight);
        QString color = QString::fromStdString(pet.color);
        q.bindValue(":color", color);
        q.bindValue(":hypoallergenic", pet.hypoallergenic);
        QString sex = QString::fromStdString(pet.sex);
        q.bindValue(":sex", sex);
        QString bio = QString::fromStdString(pet.bio);
        q.bindValue(":bio", bio);
    if(q.exec()){
        pets.push_back(pet); //Adds pet struct to pets vector
        return true;
    } else {
        qDebug() << "Add Pet Error" << q.lastError();
        return false;
    }
}

//Removes a pet from the database of pets
bool DatabaseManager::removePet(int petId) {
    QString qPetId = "" + petId;

    QSqlQuery q;
    q.prepare("DELETE FROM pet WHERE petId = \"" + qPetId + "\";");

    if(q.exec()) {
        //Searches through pets vector to find pet with given id
        for(int i = 0; i < (int)pets.size(); i++) {
            //When pet with matching id is found, return it
            if(pets.at(i).id == petId) {
                pets.erase(pets.begin() + i);
                return true;
            }
        }
    }
    return false;
}

//Adds an adopter to the database of adopters, using the pref struct
bool DatabaseManager::addAdopter(Adopter a, string password) {
    //Prepares a query that inserts given adopter
    QSqlQuery q;
        q.prepare("INSERT INTO adopter (usernameAdopter, password,"
                  "likedPetIds, dislikedPetIds,"
                  "prefSpecies, prefSpeciesReq,"
                  "prefBreed, prefBreedReq, prefAge, prefAgeReq"
                  "prefWeight, prefWeightReq, prefColor, prefColorReq"
                  "prefHypoallergenic, prefHypoallergenicReq,"
                  "prefSex, prefSexReq)"
                  "VALUES :usernameAdopter, :password,"
                  ":likedPetIds, :dislikedPetIds,"
                  ":prefSpecies, :prefSpeciesReq,"
                  ":prefBreed, :prefBreedReq, :prefAge, :prefAgeReq"
                  ":prefWeight, :prefWeightReq, :prefColor, :prefColorReq"
                  ":prefHypoallergenic, :prefHypoallergenicReq,"
                  ":prefSex, :prefSexReq)");
        QString username = QString::fromStdString(a.username);
        q.bindValue(":usernameAdopter", username);
        QString qPassword = QString::fromStdString(password);
        q.bindValue(":password", qPassword);
        q.bindValue(":likedPetIds", intVectorToQString(a.likedPetIds));
        q.bindValue(":dislikedPetIds", intVectorToQString(a.dislikedPetIds));
        QString prefSpecies = QString::fromStdString(a.prefSpecies);
        q.bindValue(":prefSpecies", prefSpecies);
        q.bindValue(":prefSpeciesReq", a.prefSpeciesReq);
        QString prefBreed = QString::fromStdString(a.prefBreed);
        q.bindValue(":prefBreed", prefBreed);
        q.bindValue(":prefBreedReq", a.prefBreedReq);
        q.bindValue(":prefAge", a.prefAge);
        q.bindValue(":prefAgeReq", a.prefAgeReq);
        q.bindValue(":prefWeight", a.prefWeight);
        q.bindValue(":prefWeightReq", a.prefWeightReq);
        QString prefColor = QString::fromStdString(a.prefColor);
        q.bindValue(":prefColor", prefColor);
        q.bindValue(":prefColorReq", a.prefColorReq);
        q.bindValue(":prefHypoallergenic", a.prefHypoallergenic);
        q.bindValue(":prefHypoallergenicReq", a.prefHypoallergenicReq);
        QString prefSex = QString::fromStdString(a.prefSex);
        q.bindValue(":prefSex", prefSex);
        q.bindValue(":prefSexReq", a.prefSexReq);
    if(q.exec()) {
        return true;
    } else {
        qDebug() << "Add Pet Error" << q.lastError();
        return false;
    }
}

//Removes an adopter from the database of adopters
bool DatabaseManager::removeAdopter(string username) {
    QString qUsername;
    qUsername.fromStdString(username);

    QSqlQuery q;
    q.prepare("DELETE FROM adopter WHERE usernameAdopter = \"" + qUsername + "\";");

    if(q.exec()) {
        return true;
    }
    return false;
}

//Adds an "adoptee" to the database of adoptees, using the adoptee info struct
bool DatabaseManager::addAdoptee(Adoptee a, string password) {
    //Prepares a query that inserts given adoptee
    QSqlQuery q;
        q.prepare("INSERT INTO adoptee (usernameAdoptee, password, shelter, petIds)"
                  "VALUES (:usernameAdoptee, :password, :shelter, :petIds);");
        QString username = QString::fromStdString(a.username);
        q.bindValue(":usernameAdopter", username);
        QString qPassword = QString::fromStdString(password);
        q.bindValue(":password", qPassword);
        QString shelter = QString::fromStdString(a.shelter);
        q.bindValue(":shelter", shelter);
        q.bindValue(":petIds", intVectorToQString(a.ownedPetIds));
    if(q.exec()) {
        return true;
    }
    return false;
}

//Removes an adoptee from the database of adoptees
bool DatabaseManager::removeAdoptee(string username) {
    QString qUsername;
    qUsername.fromStdString(username);

    QSqlQuery q;
    q.prepare("DELETE FROM adoptee WHERE usernameAdoptee = \"" + qUsername + "\";");

    if(q.exec()) {
        return true;
    }
    return false;
}

//Takes a string of ints split by ' ' characters and builds it into a vector
vector<int> DatabaseManager::stringToIntVector(string str) {
    //char c[s.size() + 1];
    //strcpy(c, s.c_str());

    vector<int> vector;

    //Create stream of str string
    istringstream stream(str);
    int num;
    //Pushes ints into num variable, split by ' ' character
    while(stream >> num) {
         vector.push_back(num);
    }
    return vector;
}

//Takes an int vector and creates a QString out of its ints, seperated by ' ' characters
QString DatabaseManager::intVectorToQString(vector<int> vec) {
    QString str;

    str += str.fromStdString(to_string(vec.front()));
    for(int i = 1; i < (int)vec.size(); i++) {
        str += " " + str.fromStdString(to_string(vec.at(i)));
    }
    return str;
}

int DatabaseManager::getPetIdMax() {
    return petIdMax;
}
