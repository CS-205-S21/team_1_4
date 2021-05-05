#include <iostream>
#include "gtest/gtest.h"
#include "../matchmaking/matchmaker.h"
#include "../databasemanager/databasemanager.h"

// TO DO: EDIT TO MATCH CURRENT DATABSE PARAMETERS
// TO DO: EDIT SO THAT IT MIGHT BE ABLE TO WORK WITH OTHER THINGS IN THE DATABASE

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
    }

    virtual void TearDown() {
        delete mm;
    }

    Matchmaker *mm;
};

//*********************************************************************************************************************
//*****************************************TESTS FOR DATABASE PETS*****************************************************
//*********************************************************************************************************************
//This test is assuming that this is being run before anything else was added
//to the database.
TEST_F(DatabaseManager_Test, ADD_AND_REMOVE_PET) {
    Pet bear;
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pet should have no additions.";
    bear.name = "Trinket";
    bear.species = "Large";
    bear.breed = "Fuzzy";
    bear.age = 6;
    bear.weight = 200.0;
    bear.color = "Brown";
    bear.hypoallergenic = false;
    bear.sex = "Male";
    bear.bio = "The companion to Lady Vex'ahlia, Mistress of the Grey Hunt. Accompanying her,"
               "Trinket has seen a great many adventure and receieved special treatment as the"
               "bear that aided Vox Machina through several adventures that would save all of Tal"
               "Dore. THis is probably the most well-known bear in the world, for good reason. ";
    ASSERT_TRUE(dm->addPet(bear))
                        << "Bear should have been added.";
    ASSERT_EQ(numPets+1, dm->getNumPets())
                    << "Pets should have one addition.";
    ASSERT_TRUE(dm->removePet(bear.id))
                        << "Bear should have been removed.";
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should be back to original size.";
}

//This will not only test to make sure that the database can handle spaces between entries,
//but will also test to make sure that two pets, with the same id will not both be added.
TEST_F(DatabaseManager_Test, ADD_MULTIPLE_IDS) {
    Pet animal;
    Pet animalA;
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should have no additions.";
    animal.id = numPets+1;
    animal.name = "Jyken Deydhall";
    animal.species = "Human";
    animal.breed = "Conquest Paladin";
    animal.age = 28;
    animal.weight = 190.0;
    animal.color = "Pale Orange/Pink";
    animal.hypoallergenic = false;
    animal.sex = "Male";
    animal.bio = "The champion to The Mockery, Jyken Deydhall found his demis to the dracolich"
                 "commanded by the notorious undead king. He has since woken up, with a renewed"
                 "vow and motivation to seek out his brother's murderer, and his mentor, Enrico"
                 "Brando, the leader of the Diashad order of Paladins. Jyken has sworn to make"
                 "Enrico wish he was never alive.";
    ASSERT_TRUE(dm->addPet(animal))
                    << "Animal should have been added.";

    animalA.id = animal.id;
    animalA.name = "Red Valley Mist";
    animalA.species = "Tabaxi";
    animalA.breed = "Mercy Monk";
    animalA.age = 22;
    animalA.weight = 120.0;
    animalA.color = "Light Orange";
    animalA.hypoallergenic = true;
    animalA.sex = "Female";
    animalA.bio = "This monk has studied under the tutelage of Master Ba, a monk that has adopted"
                  "Mist when he was very young. Mist has almost no memories of his childhood, but"
                  "trusts the word of his master that he does not need to know anything. However,"
                  "master Ba had mysteriously passed away, leaving Mist to his own devices. He then"
                  "went on to discover his own path, acting as judge of the mortal world and seeking"
                  "to learn who he is.";
    ASSERT_TRUE(dm->addPet(animalA))
                << "AnimalA should have an id overwritten and added anyway";
    ASSERT_TRUE(dm->removePet(animal.id))
                << "Animal should have been removed.";
    ASSERT_TRUE(dm->removePet(animalA.id))
                << "AnimalA should have been removed.";
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should be back to the original number.";
}

//This will test to see if you can add a pet with almost empty parameters, then test to see if
//it works with empty parameters, but with a non-empty id.
TEST_F(DatabaseManager_Test, ADD_EMPTY_PET) {
    Pet frog;
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should have no additions";
    ASSERT_FALSE(dm->addPet(frog));

    frog.name = "";
    frog.species = "";
    frog.breed = "";
    frog.age = 0;
    frog.weight = 0.0;
    frog.color = "";
    frog.hypoallergenic = false;
    frog.sex = "";
    frog.bio = "";

    ASSERT_TRUE(dm->addPet(frog))
                    << "Pets should accept parameters if there are some non-applicable information.";
    ASSERT_TRUE(dm->removePet(frog.id))
                    << "Frog should be deleted.";
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should be back to the original number.";
}

//Try to remove a pet that isn't in the table
TEST_F(DatabaseManager_Test, REMOVE_NOTHING) {
    Pet nonexistence;
    nonexistence.id = -1;
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should have no additions.";
    ASSERT_FALSE(dm->removePet(nonexistence.id))
                << "You cannot remove what does not exist.";
}

//This will test to see if you can add a pet with weird data such as a negative id number
TEST_F(DatabaseManager_Test, WEIRD_DATA) {
    Pet animal;
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should have normal amount of pets";
    animal.id = -1;
    animal.name = "Rdame Ylepse";
    animal.species = "Updog";
    animal.breed = "Sawcawn";
    animal.age = -9;
    animal.weight = -4;
    animal.color = "Spotted";
    animal.hypoallergenic = true;
    animal.sex = "Non-Binary";
    animal.bio = "N/A";
    ASSERT_FALSE(dm->addPet(animal))
                    << "Pets should not accept parameters with weird information";
    //just in case it was not removed yet
    dm->removePet(animal.id);
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should now have the original amout of pets";
}

//This will test the search method for database manager
TEST_F(DatabaseManager_Test, FIND_PETS) {
    Pet pika;
    Pet tepi;
    Pet sniv;
    Pet osha;

    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should have no additions";
    pika.name = "Pikachu";
    pika.species = "Mouse";
    pika.breed = "Brave";
    pika.age = 12;
    pika.weight = 19.0;
    pika.color = "Yellow";
    pika.hypoallergenic = false;
    pika.sex = "Male";
    pika.bio = "Pikachu is an electric type pokemon, probably best known as the companion to"
               "Ash Ketchum, or Red, who is known as the worl'd greatest Pokemon trainer. "
               "In the stories, Pikachu was Ash's first pokemon, and though their relationship"
               "was rocky at first, they grew to be the closest of friends and swore to become the"
               "very best like no one ever was together.";
    ASSERT_TRUE(dm->addPet(pika))
                    << "Pets should now contain only 1 addition";

    tepi.name = "Tepig";
    tepi.species = "Pig";
    tepi.breed = "Humble";
    tepi.age = 6;
    tepi.weight = 22.5;
    tepi.color = "Orange";
    tepi.hypoallergenic = true;
    tepi.sex = "Male";
    tepi.bio = "Tepig is a fire type pig-like pokemon that is a starter for generation 5. Tepig "
               "also joined Ash Ketchum in his quest to become the ultimate pokemon trainer, but"
               "tepig is objectively one of the best starters of all pokemon. The final evolution"
               "is Emboar.";
    ASSERT_TRUE(dm->addPet(tepi))
                    << "Pets should now contain only 2 additions";

    sniv.name = "Snivy";
    sniv.species = "Snake";
    sniv.breed = "Shy";
    sniv.age = 8;
    sniv.weight = 12.2;
    sniv.color = "Green";
    sniv.hypoallergenic = false;
    sniv.sex = "Female";
    sniv.bio = "Snivy is a grass snake, and juts like the other gen 5 starters, has also joined"
               "Ash for a brief period. Snivy can evolve into the graceful Serperior, the superior"
               "grass serpent that can slither around and capture its foes with its grassy entanglement."
               "Snivy is a beautiful pokemon with great evolutions for a fresh design in generation 5.";
    dm->addPet(sniv);
    ASSERT_TRUE(dm->addPet(sniv))
                    << "Pets should now contain only 3 additions";

    osha.name = "Oshawott";
    osha.species = "Turtle?";
    osha.breed = "Reckless";
    osha.age = 5;
    osha.weight = 21.8;
    osha.color = "Blue and White";
    osha.hypoallergenic = true;
    osha.sex = "Male";
    osha.bio = "Oshawott is a generation 5 starter, who also breifly joined Ash Ketchum's adventure,"
               "but is another yet amazing starter. I do not know what type of animal Oshawott resembles,"
               "but it might be some sort of turtle. Oshawott has some sort of boomerang weapon that "
               "can come off its body, but evolves into Samurott, a large and intimidating pokemon with"
               "the wespons from its first evolution adorning its legs. Truly Generation 5 was a masterpiece.";
    ASSERT_TRUE(dm->addPet(osha))
                    << "Pets should now contain only 4 additions";

    ASSERT_EQ(&pika, dm->findPet(pika.id));
    ASSERT_EQ(&tepi, dm->findPet(tepi.id));
    ASSERT_EQ(&sniv, dm->findPet(sniv.id));
    ASSERT_EQ(&osha, dm->findPet(osha.id));

    ASSERT_EQ(numPets+4, dm->getNumPets())
                    << "Pets should have all new pokemon";
    ASSERT_TRUE(dm->removePet(pika.id))
                    << "Pika should be deleted.";
    ASSERT_EQ(numPets+3, dm->getNumPets())
                    << "Pets should have three pokemon";
    ASSERT_TRUE(dm->removePet(tepi.id))
                    << "Tepi should be deleted.";
    ASSERT_EQ(numPets+2, dm->getNumPets())
                    << "Pets should have two pokemon";
    ASSERT_TRUE(dm->removePet(sniv.id))
                    << "Sniv should be deleted.";
    ASSERT_EQ(numPets+1, dm->getNumPets())
                    << "Pets should have one pokemon";
    ASSERT_TRUE(dm->removePet(osha.id))
                    << "Osha should be deleted.";
    ASSERT_EQ(numPets, dm->getNumPets())
                    << "Pets should be back to original number";
}

//*********************************************************************************************************************
//*****************************************TESTS FOR DATABASE Adopters*************************************************
//*********************************************************************************************************************


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
    return 0;
}
