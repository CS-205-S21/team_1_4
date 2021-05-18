#include <iostream>
#include "gtest/gtest.h"
#include "../matchmaking/matchmaker.h"
#include "../databasemanager/databasemanager.h"

// The fixture for testing class Databasemanager
class DatabaseManager_Test : public::testing::Test {
    protected:

    DatabaseManager_Test() {
        dm = new DatabaseManager();
        dm->readInPets();
        numPets = dm->getNumPets();
        numAdopters = dm->getNumAdopters();
        numAdoptees = dm->getNumAdoptees();
    }

    virtual void TearDown() {
        delete dm;
    }

    DatabaseManager *dm;
    int numPets;
    int numAdopters;
    int numAdoptees;
};

//The Fixture for testing class Matchmaker
class Matchmaking_Test : public::testing::Test {
    protected:

    Matchmaking_Test() {
        mm = new Matchmaker();
        dm = mm->DM;

        addTestPets();
        addTestAdopters();
    }

    void addTestPets(){
        tPet1 = new Pet;
        tPet1->name = "Loki";
        tPet1->species = "Dog";
        tPet1->breed = "Shorkie";
        tPet1->age = 1;
        tPet1->weight = 12.5;
        tPet1->color = "Brown";
        tPet1->hypoallergenic = false;
        tPet1->sex = "Female";
        tPet1->bio = "The beloved Puppy of Danny, the head Tester for Claws n' Paws!";
        tPet1->image = "";
        dm->addPet(tPet1);

        tPet2 = new Pet;
        tPet2->name = "Sir McQuackins";
        tPet2->species = "Duck";
        tPet2->breed = "Domestic";
        tPet2->age = 4;
        tPet2->weight = 9.0;
        tPet2->color = "White";
        tPet2->hypoallergenic = false;
        tPet2->sex = "Male";
        tPet2->bio = "What time does a duck wake up in the morning? At the quack of Dawn!";
        tPet2->image = "";
        dm->addPet(tPet2);

        tPet3 = new Pet;
        tPet3->name = "Frumpkin";
        tPet3->species = "Cat";
        tPet3->breed = "Bengal";
        tPet3->age = 7;
        tPet3->weight = 8.4;
        tPet3->color = "Orange";
        tPet3->hypoallergenic = true;
        tPet3->sex = "Male";
        tPet3->bio = "Oh, you have cat to be kitten me right meow ^.^ OwO";
        tPet3->image = "";
        dm->addPet(tPet3);

        tPet4 = new Pet;
        tPet4->name = "Thor";
        tPet4->species = "Dog";
        tPet4->breed = "Shih Tzu";
        tPet4->age = 7;
        tPet4->weight = 12.5;
        tPet4->color = "White";
        tPet4->hypoallergenic = true;
        tPet4->sex = "Male";
        tPet4->bio = "I went to the zoo, but they only had one dog... It was a Shih Tzu";
        tPet4->image = "";
        dm->addPet(tPet4);
    }

    void addTestAdopters(){
        vector<int> likedPets;
        vector<int> dislikedPets;
        likedPets.push_back(0);
        dislikedPets.push_back(0);

        dan = new Adopter;
        dan->username = "Danny_Admin";
        dan->likedPetIds = likedPets;
        dan->dislikedPetIds = dislikedPets;
        dan->prefSpecies = "Dog";
        dan->prefSpeciesReq = false;
        dan->prefBreed = "Shorkie";
        dan->prefBreedReq = false;
        dan->prefAge = 1;
        dan->prefAgeReq = false;
        dan->prefWeight = 12.5;
        dan->prefWeightReq = false;
        dan->prefColor = "Brown";
        dan->prefColorReq = false;
        dan->prefHypoallergenic = false;
        dan->prefHypoallergenicReq = false;
        dan->prefSex = "Female";
        dan->prefSexReq = false;
        dan->bio = "Lookin for some Hot Dogs";
        dm->addAdopter(dan, "D1a2N3");

        alex = new Adopter;
        alex->username = "Alex_Admin";
        alex->likedPetIds = likedPets;
        alex->dislikedPetIds = dislikedPets;
        alex->prefSpecies = "Duck";
        alex->prefSpeciesReq = true;
        alex->prefBreed = "Domestic";
        alex->prefBreedReq = true;
        alex->prefAge = 4;
        alex->prefAgeReq = false;
        alex->prefWeight = 9.0;
        alex->prefWeightReq = true;
        alex->prefColor = "White";
        alex->prefColorReq = true;
        alex->prefHypoallergenic = false;
        alex->prefHypoallergenicReq = true;
        alex->prefSex = "Male";
        alex->prefSexReq = true;
        alex->bio = "I am gay.";
        dm->addAdopter(alex, "A1l2E3x4");

        ally = new Adopter;
        ally->username = "Ally_Admin";
        ally->likedPetIds = likedPets;
        ally->dislikedPetIds = dislikedPets;
        ally->prefSpecies = "Cat";
        ally->prefSpeciesReq = true;
        ally->prefBreed = "Russian Blue";
        ally->prefBreedReq = false;
        ally->prefAge = 4;
        ally->prefAgeReq = true;
        ally->prefWeight = 12.5;
        ally->prefWeightReq = true;
        ally->prefColor = "Orange";
        ally->prefColorReq = true;
        ally->prefHypoallergenic = false;
        ally->prefHypoallergenicReq = true;
        ally->prefSex = "Male";
        ally->prefSexReq = false;
        ally->bio = "Haha I am female.";
        dm->addAdopter(ally, "A1l2L3y4");

        addy = new Adopter;
        addy->username = "Addy_Admin";
        addy->likedPetIds = likedPets;
        addy->dislikedPetIds = dislikedPets;
        addy->prefSpecies = "Pig";
        addy->prefSpeciesReq = 1;
        addy->prefBreed = "Duroc";
        addy->prefBreedReq = 1;
        addy->prefAge = 8;
        addy->prefAgeReq = 1;
        addy->prefWeight = 27.5;
        addy->prefWeightReq = 1;
        addy->prefColor = "Gray";
        addy->prefColorReq = 1;
        addy->prefHypoallergenic = 1;
        addy->prefHypoallergenicReq = 1;
        addy->prefSex = "Male";
        addy->prefSexReq = 1;
        addy->bio = "I don't care.";
        dm->addAdopter(addy, "A1d2D3y4");
    }

    virtual void TearDown() {
        dm->removePet(tPet1->id);
        dm->removePet(tPet2->id);
        dm->removePet(tPet3->id);
        dm->removePet(tPet4->id);
        dm->removeAdopter(dan->username);
        dm->removeAdopter(alex->username);
        dm->removeAdopter(ally->username);
        dm->removeAdopter(addy->username);
        delete dm;
        delete mm;
    }

    Matchmaker *mm;
    DatabaseManager *dm;
    Pet *tPet1;
    Pet *tPet2;
    Pet *tPet3;
    Pet *tPet4;
    Adopter *dan;
    Adopter *alex;
    Adopter *ally;
    Adopter *addy;
};

//*********************************************************************************************************************
//*****************************************TESTS FOR DATABASE PETS*****************************************************
//*********************************************************************************************************************
//This test is assuming that this is being run before anything else was added
//to the database.
TEST_F(DatabaseManager_Test, ADD_AND_REMOVE_PET) {
    Pet *bear = new Pet;
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pet should have no additions.";
    bear->name = "Trinket";
    bear->species = "Large";
    bear->breed = "Fuzzy";
    bear->age = 6;
    bear->weight = 200.0;
    bear->color = "Brown";
    bear->hypoallergenic = false;
    bear->sex = "Male";
    bear->bio = "The companion to Lady Vex'ahlia, Mistress of the Grey Hunt. Accompanying her,"
               "Trinket has seen a great many adventure and receieved special treatment as the"
               "bear that aided Vox Machina through several adventures that would save all of Tal"
               "Dore. THis is probably the most well-known bear in the world, for good reason. ";
    bear->image = "";
    ASSERT_TRUE(dm->addPet(bear))
                        << "Bear should have been added.";
    ASSERT_EQ(numPets+1, dm->getNumPets())
                    << "Pets should have one addition.";
    ASSERT_TRUE(dm->removePet(bear->id))
                        << "Bear should have been removed.";
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should be back to original size.";
}

//This will not only test to make sure that the database can handle spaces between entries,
//but will also test to make sure that two pets, with the same id will not both be added.
TEST_F(DatabaseManager_Test, ADD_MULTIPLE_IDS) {
    Pet *animal = new Pet;
    Pet *animalA = new Pet;
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should have no additions.";
    animal->id = numPets+1;
    animal->name = "Jyken Deydhall";
    animal->species = "Human";
    animal->breed = "Conquest Paladin";
    animal->age = 28;
    animal->weight = 190.0;
    animal->color = "Pale Orange/Pink";
    animal->hypoallergenic = false;
    animal->sex = "Male";
    animal->bio = "The champion to The Mockery, Jyken Deydhall found his demis to the dracolich"
                 "commanded by the notorious undead king. He has since woken up, with a renewed"
                 "vow and motivation to seek out his brother's murderer, and his mentor, Enrico"
                 "Brando, the leader of the Diashad order of Paladins. Jyken has sworn to make"
                 "Enrico wish he was never alive.";
    animal->image = "";
    ASSERT_TRUE(dm->addPet(animal))
                    << "Animal should have been added.";

    animalA->id = animal->id;
    animalA->name = "Red Valley Mist";
    animalA->species = "Tabaxi";
    animalA->breed = "Mercy Monk";
    animalA->age = 22;
    animalA->weight = 120.0;
    animalA->color = "Light Orange";
    animalA->hypoallergenic = true;
    animalA->sex = "Female";
    animalA->bio = "This monk has studied under the tutelage of Master Ba, a monk that has adopted"
                  "Mist when he was very young. Mist has almost no memories of his childhood, but"
                  "trusts the word of his master that he does not need to know anything. However,"
                  "master Ba had mysteriously passed away, leaving Mist to his own devices. He then"
                  "went on to discover his own path, acting as judge of the mortal world and seeking"
                  "to learn who he is.";
    animalA->image = "";
    ASSERT_TRUE(dm->addPet(animalA))
                << "AnimalA should have an id overwritten and added anyway";
    ASSERT_TRUE(dm->removePet(animal->id))
                << "Animal should have been removed.";
    ASSERT_TRUE(dm->removePet(animalA->id))
                << "AnimalA should have been removed.";
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should be back to the original number.";
}

//This will test to see if you can add a pet with almost empty parameters, then test to see if
//it works with empty parameters, but with a non-empty id.
TEST_F(DatabaseManager_Test, ADD_EMPTY_PET) {
    Pet *frog = new Pet;
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should have no additions";

    frog->name = "";
    frog->species = "";
    frog->breed = "";
    frog->age = 1;
    frog->weight = 0.1;
    frog->color = "";
    frog->hypoallergenic = false;
    frog->sex = "";
    frog->bio = "";
    frog->image = "";

    ASSERT_TRUE(dm->addPet(frog))
                    << "Pets should accept parameters if there are some non-applicable information.";
    ASSERT_TRUE(dm->removePet(frog->id))
                    << "Frog should be deleted.";
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should be back to the original number.";
}

//Try to add and remove a pet that isn't in the table
TEST_F(DatabaseManager_Test, ADD_NONEXISTENT_PET) {
    Pet *knowledgeOfHowToCode = new Pet;
    knowledgeOfHowToCode->id = -1;
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should have no additions.";
    ASSERT_FALSE(dm->removePet(knowledgeOfHowToCode->id))
                << "You cannot remove what does not exist.";
}

//This will test to see if you can add a pet with weird data such as a negative id number
TEST_F(DatabaseManager_Test, WEIRD_PET_DATA) {
    Pet *animal = new Pet;
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should have normal amount of pets";
    animal->id = -1;
    animal->name = "Rdame Ylepse";
    animal->species = "Updog";
    animal->breed = "Sawcawn";
    animal->age = -9;
    animal->weight = -4;
    animal->color = "Spotted";
    animal->hypoallergenic = true;
    animal->sex = "Non-Binary";
    animal->bio = "N/A";
    animal->image = "";
    ASSERT_FALSE(dm->addPet(animal))
                    << "Pets should not accept parameters with weird information";
    //just in case it was not removed yet
    ASSERT_FALSE(dm->removePet(animal->id));
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should now have the original amout of pets";
}

//This will test the search method for database manager
TEST_F(DatabaseManager_Test, FIND_PETS) {
    Pet *pika = new Pet;
    Pet *tepi = new Pet;
    Pet *sniv = new Pet;
    Pet *osha = new Pet;

    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should have no additions";
    pika->name = "Pikachu";
    pika->species = "Mouse";
    pika->breed = "Brave";
    pika->age = 12;
    pika->weight = 19.0;
    pika->color = "Yellow";
    pika->hypoallergenic = false;
    pika->sex = "Male";
    pika->bio = "Pikachu is an electric type pokemon, probably best known as the companion to"
               "Ash Ketchum, or Red, who is known as the worl'd greatest Pokemon trainer. "
               "In the stories, Pikachu was Ash's first pokemon, and though their relationship"
               "was rocky at first, they grew to be the closest of friends and swore to become the"
               "very best like no one ever was together.";
    pika->image = "";
    ASSERT_TRUE(dm->addPet(pika))
                    << "Pets should now contain only 1 addition";

    tepi->name = "Tepig";
    tepi->species = "Pig";
    tepi->breed = "Humble";
    tepi->age = 6;
    tepi->weight = 22.5;
    tepi->color = "Orange";
    tepi->hypoallergenic = true;
    tepi->sex = "Male";
    tepi->bio = "Tepig is a fire type pig-like pokemon that is a starter for generation 5. Tepig "
               "also joined Ash Ketchum in his quest to become the ultimate pokemon trainer, but"
               "tepig is objectively one of the best starters of all pokemon. The final evolution"
               "is Emboar.";
    tepi->image = "";
    ASSERT_TRUE(dm->addPet(tepi))
                    << "Pets should now contain only 2 additions";

    sniv->name = "Snivy";
    sniv->species = "Snake";
    sniv->breed = "Shy";
    sniv->age = 8;
    sniv->weight = 12.2;
    sniv->color = "Green";
    sniv->hypoallergenic = false;
    sniv->sex = "Female";
    sniv->bio = "Snivy is a grass snake, and juts like the other gen 5 starters, has also joined"
               "Ash for a brief period. Snivy can evolve into the graceful Serperior, the superior"
               "grass serpent that can slither around and capture its foes with its grassy entanglement."
               "Snivy is a beautiful pokemon with great evolutions for a fresh design in generation 5.";
    sniv->image = "";
    ASSERT_TRUE(dm->addPet(sniv))
                    << "Pets should now contain only 3 additions";

    osha->name = "Oshawott";
    osha->species = "Turtle?";
    osha->breed = "Reckless";
    osha->age = 5;
    osha->weight = 21.8;
    osha->color = "Blue and White";
    osha->hypoallergenic = true;
    osha->sex = "Male";
    osha->bio = "Oshawott is a generation 5 starter, who also breifly joined Ash Ketchum's adventure,"
               "but is another yet amazing starter. I do not know what type of animal Oshawott resembles,"
               "but it might be some sort of turtle. Oshawott has some sort of boomerang weapon that "
               "can come off its body, but evolves into Samurott, a large and intimidating pokemon with"
               "the wespons from its first evolution adorning its legs. Truly Generation 5 was a masterpiece.";
    osha->image = "";
    ASSERT_TRUE(dm->addPet(osha))
                    << "Pets should now contain only 4 additions";

    ASSERT_EQ(pika->name, dm->findPet(pika->id)->name);
    ASSERT_EQ(tepi->name, dm->findPet(tepi->id)->name);
    ASSERT_EQ(sniv->name, dm->findPet(sniv->id)->name);
    ASSERT_EQ(osha->name, dm->findPet(osha->id)->name);

    ASSERT_EQ(numPets+4, dm->getNumPets())
                    << "Pets should have all new pokemon";
    ASSERT_TRUE(dm->removePet(pika->id))
                    << "Pika should be deleted.";
    ASSERT_EQ(numPets+3, dm->getNumPets())
                    << "Pets should have three pokemon";
    ASSERT_TRUE(dm->removePet(tepi->id))
                    << "Tepi should be deleted.";
    ASSERT_EQ(numPets+2, dm->getNumPets())
                    << "Pets should have two pokemon";
    ASSERT_TRUE(dm->removePet(sniv->id))
                    << "Sniv should be deleted.";
    ASSERT_EQ(numPets+1, dm->getNumPets())
                    << "Pets should have one pokemon";
    ASSERT_TRUE(dm->removePet(osha->id))
                    << "Osha should be deleted.";
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should be back to original number";
}

//This will test Updating a pet in the database manager
TEST_F(DatabaseManager_Test, UPDATE_PET) {
    Pet *bear = new Pet;
    bear->name = "Trinket";
    bear->species = "Large";
    bear->breed = "Fuzzy";
    bear->age = 6;
    bear->weight = 200.0;
    bear->color = "Brown";
    bear->hypoallergenic = false;
    bear->sex = "Male";
    bear->bio = "The companion to Lady Vex'ahlia, Mistress of the Grey Hunt. Accompanying her,"
               "Trinket has seen a great many adventure and receieved special treatment as the"
               "bear that aided Vox Machina through several adventures that would save all of Tal"
               "Dore. THis is probably the most well-known bear in the world, for good reason. ";
    bear->image = "";
    ASSERT_TRUE(dm->addPet(bear))
                        << "Bear should have been added.";
    ASSERT_EQ(numPets+1, dm->getNumPets())
                    << "Pets should have one addition.";
    bear->name = "Not Trinket";
    bear->species = "Bear";
    bear->breed = "Brown Bear";
    bear->age = 7;
    bear->weight = 250.5;
    bear->color = "brown";
    bear->hypoallergenic = true;
    bear->sex = "Female";
    bear->bio = "Changed.";
    ASSERT_TRUE(dm->updatePet(bear));
    ASSERT_EQ("Not Trinket", dm->findPet(bear->id)->name)
                        << "Bear should have updated information";
    ASSERT_EQ("Bear", dm->findPet(bear->id)->species)
                        << "Bear should have updated information";
    ASSERT_EQ("Brown Bear", dm->findPet(bear->id)->breed)
                        << "Bear should have updated information";
    ASSERT_EQ(7, dm->findPet(bear->id)->age)
                        << "Bear should have updated information";
    ASSERT_EQ(250.5, dm->findPet(bear->id)->weight)
                        << "Bear should have updated information";
    ASSERT_EQ("brown", dm->findPet(bear->id)->color)
                        << "Bear should have updated information";
    ASSERT_EQ("Female", dm->findPet(bear->id)->sex)
                        << "Bear should have updated information";
    ASSERT_EQ("Changed.", dm->findPet(bear->id)->bio)
                        << "Bear should have updated information";
    ASSERT_TRUE(dm->removePet(bear->id))
                        << "Bear should have been removed.";
}

//*********************************************************************************************************************
//*****************************************TESTS FOR DATABASE ADOPTERS*************************************************
//*********************************************************************************************************************
//This will test just simly adding and removing a new pet adopter
TEST_F(DatabaseManager_Test, ADD_AND_REMOVE_ADOPTER) {
    Adopter *dan = new Adopter;
    vector<int> likedPets;
    likedPets.push_back(1);
    vector<int> dislikedPets;
    dislikedPets.push_back(0);
    ASSERT_EQ(numAdopters, dm->getNumAdopters())
                    << "This should never be false";
    dan->username = "Danny";
    dan->likedPetIds = likedPets;
    dan->dislikedPetIds = dislikedPets;
    dan->prefSpecies = "Dog";
    dan->prefSpeciesReq = true;
    dan->prefBreed = "Shorkie";
    dan->prefBreedReq = false;
    dan->prefAge = 3;
    dan->prefAgeReq = false;
    dan->prefWeight = 2.0;
    dan->prefWeightReq = false;
    dan->prefColor = "Brown";
    dan->prefColorReq = false;
    dan->prefHypoallergenic = true;
    dan->prefHypoallergenicReq = true;
    dan->prefSex = "Female";
    dan->prefSexReq = false;
    dan->bio = "";

    ASSERT_TRUE(dm->addAdopter(dan, "Password"))
                        << "dan the adopter was not added.";
    ASSERT_EQ(numAdopters+1, dm->getNumAdopters())
                        << "Adopters should have one addition.";
    ASSERT_TRUE(dm->removeAdopter(dan->username))
                        << "dan the adopter should have been removed.";
    ASSERT_EQ(numAdopters, dm->getNumAdopters())
                        << "Adopters should be back to original size.";
}

//This will test adding adopters with the same username and password, which should not be allowed.
TEST_F(DatabaseManager_Test, ADD_SAME_ADOPTER_INFO) {
    Adopter *addison = new Adopter;
    vector<int> likedPets;
    likedPets.push_back(1);
    vector<int> dislikedPets;
    dislikedPets.push_back(2);
    ASSERT_EQ(numAdopters, dm->getNumAdopters())
                    << "This should never be false";
    addison->username = "Addison Wand";
    addison->likedPetIds = likedPets;
    addison->dislikedPetIds = dislikedPets;
    addison->prefSpecies = "Cat";
    addison->prefSpeciesReq = false;
    addison->prefBreed = "Mao";
    addison->prefBreedReq = false;
    addison->prefAge = 2;
    addison->prefAgeReq = false;
    addison->prefWeight = 20.9;
    addison->prefWeightReq = false;
    addison->prefColor = "gray";
    addison->prefColorReq = true;
    addison->prefHypoallergenic = false;
    addison->prefHypoallergenicReq = false;
    addison->prefSex = "Male";
    addison->prefSexReq = true;
    addison->bio = "";

    Adopter *copy = new Adopter;
    ASSERT_EQ(numAdopters, dm->getNumAdopters())
                    << "This should never be false";
    copy->username = "Addison Wand";
    copy->likedPetIds = addison->likedPetIds;
    copy->dislikedPetIds = addison->dislikedPetIds;
    copy->prefSpecies = "Cat";
    copy->prefSpeciesReq = false;
    copy->prefBreed = "Mao";
    copy->prefBreedReq = false;
    copy->prefAge = 2;
    copy->prefAgeReq = false;
    copy->prefWeight = 20.9;
    copy->prefWeightReq = false;
    copy->prefColor = "gray";
    copy->prefColorReq = true;
    copy->prefHypoallergenic = false;
    copy->prefHypoallergenicReq = false;
    copy->prefSex = "Male";
    copy->prefSexReq = true;
    copy->bio = "";

    ASSERT_TRUE(dm->addAdopter(addison, "Password"))
                        << "addison the adopter was not added.";
    ASSERT_EQ(numAdopters+1, dm->getNumAdopters())
                        << "Adopters should have one addition.";
    ASSERT_FALSE(dm->addAdopter(copy, "Password"))
                        << "Copy was added, but with the same info as addison.";
    ASSERT_EQ(numAdopters+1, dm->getNumAdopters())
                        << "Adopters should have one addition.";
    ASSERT_TRUE(dm->removeAdopter(addison->username))
                        << "Addison the adopter should have been removed.";
    ASSERT_FALSE(dm->removeAdopter(copy->username))
                        << "Copy the adopter should not be able to be removed.";
    ASSERT_EQ(numAdopters, dm->getNumAdopters())
                        << "Adopters should be back to original size.";
}

//This test should allow an adopter to be added even without much defined info
TEST_F(DatabaseManager_Test, ADD_EMPTY_ADOPTER) {
    Adopter *alex = new Adopter;
    vector<int> likedPets;
    likedPets.push_back(1);
    vector<int> dislikedPets;
    dislikedPets.push_back(2);
    ASSERT_EQ(numAdopters, dm->getNumAdopters())
                    << "This should never be false";
    alex->username = "";
    alex->likedPetIds = likedPets;
    alex->dislikedPetIds = dislikedPets;
    alex->prefSpecies = "";
    alex->prefSpeciesReq = false;
    alex->prefBreed = "";
    alex->prefBreedReq = false;
    alex->prefAge = 0;
    alex->prefAgeReq = false;
    alex->prefWeight = 0.0;
    alex->prefWeightReq = false;
    alex->prefColor = "";
    alex->prefColorReq = false;
    alex->prefHypoallergenic = false;
    alex->prefHypoallergenicReq = false;
    alex->prefSex = "";
    alex->prefSexReq = true;
    alex->bio = "";

    ASSERT_TRUE(dm->addAdopter(alex, ""))
                        << "Alex the adopter was not added.";
    ASSERT_EQ(numAdopters+1, dm->getNumAdopters())
                        << "Adopters should have one addition.";
    ASSERT_TRUE(dm->removeAdopter(alex->username))
                        << "Alex the adopter should have been removed.";
    ASSERT_EQ(numAdopters, dm->getNumAdopters())
                        << "Adopters should be back to normal amount.";
}

//This will test adding a nonexistent adopter in the table
TEST_F(DatabaseManager_Test, ADD_NONEXISTENT_ADOPTER) {
    Adopter *nonexistent = new Adopter;
    ASSERT_EQ(numAdopters, dm->getNumAdopters())
                        << "Adopters should have no additions.";
    ASSERT_FALSE(dm->removeAdopter(nonexistent->username))
                        << "Nonexistent adopter should not have been added or removed.";
}

//This will add an adopter with weird infromation that probably should not be accepted
TEST_F(DatabaseManager_Test, ADD_WEIRD_ADOPTER) {
    Adopter *ally = new Adopter;
    vector<int> likedPets;
    likedPets.push_back(1);
    vector<int> dislikedPets;
    dislikedPets.push_back(2);
    ASSERT_EQ(numAdopters, dm->getNumAdopters())
                    << "This should never be false";
    ally->username = "Ally_is_Super_Cool #420";
    ally->likedPetIds = likedPets;
    ally->dislikedPetIds = dislikedPets;
    ally->prefSpecies = "gray";
    ally->prefSpeciesReq = true;
    ally->prefBreed = "yellow";
    ally->prefBreedReq = true;
    ally->prefAge = -100;
    ally->prefAgeReq = true;
    ally->prefWeight = -100.0;
    ally->prefWeightReq = true;
    ally->prefColor = "Abraham Lincoln";
    ally->prefColorReq = true;
    ally->prefHypoallergenic = false;
    ally->prefHypoallergenicReq = true;
    ally->prefSex = "Gay";
    ally->prefSexReq = true;
    ally->bio = "";

    ASSERT_TRUE(dm->addAdopter(ally, ""))
                        << "Ally the adopter was not added.";
    ASSERT_EQ(numAdopters+1, dm->getNumAdopters())
                        << "Adopters should have one addition.";
    ASSERT_TRUE(dm->removeAdopter(ally->username))
                        << "Ally the adopter should have been removed.";
    ASSERT_EQ(numAdopters, dm->getNumAdopters())
                        << "Adopters should be back to normal amount.";
}

//This will test the read in adopter method
TEST_F(DatabaseManager_Test, READ_IN_ADOPTER) {
    Adopter *js = new Adopter;
    vector<int> likedPets;
    likedPets.push_back(1);
    vector<int> dislikedPets;
    dislikedPets.push_back(2);
    ASSERT_EQ(numAdopters, dm->getNumAdopters())
                    << "This should never be false";
    js->username = "Justin Smith";
    js->likedPetIds = likedPets;
    js->dislikedPetIds = dislikedPets;
    js->prefSpecies = "Cat";
    js->prefSpeciesReq = true;
    js->prefBreed = "Butter";
    js->prefBreedReq = true;
    js->prefAge = 2;
    js->prefAgeReq = false;
    js->prefWeight = 10.0;
    js->prefWeightReq = false;
    js->prefColor = "Silver";
    js->prefColorReq = true;
    js->prefHypoallergenic = true;
    js->prefHypoallergenicReq = false;
    js->prefSex = "Female";
    js->prefSexReq = true;
    js->bio = "";

    ASSERT_TRUE(dm->addAdopter(js, "ButterIsGorgeous72"))
                        << "Justin Smith the adopter was not added.";
    ASSERT_EQ(numAdopters+1, dm->getNumAdopters())
                        << "Adopters should have one addition.";
    ASSERT_EQ(js->username, dm->readInAdopter("Justin Smith", "ButterIsGorgeous72")->username)
                        << "Read in Adopter should return the same adopter";
    ASSERT_TRUE(dm->removeAdopter(js->username))
                        << "Justin Smith the adopter should have been removed.";
}

//This will test updating adopter information
TEST_F(DatabaseManager_Test, UPDATE_ADOPTER) {
    Adopter *dan = new Adopter;
    vector<int> likedPets;
    likedPets.push_back(1);
    vector<int> dislikedPets;
    dislikedPets.push_back(0);
    dan->username = "Danny";
    dan->likedPetIds = likedPets;
    dan->dislikedPetIds = dislikedPets;
    dan->prefSpecies = "Dog";
    dan->prefSpeciesReq = true;
    dan->prefBreed = "Shorkie";
    dan->prefBreedReq = false;
    dan->prefAge = 3;
    dan->prefAgeReq = false;
    dan->prefWeight = 2.0;
    dan->prefWeightReq = false;
    dan->prefColor = "Brown";
    dan->prefColorReq = false;
    dan->prefHypoallergenic = true;
    dan->prefHypoallergenicReq = true;
    dan->prefSex = "Female";
    dan->prefSexReq = false;
    dan->bio = "";
    ASSERT_TRUE(dm->addAdopter(dan, "Password"))
                        << "dan the adopter was not added.";
    dan->prefSpecies = "Cat";
    dan->prefSpeciesReq = false;
    dan->prefBreed = "Bengal";
    dan->prefBreedReq = true;
    dan->prefAge = 4;
    dan->prefAgeReq = true;
    dan->prefWeight = 3.5;
    dan->prefWeightReq = true;
    dan->prefColor = "Orange";
    dan->prefColorReq = true;
    dan->prefHypoallergenic = false;
    dan->prefHypoallergenicReq = false;
    dan->prefSex = "Male";
    dan->prefSexReq = true;
    dan->bio = "Hi";
    ASSERT_TRUE(dm->updateAdopter(dan));
    ASSERT_EQ("Cat", dm->readInAdopter(dan->username, "Password")->prefSpecies)
                        << "The adopter changes should be saved.";
    ASSERT_EQ(false, dm->readInAdopter(dan->username, "Password")->prefSpeciesReq)
                        << "The adopter changes should be saved.";
    ASSERT_EQ("Bengal", dm->readInAdopter(dan->username, "Password")->prefBreed)
                        << "The adopter changes should be saved.";
    ASSERT_EQ(true, dm->readInAdopter(dan->username, "Password")->prefBreedReq)
                        << "The adopter changes should be saved.";
    ASSERT_EQ(dan->prefAge, dm->readInAdopter(dan->username, "Password")->prefAge)
                        << "The adopter changes should be saved.";
    ASSERT_EQ(true, dm->readInAdopter(dan->username, "Password")->prefAgeReq)
                        << "The adopter changes should be saved.";
    ASSERT_EQ(3.5, dm->readInAdopter(dan->username, "Password")->prefWeight)
                        << "The adopter changes should be saved.";
    ASSERT_EQ(true, dm->readInAdopter(dan->username, "Password")->prefWeightReq)
                        << "The adopter changes should be saved.";
    ASSERT_EQ("Orange", dm->readInAdopter(dan->username, "Password")->prefColor)
                        << "The adopter changes should be saved.";
    ASSERT_EQ(true, dm->readInAdopter(dan->username, "Password")->prefColorReq)
                        << "The adopter changes should be saved.";
    ASSERT_EQ(false, dm->readInAdopter(dan->username, "Password")->prefHypoallergenic)
                        << "The adopter changes should be saved.";
    ASSERT_EQ(false, dm->readInAdopter(dan->username, "Password")->prefHypoallergenicReq)
                        << "The adopter changes should be saved.";
    ASSERT_EQ("Male", dm->readInAdopter(dan->username, "Password")->prefSex)
                        << "The adopter changes should be saved.";
    ASSERT_EQ(true, dm->readInAdopter(dan->username, "Password")->prefSexReq)
                        << "The adopter changes should be saved.";
    ASSERT_EQ("Hi", dm->readInAdopter(dan->username, "Password")->bio)
                        << "The adopter changes should be saved.";

    ASSERT_TRUE(dm->removeAdopter(dan->username))
                        << "dan the adopter should have been removed.";
}

//*********************************************************************************************************************
//*****************************************TESTS FOR DATABASE ADOPTEES*************************************************
//*********************************************************************************************************************
//This test will test the basic addition and removal of an adoptee
TEST_F(DatabaseManager_Test, ADD_AND_REMOVE_ADOPTEE) {
    Adoptee *pt = new Adoptee;
    vector<int> ownedPetIds;
    ownedPetIds.push_back(1);
    pt->username = "Pet Tinder";
    pt->shelter = "Claws n' Paws";
    pt->ownedPetIds = ownedPetIds;
    pt->bio = "";

    ASSERT_TRUE(dm->addAdoptee(pt, "Password"))
                        << "Pet Tinder the adoptee was not added.";
    ASSERT_EQ(numAdoptees+1, dm->getNumAdoptees())
                        << "Adoptees should have one addition.";
    ASSERT_TRUE(dm->removeAdoptee(pt->username))
                        << "Pet Tinder the adoptee should have been removed.";
    ASSERT_EQ(numAdoptees, dm->getNumAdoptees())
                        << "Adoptees should be back to normal amount.";
}

//This will test adding two users with the same information to see.
TEST_F(DatabaseManager_Test, ADD_SAME_ADOPTEE_INFO) {
    Adoptee *apee = new Adoptee;
    Adoptee *copy = new Adoptee;
    vector<int> ownedPetIds;
    ownedPetIds.push_back(1);
    apee->username = "Monke";
    apee->shelter = "Monke";
    apee->ownedPetIds = ownedPetIds;
    copy->username = "Monke";
    copy->shelter = "Monke";
    copy->ownedPetIds = ownedPetIds;
    copy->bio = "";

    ASSERT_TRUE(dm->addAdoptee(apee, "Monke"))
                        << "Apee the adoptee was not added.";
    ASSERT_EQ(numAdoptees+1, dm->getNumAdoptees())
                        << "Adoptees should have one addition.";
    ASSERT_FALSE(dm->addAdoptee(copy, "Monke"))
                        << "Copy of apee the adoptee was added.";
    ASSERT_TRUE(dm->removeAdoptee(apee->username))
                        << "Apee the adoptee should have been removed.";
    ASSERT_EQ(numAdoptees, dm->getNumAdoptees())
                        << "Adoptees should be back to normal amount.";
}

//This will test adding an adoptee with almost empty information
TEST_F(DatabaseManager_Test, ADD_EMPTY_ADOPTEE) {
    Adoptee *peta = new Adoptee;
    vector<int> ownedPetIds;
    ownedPetIds.push_back(1);
    peta->username = "";
    peta->shelter = "";
    peta->ownedPetIds = ownedPetIds;
    peta->bio = "";

    ASSERT_TRUE(dm->addAdoptee(peta, "Password"))
                        << "Peta the adoptee was not added.";
    ASSERT_EQ(numAdoptees+1, dm->getNumAdoptees())
                        << "Adoptees should have one addition.";
    ASSERT_TRUE(dm->removeAdoptee(peta->username))
                        << "Peta the adoptee should have been removed.";
    ASSERT_EQ(numAdoptees, dm->getNumAdoptees())
                        << "Adoptees should be back to normal amount.";
}

//This will test adding and removing a nonexistent adoptee in the table
TEST_F(DatabaseManager_Test, ADD_NONEXISTENT_ADOPTEE) {
    Adoptee *happinessWhileWorkingOnCSWork = new Adoptee;
    ASSERT_FALSE(dm->removeAdoptee(happinessWhileWorkingOnCSWork->username))
                        << "If not false, delete did not work.";
    ASSERT_EQ(numAdoptees, dm->getNumAdoptees())
                        << "Adoptees should be back to normal amount.";
}

//This will add an adoptee with weird infromation that probably should not be accepted
TEST_F(DatabaseManager_Test, ADD_WEIRD_ADOPTEE) {
    Adoptee *fr = new Adoptee;
    vector<int> ownedPetIds;
    ownedPetIds.push_back(1);
    fr->username = "SuperDuperClimax1000";
    fr->shelter = "ShelterDeezNutz Goteem";
    fr->ownedPetIds = ownedPetIds;
    fr->bio = "";

    ASSERT_TRUE(dm->addAdoptee(fr, ""))
                        << "The adoptee was not added.";
    ASSERT_EQ(numAdoptees+1, dm->getNumAdoptees())
                        << "Adoptees should have one addition.";
    ASSERT_TRUE(dm->removeAdoptee(fr->username))
                        << "The adoptee should have been removed.";
    ASSERT_EQ(numAdoptees, dm->getNumAdoptees())
                        << "Adoptees should be back to normal amount.";
}

//This will test the read in adoptee method
TEST_F(DatabaseManager_Test, READ_IN_ADOPTEE) {
    Adoptee *butter = new Adoptee;
    vector<int> ownedPetIds;
    ownedPetIds.push_back(1);
    butter->username = "KoolKat12";
    butter->shelter = "Matchmaker App";
    butter->ownedPetIds = ownedPetIds;
    butter->bio = "";

    ASSERT_TRUE(dm->addAdoptee(butter, "ButterIsGorgeous72"))
                        << "Butter the adoptee was not added.";
    ASSERT_EQ(numAdoptees+1, dm->getNumAdoptees())
                        << "Adoptees should have one addition.";
    ASSERT_EQ(butter->username, dm->readInAdoptee("KoolKat12", "ButterIsGorgeous72")->username)
                        << "Read in Adoptee should return the same adoptee";
    ASSERT_TRUE(dm->removeAdoptee(butter->username))
                        << "Butter the adoptee should have been removed.";
}

//This will test the update adoptee method
TEST_F(DatabaseManager_Test, UPDATE_ADOPTEE) {
    Adoptee *pt = new Adoptee;
    vector<int> ownedPetIds;
    ownedPetIds.push_back(1);
    pt->username = "Pet Tinder";
    pt->shelter = "Claws n' Paws";
    pt->ownedPetIds = ownedPetIds;
    pt->bio = "";
    ASSERT_TRUE(dm->addAdoptee(pt, "Password"))
                        << "Pet Tinder the adoptee was not added.";
    pt->bio = "Bio";
    ASSERT_TRUE(dm->updateAdoptee(pt));
    ASSERT_EQ("Pet Tinder", dm->readInAdoptee(pt->username, "Password")->username)
                        << "The adopter changes should be saved.";
    ASSERT_EQ("Bio", dm->readInAdoptee(pt->username, "Password")->bio)
                        << "The adopter changes should be saved.";
    ASSERT_TRUE(dm->removeAdoptee(pt->username))
                        << "Pet Tinder the adoptee should have been removed.";
}

//*********************************************************************************************************************
//*****************************************OTHER TESTS FOR DATABASE****************************************************
//*********************************************************************************************************************
//This will test the important and testable parts of the messages database. It is less extensive since most
//of the fields of the Conversation are other adopters and adoptees.
TEST_F(DatabaseManager_Test, ADD_REMOVE_AND_READ_IN_MESSAGES){
    Pet *bear = new Pet;
    bear->name = "Trinket";
    bear->species = "Large";
    bear->breed = "Fuzzy";
    bear->age = 6;
    bear->weight = 200.0;
    bear->color = "Brown";
    bear->hypoallergenic = false;
    bear->sex = "Male";
    bear->bio = "The companion to Lady Vex'ahlia, Mistress of the Grey Hunt. Accompanying her,"
               "Trinket has seen a great many adventure and receieved special treatment as the"
               "bear that aided Vox Machina through several adventures that would save all of Tal"
               "Dore. THis is probably the most well-known bear in the world, for good reason. ";
    bear->image = "";
    ASSERT_TRUE(dm->addPet(bear))
                        << "Bear should have been added.";

    Adopter *dan = new Adopter;
    vector<int> likedPets;
    likedPets.push_back(1);
    vector<int> dislikedPets;
    dislikedPets.push_back(0);
    ASSERT_EQ(numAdopters, dm->getNumAdopters())
                    << "This should never be false";
    dan->username = "Arthur Ayers";
    dan->likedPetIds = likedPets;
    dan->dislikedPetIds = dislikedPets;
    dan->prefSpecies = "Dog";
    dan->prefSpeciesReq = true;
    dan->prefBreed = "Shorkie";
    dan->prefBreedReq = false;
    dan->prefAge = 3;
    dan->prefAgeReq = false;
    dan->prefWeight = 2.0;
    dan->prefWeightReq = false;
    dan->prefColor = "Brown";
    dan->prefColorReq = false;
    dan->prefHypoallergenic = true;
    dan->prefHypoallergenicReq = true;
    dan->prefSex = "Female";
    dan->prefSexReq = false;
    dan->bio = "Watch my spelunky 2 speedruns ^.^";
    ASSERT_TRUE(dm->addAdopter(dan, "Password"))
                        << "dan the adopter was not added.";

    Adoptee *pt = new Adoptee;
    vector<int> ownedPetIds;
    ownedPetIds.push_back(bear->id);
    pt->username = "LC";
    pt->shelter = "Lafayette College";
    pt->ownedPetIds = ownedPetIds;
    pt->bio = "";
    ASSERT_TRUE(dm->addAdoptee(pt, "LafayetteIsBetterThanLehigh"))
                        << "LC the adoptee was not added.";

    Conversation *ct = new Conversation;
    ct->usernameAdopter = dan->username;
    ct->usernameAdoptee = pt->username;
    ct->petId = bear->id;
    QString message = QString::fromStdString("Sup Bitch");
    ct->messages.push_back(message);
    ASSERT_TRUE(dm->addConversation(ct))
                        << "Conversation ct was not added :(";

    ASSERT_EQ(ct->usernameAdopter, dm->readInConversation(ct->usernameAdopter, ct->petId)->usernameAdopter)
                        << "Read in Conversation should have the same usernames.";
    ASSERT_EQ(ct->usernameAdoptee, dm->readInConversation(ct->usernameAdopter, ct->petId)->usernameAdoptee)
                        << "Read in Conversation should have the same usernames.";
    QString message2 = QString::fromStdString("|Bitches");
    ct->messages.push_back(message2);
    dm->updateConversation(ct);
    ASSERT_EQ(ct->usernameAdopter, dm->readInConversation(ct->usernameAdopter, ct->petId)->usernameAdopter)
                        << "Read in Conversation should have the same usernames.";
    ASSERT_EQ(ct->usernameAdoptee, dm->readInConversation(ct->usernameAdopter, ct->petId)->usernameAdoptee)
                        << "Read in Conversation should have the same usernames.";
    ASSERT_TRUE(dm->removeConversation(ct->usernameAdopter, ct->petId))
                        << "Conversation should be removed.";
    ASSERT_TRUE(dm->removePet(bear->id))
                        << "Bear should have been removed.";
    ASSERT_TRUE(dm->removeAdoptee(pt->username))
                        << "Pet Tinder the adoptee should have been removed.";
    ASSERT_TRUE(dm->removeAdopter(dan->username))
                        << "dan the adopter should have been removed.";
}

//This will test the other method dealing with usernames across all users, not just adopters and adoptees
TEST_F(DatabaseManager_Test, TEST_SAME_USERNAMES){
    Adopter *dumbass = new Adopter;
    vector<int> likedPets;
    likedPets.push_back(1);
    vector<int> dislikedPets;
    dislikedPets.push_back(0);
    dumbass->username = "Standard Username";
    dumbass->likedPetIds = likedPets;
    dumbass->dislikedPetIds = dislikedPets;
    dumbass->prefSpecies = "Dog";
    dumbass->prefSpeciesReq = true;
    dumbass->prefBreed = "Shorkie";
    dumbass->prefBreedReq = false;
    dumbass->prefAge = 3;
    dumbass->prefAgeReq = false;
    dumbass->prefWeight = 2.0;
    dumbass->prefWeightReq = false;
    dumbass->prefColor = "Brown";
    dumbass->prefColorReq = false;
    dumbass->prefHypoallergenic = true;
    dumbass->prefHypoallergenicReq = true;
    dumbass->prefSex = "Female";
    dumbass->prefSexReq = false;
    dumbass->bio = "My name is Alex";
    ASSERT_TRUE(dm->addAdopter(dumbass, "Password"))
                        << "Dumbass the adopter was not added.";
    ASSERT_TRUE(dm->isUsernameTaken(dumbass->username))
                        << "The username should be taken.";

    Adoptee *coolass = new Adoptee;
    vector<int> ownedPetIds;
    ownedPetIds.push_back(1);
    coolass->username = "Less Standard Username";
    coolass->shelter = "Claws n' Paws";
    coolass->ownedPetIds = ownedPetIds;
    coolass->bio = "My name is not Alex";
    ASSERT_FALSE(dm->isUsernameTaken(coolass->username))
                        << "The username should not be taken yet.";
    ASSERT_TRUE(dm->addAdoptee(coolass, "Password"))
                        << "Coolass the adoptee was not added.";
    ASSERT_TRUE(dm->isUsernameTaken(coolass->username))
                        << "The username should be taken now.";
    ASSERT_TRUE(dm->removeAdoptee(coolass->username))
                        << "Coolass the adoptee should have been removed.";
    ASSERT_TRUE(dm->removeAdopter(dumbass->username))
                        << "Dumbass the adopter should have been removed.";
}

//*********************************************************************************************************************
//*********************************************************************************************************************
//*****************************************TESTS FOR MATCHMAKER********************************************************
//*********************************************************************************************************************
//*********************************************************************************************************************
//This test will be a basic test for Matchmaker
TEST_F(Matchmaking_Test, SORT_AND_ARRANGE_PREFS_TESTS){
    vector<string> speciesR;
    vector<string> breedR;
    vector<string> colorR;
    vector<int> ageR;
    vector<double> weightR;

    speciesR.push_back("Cat");
    speciesR.push_back("Dog");
    speciesR.push_back("Duck");

    breedR.push_back("Bengal");
    breedR.push_back("Domestic");
    breedR.push_back("Shih Tzu");
    breedR.push_back("Shorkie");

    colorR.push_back("Brown");
    colorR.push_back("Orange");
    colorR.push_back("White");

    ageR.push_back(1);
    ageR.push_back(4);
    ageR.push_back(7);

    weightR.push_back(8.4);
    weightR.push_back(9.0);
    weightR.push_back(12.5);

    mm->sortPrefs();
    cout << mm->total.species.size() << endl;

    ASSERT_EQ(speciesR, mm->total.species);
    ASSERT_EQ(breedR, mm->total.breeds);
    ASSERT_EQ(colorR, mm->total.colors);
    ASSERT_EQ(ageR, mm->total.ages);
    ASSERT_EQ(weightR, mm->total.weights);
}

//First Test for the matchmaking system based on the user's preferences
TEST_F(Matchmaking_Test, MATCHMAKER_TEST_PREFS){
    //adopter danny already liked/disliked 1 pet, so he should still have all but one pet to see.
    ASSERT_EQ(dm->getNumPets()-1, mm->DatabaseInterface(dan).size());
    ASSERT_EQ(1, mm->DatabaseInterface(alex).size());
    ASSERT_EQ(0, mm->DatabaseInterface(ally).size());
    ASSERT_EQ(0, mm->DatabaseInterface(addy).size());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
