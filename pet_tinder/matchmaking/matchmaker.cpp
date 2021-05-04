#include "matchmaker.h"

Matchmaker::Matchmaker(){
    DM = new DatabaseManager();
    innit();


}
void Matchmaker::innit(){
    DM->readInPets();


}

//int Matchmaker::DatabaseInterface(string what, string whatTheUserWants){

//    //returns the location of a pet that matches for inital list
//    //only runs through hard preferences and lists all in arraylist for this class to use


//}
