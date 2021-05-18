# Documentation For Testing Introduction:
For this project, we created tests based on the white-box testing technique. 
We divided the testing work up to a head tester, and then the assistants. 
Danny DeMelfi was the head of testing, with Alex and Ally as the assistants. 
First, we created a skeleton of gtest, but we created tests after the 
implementation of other classes was complete. We did not let the unit tests
define what functions would work before they were created, but instead created 
the tests to see if everything worked as intended after the implementation was 
completed. We used two classes defined in the unit test class, for the database
and the matchmaker respectively, with the matchmaker specifying the creation of 
4 new pets and 4 new adopters that are destroyed at the end of the test. 

There are five groupings of tests, separated by blocks of asterisks and the name 
of the next group for testing. Each outlines the tests that were done for that 
group. We did not bother testing GUI since that is less-effective with unit testing. 
Instead, we tested the database and matchmaker functions. 4 out of the 5 groupings 
were tests created for testing databases, the core of the foundation for the project.
As important as the database was, we decided to thoroughly test it the most, 
including adding to the different tables, reading the data in, and retrieving that 
data. For matchmaking, the tests were more simplistic, since it was a shorter class
and most methods utilized each other, so if one worked, then the other would as well.
As such, less tests were needed, since we could see if they worked. 

# Database Tests
First, we tested the addition and removal of pets into the database. For every test,
sample data was created, then deleted so as to not permanently change the database 
and save test information. We then tested adding pets with the same id, which was fine
since the id is automatically reassigned in the beginning of the pets, however we did
not allow pets with the same species, breed and name in case of duplicates. We also 
made sure that a pet with little parameters specified was able to be added, say if 
the user could not fill out the information entirely. We also tested that a user could
not enter weird information like negative ages or weights or something similar. We also
tested that we could not add a pet that was un-initialized. We also tested that when
searching for pets, using the find pets method within the database, it returned the 
correct pets. Finally, we tested the update pet method so that pets within the database
can be edited if needed by the user.

Next we focused on similar tests for the adopter and adoptee respectively. The only 
difference in tests for the pets and these two, were that instead of the find pets, 
we tested the read-in methods as well. The pets read-in was not needed to test since 
it’s sole purpose is to read in pets that already exist in the database which was 
tested separately from the unit tests. However, for the read-in methods for adopter 
and adoptee, we created sample adopters/adoptees which we then read in using the 
database manager read-in methods. Each of these tests were successful. Finally, to 
finish the database tests, we did an additional test for finding the same username 
by creating two users, one being an adopter and the other being an adoptee, to make 
sure that they could not be added because they had the same username. The Conversation
table was much simpler than the others, and used already created adopters and adoptees 
so the add and remove methods were combined into one test. Overall, all tests run as 
expected, after debugging the database when these tests were written. 

# Matchmaking Tests
The final two tests are written for matchmaking. As stated previously, the matchmaker 
test is created using a class defined within the testing class that creates 4 pets, 
two with the same species, and some similar information. Then there are four adopters 
each with different preferences. These were created so that one adopter would be able 
to see all four testing pets, the second adopter would match their preferences for 
exactly one test pet, while the others both tested unusual hard preferences which 
should return no pets that they would be able to see. All tests within one unit test 
were successful. The other matchmaker test, made sure that the arrange pets worked, 
which sorted them in alphabetical order using a sorting library that worked fine. 
These tests are simplistic for matchmaker, but since each method within the matchmaker 
relies on another method, if one test works as intended, then others test would as well.
However, there is one error. When the database is reloaded with the test information 
one method for matchmaker tests returns an error, but if the program is run again, it 
works. The reason this was not fixed, is that to test matchmaker without modifying the 
database, we erase each pet within the database vector of pets before the test is called,
which causes a temporary error. It does work after the first run through, though. This 
concludes the unit-testing for Claws n’ Paws. 
