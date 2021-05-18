#include "matchmaker.h"
#include<bits/stdc++.h>

//creates an instance of the database
Matchmaker::Matchmaker(){
    DM = new DatabaseManager();

}

//reads in pets to the correct areas
void Matchmaker::innit(){
    DM->readInPets();
    sortPrefs();
}
//this is called to return a queue of pets for the petfinder screen
vector<Pet*> Matchmaker::DatabaseInterface(Adopter *cu){
    currentUser = cu;
    refreshPetList();
    Queue.clear();

    //cout << "sortablePets size = " + to_string((int)sortablePets.size()) << endl;
    if(sortablePets.size() <= 0) {
        cout << "pass" << endl;
        vector<Pet*> empty;
        return empty;
    }
    //cycles through all pets to find pets that match preferences and adds them to the queue
    //continue breaks loop and is triggers for when a pet doesnt match a hard preference
    for(int i = 0; i < (int)sortablePets.size(); i++){ //SORTABLE PETS EMPTY
        if(currentUser->prefSpeciesReq == true){
            if(strcasecmp(currentUser->prefSpecies.c_str(), sortablePets.at(i)->species.c_str()) != 0){
                continue;
            }
        }
        if(currentUser->prefBreedReq == true){
            if(strcasecmp(currentUser->prefBreed.c_str(),sortablePets.at(i)->breed.c_str()) != 0){
                continue;
            }
        }
        if(currentUser->prefAgeReq == true){
            if((int)currentUser->prefAge != (int)sortablePets.at(i)->age){
                continue;
            }
        }
        if(currentUser->prefWeightReq == true){
            if(currentUser->prefWeight != sortablePets.at(i)->weight){
                continue;
            }
        }
        if(currentUser->prefColorReq == true){
            if(strcasecmp(currentUser->prefColor.c_str(),sortablePets.at(i)->color.c_str()) != 0){
                continue;
            }
        }
        if(currentUser->prefHypoallergenicReq == true){
            if(currentUser->prefHypoallergenic != sortablePets.at(i)->hypoallergenic){
                continue;
            }
        }
        if(currentUser->prefSexReq == true){
            if(currentUser->prefSex != sortablePets.at(i)->sex){
                continue;
            }
        }
        //cout << "Pet successfully added for " + currentUser->username << endl;
        Queue.push_back(sortablePets.at(i));
    }
    return Queue;
}
//rereads in pets and creates a list of all non liked/disliked pets for database interface
void Matchmaker::refreshPetList(){
    sortablePets.clear();
    innit();

    //Combines disliked and liked pet ids into one vector and sorts
    //through it to add pets to the sortablePets vector
    //discardedPetIds.resize((currentUser->dislikedPetIds.size()+currentUser->likedPetIds.size()));

    for(int i = 0; i < (int)currentUser->dislikedPetIds.size(); i++){
        //cout << "disliked pet: " + to_string(currentUser->dislikedPetIds.at(i)) << endl;
        discardedPetIds.push_back(currentUser->dislikedPetIds.at(i));
    }

    //cout << "likedPets size: " << currentUser->likedPetIds.size() << endl;
    for(int i = 0; i < (int)currentUser->likedPetIds.size(); i++){
        //cout << "liked pet: " + to_string(currentUser->likedPetIds.at(i)) << endl;
        discardedPetIds.push_back(currentUser->likedPetIds.at(i));
    }

    //cout << "Number of pets in DM vector = " + to_string(DM->getNumPets()) << endl;
    //sorts through all pets and adds to a vector if they are not liked/disliked
    for(int j = 0; j < DM->getNumPets(); j++){
        //cout << "pet id: " + to_string(DM->pets.at(j)->id) << endl;
        int flag = 0;
        for(int k = 0; k < (int)discardedPetIds.size(); k++){
            if(DM->pets.at(j)->id == discardedPetIds.at(k)) {
                flag = 1;
            }
        }
        if(flag == 0){
            //cout << "Pet added to sortablePets vector" << endl;
            sortablePets.push_back(DM->pets.at(j));
        }
    }
}
void Matchmaker::sortPrefs(){
    //Sort Pref Species
    total.species.push_back(DM->pets.at(0)->species);
    for(int i = 0; i < DM->getNumPets(); i++){
        int flag = 0;
        for(int j = 0; j < (int)total.species.size(); j++){
            if(DM->pets.at(i)->species != total.species.at(j)){
                flag++;
            }
        }
        if(flag != (int)total.species.size()-1){
            total.species.push_back(DM->pets.at(i)->species);
        }
    }
    //Sort Pref Breed
    total.breeds.push_back(DM->pets.at(0)->breed);
    for(int i = 0; i < DM->getNumPets(); i++){
        int flag = 0;
        for(int j = 0; j < (int)total.breeds.size(); j++){
            if(DM->pets.at(i)->breed != total.breeds.at(j)){
                flag++;
            }
        }
        if(flag != (int)total.breeds.size()-1){
            total.breeds.push_back(DM->pets.at(i)->breed);
        }
    }

    //Sort Pref Age
    total.ages.push_back(DM->pets.at(0)->age);
    for(int i = 0; i < DM->getNumPets(); i++){
        int flag = 0;
        for(int j = 0; j< (int)total.ages.size(); j++){
            if(DM->pets.at(i)->age != total.ages.at(j)){
                flag++;
            }
        }
        if(flag != (int)total.ages.size()-1){
            total.ages.push_back(DM->pets.at(i)->age);
        }
    }

    //Sort Pref Weight
    total.weights.push_back(DM->pets.at(0)->weight);
    for(int i = 0; i < DM->getNumPets(); i++){
        int flag = 0;
        for(int j = 0; j< (int)total.weights.size(); j++){
            if(DM->pets.at(i)->weight != total.weights.at(j)){
                flag++;
            }
        }
        if(flag != (int)total.weights.size()-1){
            total.weights.push_back(DM->pets.at(i)->weight);
        }
    }

    //Sort Pref Color
    total.colors.push_back(DM->pets.at(0)->color);
    for(int i = 0; i < DM->getNumPets(); i++){
        int flag = 0;
        for(int j = 0; j< (int)total.colors.size(); j++){
            if(DM->pets.at(i)->color != total.colors.at(j)){
                flag++;
            }
        }
        if(flag != (int)total.colors.size()-1){
            total.colors.push_back(DM->pets.at(i)->color);
        }
    }
    arrangePrefs();
}
void Matchmaker::arrangePrefs(){
    sort(total.species.begin(),total.species.end());
    sort(total.breeds.begin(),total.breeds.end());
    sort(total.colors.begin(),total.colors.end());
    sort(total.ages.begin(),total.ages.end());
    sort(total.weights.begin(),total.weights.end());
}
