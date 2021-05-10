#include "matchmaker.h"


//creates an instance of the database
Matchmaker::Matchmaker(){
    DM = new DatabaseManager();
    innit();



}
//reads in pets to the correct areas
void Matchmaker::innit(){
    DM->readInPets();
    sortPrefs();

}
//this is called to return a queue of pets for the petfinder screen
vector<Pet> Matchmaker::DatabaseInterface(string username, string password){


    currentUser = DM->readInAdopter(username, password);
     refreshPetList();

    //cycles through all pets to find pets that match preferences and adds them to the queue
     //continue breaks loop and is triggers for when a pet doesnt match a hard preference
     for(int i = 0; i < (int)sortablePets.size(); i++){

         if(currentUser->prefSpeciesReq == true){
             if(currentUser->prefSpecies != sortablePets.at(i).species){
                 continue;
             }
         }
         if(currentUser->prefBreedReq == true){
             if(currentUser->prefBreed != sortablePets.at(i).breed){
                 continue;
             }
         }
         if(currentUser->prefAgeReq == true){
             if(currentUser->prefAge != sortablePets.at(i).age){
                 continue;
             }
         }
         if(currentUser->prefWeightReq == true){
             if(currentUser->prefWeight != sortablePets.at(i).weight){
                 continue;
             }
         }
         if(currentUser->prefColorReq == true){
             if(currentUser->prefColor != sortablePets.at(i).color){
                 continue;
             }
         }
         if(currentUser->prefHypoallergenicReq == true){
             if(currentUser->prefHypoallergenic != sortablePets.at(i).hypoallergenic){
                 continue;
             }
         }
         if(currentUser->prefSexReq == true){
             if(currentUser->prefSex != sortablePets.at(i).sex){
                 continue;
             }
         }
         else{
             Queue.push_back(sortablePets.at(i));
         }
     }

     if(Queue.size() != 0){
         return Queue;
     }
     //if the queue is empty creates an error pet (just populates current fields to save time"
     else{
         Pet *error;
        error->name = "No more pets matching current preferences";
        error->color = "Please adjust preferences to see more potential pets";
         Queue.push_back(*error);
         return Queue;
     }
}
//re reads in pets and creates a list of all non liked/ disliked pets for database interface
void Matchmaker::refreshPetList(){
    innit();

    //Combines disliked and liked pet ids into one vector and sorts
    //through it to add pets to the sortablePets vector

    discardedPetIds.resize((currentUser->dislikedPetIds.size()+currentUser->likedPetIds.size()));

    for(int i = 0; i < (int)currentUser->dislikedPetIds.size(); i++){
        discardedPetIds.push_back(currentUser->dislikedPetIds.at(i));
    }
    for(int i = currentUser->dislikedPetIds.size(); i < (int)discardedPetIds.size(); i++){

        discardedPetIds.push_back(currentUser->likedPetIds.at(i));
    }



    //sorts through all pets and adds to a vector if they are not liked/disliked
    for(int j = 0; j < DM->getNumPets(); j++){
        int flag = 0;
        for(int k = 0; k < (int)discardedPetIds.size(); k++){
            if(DM->pets.at(j).id == discardedPetIds.at(k)) {
                flag =1;
            }
             else{
            }
        }
        if(flag == 0){
            sortablePets.push_back(DM->pets.at(j));
        }
        else{

        }
    }


}
void Matchmaker::sortPrefs(){


    total.species.push_back(DM->pets.at(0).species);
    for(int i = 0; i < DM->getNumPets(); i++){
            int flag = 0;
            for(int j = 0; j< (int)total.species.size(); j++){
                if(DM->pets.at(i).species != total.species.at(j)){
                    flag++;
                }
                else{
                }
            }
            if(flag == (int)total.species.size()-1){
                total.species.push_back(DM->pets.at(i).species);
            }
            else{
            }
        }

    total.breeds.push_back(DM->pets.at(0).breed);
    for(int i = 0; i < DM->getNumPets(); i++){
            int flag = 0;
            for(int j = 0; j< (int)total.breeds.size(); j++){
                if(DM->pets.at(i).breed != total.breeds.at(j)){
                    flag++;
                }
                else{
                }
            }
            if(flag == (int)total.breeds.size()-1){
                total.breeds.push_back(DM->pets.at(i).breed);
            }
            else{
            }
        }

    total.ages.push_back(DM->pets.at(0).age);
    for(int i = 0; i < DM->getNumPets(); i++){
            int flag = 0;
            for(int j = 0; j< (int)total.ages.size(); j++){
                if(DM->pets.at(i).age != total.ages.at(j)){
                    flag++;
                }
                else{
                }
            }
            if(flag == (int)total.ages.size()-1){
                total.ages.push_back(DM->pets.at(i).age);
            }
            else{
            }
        }

    total.weights.push_back(DM->pets.at(0).weight);
    for(int i = 0; i < DM->getNumPets(); i++){
            int flag = 0;
            for(int j = 0; j< (int)total.weights.size(); j++){
                if(DM->pets.at(i).weight != total.weights.at(j)){
                    flag++;
                }
                else{
                }
            }
            if(flag == (int)total.weights.size()-1){
                total.weights.push_back(DM->pets.at(i).weight);
            }
            else{
            }
        }

    total.colors.push_back(DM->pets.at(0).color);
    for(int i = 0; i < DM->getNumPets(); i++){
            int flag = 0;
            for(int j = 0; j< (int)total.colors.size(); j++){
                if(DM->pets.at(i).color != total.colors.at(j)){
                    flag++;
                }
                else{
                }
            }
            if(flag == (int)total.colors.size()-1){
                total.colors.push_back(DM->pets.at(i).color);
            }
            else{
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
