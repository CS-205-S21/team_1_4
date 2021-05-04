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
    }

    virtual void TearDown() {
        delete dm;
    }

    DatabaseManager *dm;
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

//This test is assuming that this is being run before anything else was added
//to the database.
TEST_F(DatabaseManager_Test, ADD_AND_REMOVE_PET) {
    Pet bear;
    ASSERT_EQ(0, dm->getNumPets())
                    << "Pets should be empty";
    bear.id = 1;
    bear.name = "Trinket";
    bear.species = "Large";
    bear.breed = "Fuzzy";
    bear.age = 6;
    bear.weight = 200;
    bear.color = "Brown";
    bear.hypoallergenic = false;
    bear.sex = "Male";
    bear.bio = "The companion to Lady Vex'ahlia, Mistress of the Grey Hunt. Accompanying her,"
               "Trinket has seen a great many adventure and receieved special treatment as the"
               "bear that aided Vox Machina through several adventures that would save all of Tal"
               "Dore. THis is probably the most well-known bear in the world, for good reason. ";
    dm->addPet(bear);
    ASSERT_EQ(1, dm->getNumPets())
                    << "Pets should now have one pet";
    dm->removePet(bear);
    ASSERT_EQ(0, dm->getNumPets())
                    << "Pets should be empty";
}

//This will not only test to make sure that the database can handle spaces between entries,
//but will also test to make sure that two pets, with the same id will not both be added.
TEST_F(DatabaseManager_Test, ADD_MULTIPLE_IDS) {
    Pet animal;
    Pet animalA;
    ASSERT_EQ(0, dm->getNumPets())
                    << "Pets should be empty";
    animal.id = 1;
    animal.name = "Jyken Deydhall";
    animal.species = "Human";
    animal.breed = "Conquest Paladin";
    animal.age = 28;
    animal.weight = 190;
    animal.color = "Pale Orange/Pink";
    animal.hypoallergenic = false;
    animal.sex = "Male";
    animal.bio = "The champion to The Mockery, Jyken Deydhall found his demis to the dracolich"
                 "commanded by the notorious undead king. He has since woken up, with a renewed"
                 "vow and motivation to seek out his brother's murderer, and his mentor, Enrico"
                 "Brando, the leader of the Diashad order of Paladins. Jyken has sworn to make"
                 "Enrico wish he was never alive.";
    dm->addPet(animal);
    ASSERT_EQ(1, dm->getNumPets())
                    << "Pets should now contain only 1";

    animalA.id = 1;
    animalA.name = "Red Valley Mist";
    animalA.species = "Tabaxi";
    animalA.breed = "Mercy Monk";
    animalA.age = 22;
    animalA.weight = 120;
    animalA.color = "Light Orange";
    animalA.hypoallergenic = true;
    animalA.sex = "Female";
    animalA.bio = "This monk has studied under the tutelage of Master Ba, a monk that has adopted"
                  "Mist when he was very young. Mist has almost no memories of his childhood, but"
                  "trusts the word of his master that he does not need to know anything. However,"
                  "master Ba had mysteriously passed away, leaving Mist to his own devices. He then"
                  "went on to discover his own path, acting as judge of the mortal world and seeking"
                  "to learn who he is.";
    dm->addPet(animalA);
    ASSERT_EQ(1, dm->getNumPets())
                    << "Pets should still contain only 1";

    dm->removePet(animal);
    ASSERT_EQ(0, dm->getNumPets())
                    << "Pets should be empty";
}

//This will test to see if you can add a pet with almost empty parameters, then test to see if
//it works with empty parameters, but with a non-empty id.
TEST_F(DatabaseManager_Test, ADD_EMPTY_PET) {
    Pet frog;
    ASSERT_EQ(0, dm->getNumPets())
                    << "Pets should be empty";
    dm->addPet(frog);
    ASSERT_EQ(0, dm->getNumPets())
                    << "Pets should not have any pets";
    frog.id = 0;
    frog.name = "";
    frog.species = "";
    frog.breed = "";
    frog.age = 0;
    frog.weight = 0;
    frog.color = "";
    frog.hypoallergenic = false;
    frog.sex = "";
    frog.bio = "";
    dm->addPet(frog);
    ASSERT_EQ(1, dm->getNumPets())
                    << "Pets should accept parameters if there are some non-applicable information";
    dm->removePet(frog);
    ASSERT_EQ(0, dm->getNumPets())
                    << "Pets should now be empty";
}

//Try to remove a pet that isn't in the table
TEST_F(DatabaseManager_Test, REMOVE_NOTHING) {
    Pet nonexistence;
    ASSERT_EQ(0, dm->getNumPets())
                    << "Pets should be empty";
    dm->removePet(nonexistence);
    ASSERT_EQ(0, dm->getNumPets())
                    << "Pets should be empty";
}

//This will test to see if you can add a pet with almost empty parameters, then test to see if
//it works with empty parameters, but with a non-empty id.
TEST_F(DatabaseManager_Test, WEIRD_DATA) {
    Pet animal;
    ASSERT_EQ(0, dm->getNumPets())
                    << "Pets should be empty";
    animal.id = -1;
    animal.name = "Rdame Ylepse";
    animal.species = "Updog";
    animal.breed = "Sawcawn";
    animal.age = -9;
    animal.weight = 4.2;
    animal.color = "Spotted";
    animal.hypoallergenic = true;
    animal.sex = "Non-Binary";
    animal.bio = "N/A";
    dm->addPet(animal);
    ASSERT_EQ(0, dm->getNumPets())
                    << "Pets should not accept parameters with weird information";
    //just in case it was not removed yet
    dm->removePet(animal);
    ASSERT_EQ(0, dm->getNumPets())
                    << "Pets should now be empty";
}

//This will test to see if you can add a pet with almost empty parameters, then test to see if
//it works with empty parameters, but with a non-empty id.
TEST_F(DatabaseManager_Test, FIND_PETS) {
    Pet pika;
    Pet tepi;
    Pet sniv;
    Pet osha;

    ASSERT_EQ(0, dm->getNumPets())
                    << "Pets should be empty";
    pika.id = 0;
    pika.name = "Pikachu";
    pika.species = "Mouse";
    pika.breed = "Brave";
    pika.age = 12;
    pika.weight = 19;
    pika.color = "Yellow";
    pika.hypoallergenic = false;
    pika.sex = "Male";
    pika.bio = "Pikachu is an electric type pokemon, probably best known as the companion to"
               "Ash Ketchum, or Red, who is known as the worl'd greatest Pokemon trainer. "
               "In the stories, Pikachu was Ash's first pokemon, and though their relationship"
               "was rocky at first, they grew to be the closest of friends and swore to become the"
               "very best like no one ever was together.";
    dm->addPet(pika);
    ASSERT_EQ(1, dm->getNumPets())
                    << "Pets should now contain only 1";

    tepi.id = 1;
    tepi.name = "Tepig";
    tepi.species = "Pig";
    tepi.breed = "Humble";
    tepi.age = 6;
    tepi.weight = 22;
    tepi.color = "Orange";
    tepi.hypoallergenic = true;
    tepi.sex = "Male";
    tepi.bio = "Tepig is a fire type pig-like pokemon that is a starter for generation 5. Tepig "
               "also joined Ash Ketchum in his quest to become the ultimate pokemon trainer, but"
               "tepig is objectively one of the best starters of all pokemon. The final evolution"
               "is Emboar.";
    dm->addPet(tepi);
    ASSERT_EQ(2, dm->getNumPets())
                    << "Pets should now contain only 2";

    sniv.id = 2;
    sniv.name = "Snivy";
    sniv.species = "Snake";
    sniv.breed = "Shy";
    sniv.age = 8;
    sniv.weight = 12;
    sniv.color = "Green";
    sniv.hypoallergenic = false;
    sniv.sex = "Female";
    sniv.bio = "Snivy is a grass snake, and juts like the other gen 5 starters, has also joined"
               "Ash for a brief period. Snivy can evolve into the graceful Serperior, the superior"
               "grass serpent that can slither around and capture its foes with its grassy entanglement."
               "Snivy is a beautiful pokemon with great evolutions for a fresh design in generation 5.";
    dm->addPet(sniv);
    ASSERT_EQ(3, dm->getNumPets())
                    << "Pets should now contain only 3";

    osha.id = 3;
    osha.name = "Oshawott";
    osha.species = "Turtle?";
    osha.breed = "Reckless";
    osha.age = 5;
    osha.weight = 21;
    osha.color = "Blue and White";
    osha.hypoallergenic = true;
    osha.sex = "Male";
    osha.bio = "Oshawott is a generation 5 starter, who also breifly joined Ash Ketchum's adventure,"
               "but is another yet amazing starter. I do not know what type of animal Oshawott resembles,"
               "but it might be some sort of turtle. Oshawott has some sort of boomerang weapon that "
               "can come off its body, but evolves into Samurott, a large and intimidating pokemon with"
               "the wespons from its first evolution adorning its legs. Truly Generation 5 was a masterpiece.";
    dm->addPet(osha);
    ASSERT_EQ(4, dm->getNumPets())
                    << "Pets should now contain only 4";

    ASSERT_EQ(&pika, dm->findPet(0));
    ASSERT_EQ(&tepi, dm->findPet(1));
    ASSERT_EQ(&sniv, dm->findPet(2));
    ASSERT_EQ(&osha, dm->findPet(3));

    dm->removePet(osha);
    dm->removePet(sniv);
    dm->removePet(tepi);
    dm->removePet(pika);
    ASSERT_EQ(0, dm->getNumPets())
                    << "Pets should be empty";
}

int main(int argc, char **argv) {
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
    return 0;
}
