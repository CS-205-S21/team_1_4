![claws](https://user-images.githubusercontent.com/78805674/118567055-1d779480-b743-11eb-8f10-47420f1db017.png)

# Project: Claws n' Paws Matchmaking System!

This project will be a matchmaking system for potential adopters. They will be able to login, 
with a database containing their data, then view many profiles of pets stored in the
system’s database to find a pet that matches their preferences. Adoptees, or users defined by 
people who wish to put pets up for adoption, can edit their pets and also message adopters 
interested and who expressed interest in a pet.

It is difficult and time consuming to visit shelters and as a result, millions of pets are
not adopted and are euthanized every year. The problem lies in the lack of visitations to 
these shelters due to the inconvenience of travelling to these pet shelters, without having
a chance to know these pets. Especially with the covid-19 pandemic, it is harder than before to
travel to shelters for adoptions, leading to more pet euthanizations than before. 

**Things to note for this project:** 
1) Adopter refers to a user that specifies that they wish to adopt pets using the matchmaking system.
2) Adoptee refers to a user that wishes to put pets up for adoption. They cannot be both types of users.
3) This app is meant to be used as a short-term matchmaking system, for users who want to match with pets and message adoptees in the process of gettng a pet.
4) At first, since we do not have the backing of any shelters, we will be using sample pet data, which cannot be adopted since they are static. When we get backing of a shelter, this app will be more useful. 
5) We did not patent or trademark this name or any names associated with this project. We are currently non-profit and are not trying to gain a profit for this project. We did not use any outside code, other than created libraries like sort, or art we did not create ourselves. 
6) To view our project as either an adopter or adoptee, you can use the sample data below:
Adopter - username: "Kate" password: "123"
Adoptee - username: "Glue" password: "elmerselastic"
Adoptee - username: "Biggy" password: "Smalls"
Adoptee - username: "Brightly" password: "Townsie"

# Building and Running our System:
To build this system, just download our source code, as well as any database included with 
sqlite3 and our pictures of each pet. Then, make sure that the project builds, then run it from 
the main method of the GUI class. This will bring up the login screen 
from which the user can explore our app. 

# Files to Look Over
Before you look through the source code, to fully understand how our project works, you can
explore the documentation as described in each header file, but also presented within the 
other CODE_DOCUMENTATION.md file. From here, you can get a glance at each method within each class,
which also appears in the header file for each class. Each comment header descrbes the purpose 
of each method, and the title will exaplin what class the methods appear inside. There are two
classes, the database and the matchmaker, as the only other classes are the unit test class 
and the GUI class, both of which do not need extensive documentation, since their purposes are 
relatively simple and self-explanatory. 

The other file to look over is our TEST_DOCUMENTATION.md file, as desribed in the testing 
documentation read file. This gives a better overview of the way that we tested, which takes
the place of needing a specific overview of that class. This testing documentation contains 
the methods  we used to test and all tests that we conducted. 
