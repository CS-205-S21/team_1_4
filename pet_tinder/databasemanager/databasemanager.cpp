#include "databasemanager.h"

DatabaseManager::DatabaseManager() {
    db.setDatabaseName(QString::fromStdString("../../pet_tinder/database/mydatabase.sqlite"));
    if(!db.open()) {
        cerr << "Database does not open -- " << db.lastError().text().toStdString()
             << std::endl;
        exit(0);
    }
    petIdMax = 0;
    readInPets();
}

DatabaseManager::~DatabaseManager(){
    pets.clear();
    db.close();
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
            Pet *pet = new Pet;
            pet->id = query.value("petId").toInt();
            pet->name = query.value("name").toString().toStdString();
            pet->species = query.value("species").toString().toStdString();
            pet->breed = query.value("breed").toString().toStdString();
            pet->age = query.value("age").toInt();
            pet->weight = query.value("weight").toDouble();
            pet->color = query.value("color").toString().toStdString();
            pet->hypoallergenic = query.value("hypoallergenic").toBool();
            pet->sex = query.value("sex").toString().toStdString();
            pet->bio = query.value("bio").toString().toStdString();

            //Tracks pet ids, will hold highest current pet id by end of while loop
            if(pet->id > (int)petIdMax) {
                petIdMax = pet->id;
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

    bool exists = false;
    QSqlQuery sel;
    sel.prepare("SELECT usernameAdopter, password FROM adopter WHERE usernameAdopter = (:un) AND password = (:pw);");
    QString qUn = QString::fromStdString(username);
    sel.bindValue(":un", qUn);
    QString qPw = QString::fromStdString(password);
    sel.bindValue(":pw", qPw);
    if(sel.exec()){
        if(sel.next()){
            exists = true;
        }
    }

    //Prepares a query that will read in all pets ordered by id.
    QSqlQuery query;
    query.prepare("SELECT usernameAdopter, likedPetIds, dislikedPetIds, "
                  "prefSpecies, prefSpeciesReq, prefBreed, prefBreedReq, "
                  "prefAge, prefAgeReq, prefWeight, prefWeightReq, "
                  "prefColor, prefColorReq, prefHypoallergenic, prefHypoallergenicReq, "
                  "prefSex, prefSexReq FROM adopter "
                  "WHERE usernameAdopter = (:username) AND password = (:password);");
    query.bindValue(":username", qUsername);
    query.bindValue(":password", qPassword);
    if(query.exec() && exists) {
        //Creates and fills adopter struct
        query.next();
        Adopter *adopter = new Adopter;
        adopter->username = query.value("usernameAdopter").toString().toStdString();
        adopter->likedPetIds = stringToIntVector(query.value("likedPetIds").toString().toStdString());
        adopter->dislikedPetIds = stringToIntVector(query.value("dislikedPetIds").toString().toStdString());
        adopter->prefSpecies = query.value("prefSpecies").toString().toStdString();
        adopter->prefSpeciesReq = query.value("prefSpeciesReq").toInt();
        adopter->prefBreed = query.value("prefBreed").toString().toStdString();
        adopter->prefBreedReq = query.value("prefBreedReq").toInt();
        adopter->prefAge = query.value("prefBreed").toInt();
        adopter->prefAgeReq = query.value("prefBreedReq").toInt();
        adopter->prefWeight = query.value("prefWeight").toDouble();
        adopter->prefWeightReq = query.value("prefWeightReq").toInt();
        adopter->prefColor = query.value("prefColor").toString().toStdString();
        adopter->prefColorReq = query.value("prefColorReq").toInt();
        adopter->prefHypoallergenic = query.value("prefHypoallergenic").toInt();
        adopter->prefHypoallergenicReq = query.value("prefHypoallergenicReq").toInt();
        adopter->prefSex = query.value("prefSex").toString().toStdString();
        adopter->prefSexReq = query.value("prefSexReq").toInt();

        return adopter; //Returns adopter struct
    } else if(!exists){
        qDebug() << "Adopter cannot be found using Select" << endl;
        return nullptr;
    } else {
        cout << "Error: Issue with the Query\n";
        return nullptr;
    }
}

//WARNING: THIS DOES NOT WORK
Adoptee* DatabaseManager::readInAdoptee(string username, string password) {
    //Prepares username and password for use in query
    QString qUsername = QString::fromStdString(username);
    QString qPassword = QString::fromStdString(password);

    bool exists = false;
    QSqlQuery sel;
    sel.prepare("SELECT usernameAdoptee FROM adoptee WHERE usernameAdoptee = (:un);");
    QString qUn = QString::fromStdString(username);
    sel.bindValue(":un", qUn);
    if(sel.exec()){
        if(sel.next()){
            exists = true;
        }
    }

    //Prepares a query that will read in all pets ordered by id.
    QSqlQuery query;
    query.prepare("SELECT usernameAdoptee, shelter, petIds FROM adoptee "
                  "WHERE usernameAdoptee = (:usernameAdoptee) AND password = (:password);");
    query.bindValue(":usernameAdoptee", qUsername);
    query.bindValue(":password", qPassword);
    if(query.exec() && exists) {
        query.next();
        //Creates and fills info struct
        Adoptee *adoptee = new Adoptee;
        adoptee->username = query.value("usernameAdoptee").toString().toStdString();
        adoptee->shelter = query.value("shelter").toString().toStdString();
        adoptee->ownedPetIds = stringToIntVector(query.value("petIds").toString().toStdString());
        return adoptee; //Returns adoptee struct
    } else if(!exists){
        qDebug() << "Adoptee Cannot be found using Select." << endl;
        return nullptr;
    } else {
         qDebug() << "Read Adoptee through query error: " << query.lastError();
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
        if(pets.at(i)->id == findId) {
            return pets.at(i);
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
    query.prepare("SELECT COUNT (*) FROM adopter;");
    int rowCount = 0;

    if(query.exec()) {
        if(query.first()){
            rowCount = query.value(0).toInt();
        }
        return rowCount;
    }
    cout << "Error: Cannot find number of adopters\n";
    return -1;
}

//Finds number of registered adoptees in the database
int DatabaseManager::getNumAdoptees() {
    //Prepares a query to run in Sql
    //Finds number of unique usernames in the adoptee database
    QSqlQuery query;
    query.prepare("SELECT COUNT (*) FROM adoptee;");
    int rowCount = 0;

    if(query.exec()) {
        if(query.first()){
            rowCount = query.value(0).toInt();
        }
        return rowCount;
    }
    cout << "Error: Cannot find number of adoptees\n";
    return -1;
}

//Adds a pet to the database of pets and to the vector pf pets
bool DatabaseManager::addPet(Pet *pet) {
    QSqlQuery sel;
    sel.prepare("SELECT name, species, breed FROM pet WHERE name = (:name) AND species = (:species) AND breed = (:breed)");
    QString n = QString::fromStdString(pet->name);
    sel.bindValue(":name", n);
    QString s = QString::fromStdString(pet->name);
    sel.bindValue(":species", s);
    QString b = QString::fromStdString(pet->name);
    sel.bindValue(":breed", b);
    if(sel.exec()){
        if(sel.next()){
            return false;
        }
    }
    //Tests for bad data
    if(pet->age <= 0 || pet->weight <= 0) {
        return false;
    }
    petIdMax++;
    pet->id = petIdMax; //Sets given pet's id to max id + 1
    //cout << pet->id << std::endl;

    //Prepares a query that inserts all pet info from pet struct
    QSqlQuery q;
        q.prepare("INSERT INTO pet (petId, name, species, breed, "
                  "age, weight, color, hypoallergenic, sex, bio) "
                  "VALUES (:petId, :name, :species, :breed, :age, "
                  ":weight, :color, :hypoallergenic, :sex, :bio);");
        q.bindValue(":petId", pet->id);
        QString name = QString::fromStdString(pet->name);
        q.bindValue(":name", name);
        QString species = QString::fromStdString(pet->species);
        q.bindValue(":species", species);
        QString breed = QString::fromStdString(pet->breed);
        q.bindValue(":breed", breed);
        q.bindValue(":age", pet->age);
        q.bindValue(":weight", pet->weight);
        QString color = QString::fromStdString(pet->color);
        q.bindValue(":color", color);
        q.bindValue(":hypoallergenic", pet->hypoallergenic);
        QString sex = QString::fromStdString(pet->sex);
        q.bindValue(":sex", sex);
        QString bio = QString::fromStdString(pet->bio);
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
    bool exists = false;
    QSqlQuery sel;
    sel.prepare("SELECT petId FROM pet WHERE petId = (:id);");
    sel.bindValue(":id", petId);
    if(sel.exec()){
        if(sel.next()){
            exists = true;
        }
    }

    QSqlQuery q;
    q.prepare("DELETE FROM pet WHERE petId = (:petId);");
    q.bindValue(":petId", petId);

    if(q.exec() && exists) {
        //Searches through pets vector to find pet with given id
        for(int i = 0; i < (int)pets.size(); i++) {
            //When pet with matching id is found, return it
            if(pets.at(i)->id == petId) {
                pets.erase(pets.begin() + i);
                return true;
            }
        }
    }
    return false;
}

//Adds an adopter to the database of adopters, using the pref struct
bool DatabaseManager::addAdopter(Adopter *a, string password) {
    //Prepares a query that inserts given adopter
    bool exists = false;
    QSqlQuery sel;
    sel.prepare("SELECT usernameAdopter, password FROM adopter WHERE usernameAdopter = (:un) AND password = (:pw);");
    QString qUn = QString::fromStdString(a->username);
    sel.bindValue(":un", qUn);
    QString qPw = QString::fromStdString(password);
    sel.bindValue(":pw", qPw);
    if(sel.exec()){
        if(sel.next()){
            exists = true;
        }
    }

    QSqlQuery q;
        q.prepare("INSERT INTO adopter (usernameAdopter, password, "
                  "likedPetIds, dislikedPetIds, "
                  "prefSpecies, prefSpeciesReq, "
                  "prefBreed, prefBreedReq, prefAge, prefAgeReq, "
                  "prefWeight, prefWeightReq, prefColor, prefColorReq, "
                  "prefHypoallergenic, prefHypoallergenicReq, "
                  "prefSex, prefSexReq) "
                  "VALUES (:usernameAdopter, :password, "
                  ":likedPetIds, :dislikedPetIds, "
                  ":prefSpecies, :prefSpeciesReq, "
                  ":prefBreed, :prefBreedReq, :prefAge, :prefAgeReq, "
                  ":prefWeight, :prefWeightReq, :prefColor, :prefColorReq, "
                  ":prefHypoallergenic, :prefHypoallergenicReq, "
                  ":prefSex, :prefSexReq);");
        QString qUsername = QString::fromStdString(a->username);
        q.bindValue(":usernameAdopter", qUsername);

        QString qPassword = QString::fromStdString(password);
        q.bindValue(":password", qPassword);

        q.bindValue(":likedPetIds", intVectorToQString(a->likedPetIds));
        q.bindValue(":dislikedPetIds", intVectorToQString(a->dislikedPetIds));

        QString qPrefSpecies = QString::fromStdString(a->prefSpecies);
        q.bindValue(":prefSpecies", qPrefSpecies);
        q.bindValue(":prefSpeciesReq", a->prefSpeciesReq);

        QString qPrefBreed = QString::fromStdString(a->prefBreed);
        q.bindValue(":prefBreed", qPrefBreed);
        q.bindValue(":prefBreedReq", a->prefBreedReq);

        q.bindValue(":prefAge", a->prefAge);
        q.bindValue(":prefAgeReq", a->prefAgeReq);

        q.bindValue(":prefWeight", a->prefWeight);
        q.bindValue(":prefWeightReq", a->prefWeightReq);

        QString qPrefColor = QString::fromStdString(a->prefColor);
        q.bindValue(":prefColor", qPrefColor);
        q.bindValue(":prefColorReq", a->prefColorReq);

        q.bindValue(":prefHypoallergenic", a->prefHypoallergenic);
        q.bindValue(":prefHypoallergenicReq", a->prefHypoallergenicReq);

        QString qPrefSex = QString::fromStdString(a->prefSex);
        q.bindValue(":prefSex", qPrefSex);
        q.bindValue(":prefSexReq", a->prefSexReq);
    if(q.exec() && !exists) {
        return true;
    } else if(exists){
        qDebug() << "Adopter Already Exists.";
        return false;
    } else {
        //returns false if query has error
        qDebug() << "Add Adopter Error" << q.lastError();
        return false;
    }
}

//Removes an adopter from the database of adopters
bool DatabaseManager::removeAdopter(string username) {
    QString qUsername = QString::fromStdString(username);
    bool exists = false;

    QSqlQuery sel;
    sel.prepare("SELECT usernameAdopter, password FROM adopter WHERE usernameAdopter = (:un);");
    QString qUn = QString::fromStdString(username);
    sel.bindValue(":un", qUn);
    if(sel.exec()){
        if(sel.next()){
            exists = true;
        }
    }

    QSqlQuery q;
    q.prepare("DELETE FROM adopter WHERE usernameAdopter = (:usernameAdopter);");
    q.bindValue(":usernameAdopter", qUsername);

    if(q.exec() && exists) {
        return true;
    }
    return false;
}

//Adds an "adoptee" to the database of adoptees, using the adoptee info struct
bool DatabaseManager::addAdoptee(Adoptee *a, string password) {
    bool exists = false;
    QSqlQuery sel;
    sel.prepare("SELECT usernameAdoptee FROM adoptee WHERE usernameAdoptee = (:un);");
    QString qUn = QString::fromStdString(a->username);
    sel.bindValue(":un", qUn);
    if(sel.exec()){
        if(sel.next()){
            exists = true;
        }
    }
    //Prepares a query that inserts given adoptee
    QSqlQuery q;
        q.prepare("INSERT INTO adoptee (usernameAdoptee, password, shelter, petIds) "
                  "VALUES (:usernameAdoptee, :password, :shelter, :petIds);");
        QString username = QString::fromStdString(a->username);
        q.bindValue(":usernameAdoptee", username);
        QString qPassword = QString::fromStdString(password);
        q.bindValue(":password", qPassword);
        QString shelter = QString::fromStdString(a->shelter);
        q.bindValue(":shelter", shelter);
        q.bindValue(":petIds", intVectorToQString(a->ownedPetIds));
    if(q.exec() && !exists) {
        return true;
    } else if(exists){
        qDebug() << "Adoptee Already Exists.";
        return false;
    } else {
        qDebug() << "Add Adoptee Error" << q.lastError();
        return false;
    }
}

//Removes an adoptee from the database of adoptees
bool DatabaseManager::removeAdoptee(string username) {
    bool exists = false;
    QSqlQuery sel;
    sel.prepare("SELECT usernameAdoptee FROM adoptee WHERE usernameAdoptee = (:un);");
    QString qUn = QString::fromStdString(username);
    sel.bindValue(":un", qUn);
    if(sel.exec()){
        if(sel.next()){
            exists = true;
        }
    }

    QString qUsername = QString::fromStdString(username);

    QSqlQuery q;
    q.prepare("DELETE FROM adoptee WHERE usernameAdoptee = (:usernameAdoptee);");
    q.bindValue(":usernameAdoptee", qUsername);

    if(q.exec() && exists) {
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

vector<string> DatabaseManager::messageParse(string message) {
    string delimeterSender = ":";
    string delimeterEndMessage = "|";

    while(message.length() > 0) {
        string senderReciever = message.substr(0, message.find(delimeterSender));
        cout << senderReciever << endl;
        message.erase(0, message.find(delimeterSender));
        if(senderReciever == "S");
    }
}

int DatabaseManager::getPetIdMax() {
    return petIdMax;
}
