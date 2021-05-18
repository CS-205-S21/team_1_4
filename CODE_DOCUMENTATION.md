# Introduction
Our project has 4 total classes, with the testing file not
included with the code documentation like database and matchmaker are.
Each one has a group of methods, with their documentation code here, 
as referenced using the header file comments and method declarations.
For a more accurate depiction of our code, see the source code for the
project that also includes the source code, but this will be an overview
for the database and matchmaker classes with their method descriptions. 
It will also include a brief intoruction for what the class's prupose is
and how it works in relation ot the others. For more information on the 
testing, see the TESTING_DOCUMENTATION.md file, and make sure to read 
over the README.md file to understand what this project is, and how to 
properly build and run it. This file also contains a breif description of 
the GUI class. 

# DatabaseManager
The Database serves as the foundation for our project. Using sqlite3, we 
create four tables, for adopters, adoptees, pets, and conversations between
users. Each table has their own specifications, such as pets with names, 
species, breed, color, weight, age bio, and picture. The adopters, on the 
other hand, have their own usernames, passwords, but also a field for each 
of their preferences and whether they are hard preferences or not. They also
have fields of strings that get comverted to vectors of ints for each pet they
liked and disliked within the system. Adoptees are users similar to adopters, 
but instead of preferences or liked/disliked pets, they have a vector for pets 
that they own. Conversations each have an adopter and adoptee, and they also 
store the conversation as a string, parsed by "|". 

There are several methods within the database, with there being several different
sqlite3 queries that manage and manipulate the database. The methods are as follows:

    /**
     * @brief - These are the constructors and destructors for the database 
     * which can open and close the working database
     */
    DatabaseManager();
    ~DatabaseManager();

    /**
     * @brief PetsManager::readInPets - Reads in all pets from pet database
     *  Should only be read in once near beggining of run
     */
    void readInPets();

    /**
     * @brief DatabaseManager::readInAdopter - Reads in adopter from adopter database
     *  with matching username and password
     * @param username - Username of adopter to search for
     * @param password - Password of adopter to search for
     * @return Pointer to Pref struct of adopter's preferences and other info.
     *  If adopter is not found, a nullptr is returned.
     */
    Adopter* readInAdopter(string username, string password);
    
    /**
     * @brief DatabaseManager::readInAdopterPublic - Reads in public adopter
     *  info from database with matching username
     * @param username - Username of adopter to search for
     * @return Pointer to Pref struct of adopter's public info only.
     *  If adopter is not found, a nullptr is returned.
     */
    Adopter* readInAdopterPublic(string username);

    /**
     * @brief DatabaseManager::readInAdoptee - Reads in adoptee from adopter database
     *  with matching username and password
     * @param username - Username of adoptee to search for
     * @param password - Password of adoptee to search for
     * @return Pointer to Pref struct of adoptee's information.
     *  If adoptee is not found, a nullptr is returned.
     */
    Adoptee* readInAdoptee(string username, string password);
    
    /**
     * @brief DatabaseManager::readInAdopteePublic - Reads in public adoptee
     *  info from database with matching username
     * @param username - Username of adoptee to search for
     * @return Pointer to Pref struct of adoptee's public info only.
     *  If adoptee is not found, a nullptr is returned.
     */
    Adoptee* readInAdopteePublic(string username);

    /**
     * @brief DatabaseManager::readInMessages - Reads in conversation from
     *  messages database with adopter's username and the id
     *  of the pet they liked to begin the conversation
     * @param usernameAdopter - Username of adopter involved
     * @param petId - id of pet adopter had liked
     * @return Pointer to Conversation struct of conversation info.
     *  If conversation is not found, a nullptr is returned.
     */
    Conversation* readInConversation(string usernameAdopter, int petId);

    /**
     * @brief checkUsernames - Checks given username against usernames
     *  of all adopters and adoptees
     * @param username - Username to check for
     * @return bool - true if username is taken, false otherwise
     */
    bool isUsernameTaken(string username);

    /**
     * @brief findAdopterPet - Finds all adopters who have liked the pet
     *  with the given id
     * @param id - id for pet to look for among adopters' liked pets lists
     * @return vector<Adopter*> - a vector containing adopter structs
     *  for all adopters who liked this pet. Will return an empty
     *  vector if no adopters liked this pet or if the code otherwise fails.
     */
    vector<Adopter*> findAdopterPet(int id);

    /**
     * @brief findAdopteePet - Finds adoptee who has owned pet with given id
     * @param id - id for pet to look for among adoptees
     * @return Adoptee - struct of adoptee's info or nullptr
     *  if no adopter was found (though that shouldn't happen)
     */
    Adoptee* findAdopteePet(int id);

    /**
     * @brief DatabaseManager::findPet - Finds pet with given id from vector
     * @param findId - Id of pet to search for
     * @return Pet* - Pointer to Pet struct of pet's info. If no pet is found,
     *  returns a nullptr
     */
    Pet* findPet(int id);

    /**
     * @brief getNumPets - Finds number of pets
     * @return int - Number of pets currently in Pets vector
     */
    int getNumPets();

    /**
     * @brief getNumAdopters - Finds number of registered adopters in the database
     * @return Number of adopters currently in database, returns -1 if search fails
     */
    int getNumAdopters();

    /**
     * @brief getNumAdoptees - Finds number of registered adoptees in the database
     * @return Number of adoptees currently in database, returns -1 if search fails
     */
    int getNumAdoptees();

    /**
     * @brief addPet - Adds a pet to the database of pets and to the vector of pets
     * @param p - The pet that will be added to the database
     * @return True or false depending on if the pet was successfully added.
     */
    bool addPet(Pet* p);

    /**
     * @brief updatePet - Updates pet with given information
     * @param pet - Struct of info to update pet with
     * @return bool - True if pet successfully updated
     */
    bool updatePet(Pet* pet);

    /**
     * @brief addPet - Adds a pet to the database of pets and to the vector of pets
     * @param id - id of pet you're trying to remove
     * @return True or false depending on if the pet was successfully added.
     */
    bool removePet(int id);

    /**
     * @brief addAdopter - Adds an adopter to the database of adopters, using the pref struct
     * @param p - the adopter (pref) that will be added to the database.
     * @param password - password of adopter to add to the database
     * @return  bool - True or false depending on if the adopter was successfully added.
     */
    bool addAdopter(Adopter* p, string password);

    /**
     * @brief updateAdopter - Updates adopter with given struct of info
     * @param adopter - Adopter to find & update
     * @return bool - True if updated successfully
     */
    bool updateAdopter(Adopter* adopter);

    /**
     * @brief removeAdopter - Removes an adopter from the database of adopters
     * @param username - username of adopter you're trying to remove
     * @return bool - True or false depending on if the adopter was successfully removed.
     */
    bool removeAdopter(string username);

    /**
     * @brief addAdoptee - Adds an "adoptee" to the database of adoptees, using the adoptee info struct
     * @param p - the adoptee that will be added to the database.
     * @param password - password of adoptee to add to the database
     * @return bool - True or false depending on if the adoptee was successfully added.
     */
    bool addAdoptee(Adoptee* p, string password);

    /**
     * @brief updateAdoptee - Updates adoptee with given struct of info
     * @param adoptee - Adoptee to find & update
     * @return bool - True if updated successfully
     */
    bool updateAdoptee(Adoptee* adoptee);

    /**
     * @brief removeAdoptee - Removes an adoptee from the database of adoptees
     * @param username - username of adoptee you're trying to remove
     * @return bool - True or false depending on if the adoptee was successfully removed.
     */
    bool removeAdoptee(string username);

    /**
     * @brief addConversation - Adds a conversation to the database of conversations
     *  using the conversation struct
     * @param convo - Conversation struct
     * @return bool - Whether or not conversation was succesfully added
     */
    bool addConversation(Conversation* convo);

    /**
     * @brief updateConversation - Updates conversation with given struct of info
     * @param convo - Conversation to find & update
     * @return bool - True if updated successfully
     */
    bool updateConversation(Conversation* convo);

    /**
     * @brief removeConversation - Removes found conversation from database
     * @param usernameAdopter - Username of adopter involved in conversation
     * @param petId - id of pet involved in conversation
     * @return bool - Whether or not conversation was succesfully deleted
     */
    bool removeConversation(string usernameAdopter, int petId);

    /**
     * @brief stringToIntVector - Turns a string of ints seperated by ' ' characters
     *  into a vector of those ints
     * @param str - String to make into a vector. Must contain only integers seperated
     *  by single ' ' characters, e.g. "1 3 5 12 543"
     * @return vector<int> - Vector of ints from the passed string
     */
    vector<int> stringToIntVector(string str);

    /**
     * @brief intVectorToQString - Takes a vector of ints and converts it to
     *  a QString of numbers seperated by ' ' characters
     * @param vec - Vector of integers
     * @return QString - QString of numbers seperated by ' ' characters,
     *  e.g. "1 3 5 12 543". If a standard string is desired instead, use the
     *  QString's .toStdString function on the return value.
     */
    QString intVectorToQString(vector<int> vec);

    /**
     * @brief messageParse - Parses user message strings into a vector
     *  of seperated messages
     * @param message - A string holding all messages between the user
     *  and one other, formatted ONLY like:
     *  "senderName:Sender's message|otherSenderName:Other sender's message|", etc.
     *  Typically only used on message strings read in straight from the database
     * @return vector<QString> - A vector of individual messages, with
     *  sender's name attached to the front of each message of the
     */
    vector<QString> messageParse(string message);

    /**
     * @brief messageUnparse - Turns a vector of QStrings into a single QString
     *  seperated by '|' characters
     * @param message - A vector of QStrings
     * @return QString - Single QString of QStrings from vector
     */
    QString messageUnparse(vector<QString> message);

    /**
     * @brief getPetIdMax - Getter method for petIdMax
     * @return int - petIdMax
     */
    int getPetIdMax();
    
 # Matchmaker
 Matchmaker is the other part of the foundation for the rest of the project. 
 Matchmaking is in charge of utilizing the database manager to keep track of
 the adopters and their preferences. It uses their preferences and whether 
 they are hard preferences or not, to differentiate which pets they can see
 and which they cannot. It also keeps track of which pets they liked and
 disliked, either sending the liked pets to the GUI, or now showing the 
 disliked pets anymore. It is relatively simple, and has a total of four 
 methods that each rely on each other. 
 
 First, the Matchmaker uses the read-in pets method of the Database Manager, 
 then allocates a vector for each pet that the user has previosuly liked or 
 disliked. If they have not liked any so far, then it will show them each pet
 that matches their hard or soft preferences. The soft preferences, will still
 show them pets that do not fit their preferneces, shiffled in with pets that do 
 since this is a matchmaking system that would be useful for short-time use. 
 The matchmaker sorts these preferences in alphabetical order, and also sends that 
 information to the GUI to display the different pet types and differrent parameters
 that the user can search for within setting up their preferences. The documentation
 for Matchmaker methods looks like this:
 
    /**
     * @brief Matchmaker- Sets up database
     */
    Matchmaker();

    /**
     * @brief innit- Reads in Pets and calls the sortPrefs
     */
    void innit();

    /**
     * @brief DatabaseInterface- interfaces with the database to sort viable
     * pets for the user
     * @param cu - Current User given by GUI
     * @return Returns a vector of pets that is ready to be shown at the GUI
     */
    vector<Pet*> DatabaseInterface(Adopter *cu);

    /**
     * @brief refreshPetList- Sorts pets into discarded and sortable pets
     * based on whether they have been disliked/liked or not interfaced
     * with yet
     */
    void refreshPetList();

    /**
     * @brief sortPrefs- sorts all unique available preferencs for use in
     * comboboxes
     */
    void sortPrefs();

    /**
     * @brief arrangePrefs- arranages available user preferences
     * alphabetically for use in comboboxes
     */
    void arrangePrefs();
    
 # GUI 
 The GUI has several different forms and header files that are not listed here, 
 but instead a short description of what the GUI accomplishes. This is the main
 part of the projectm where the user can run the app, assuming they have access 
 to run it through the GUI, and we make it so that first there is a login screen
 where they can either log in as an existing user if they appear in the database,
 or they can create an account. Creating an account brings up a new form, and will
 not accept taken usernames, or if they did not select their role as an adopter or
 adoptee. Then, their data is given to the database. From here, based on whether the
 user is an adopter or adoptee, the scrren may vary. 
 
 Across both users appears differnt buttons on the screen. Users can go to their profile
 and modify their bio, or edit preferences if they are an adopter, or add/edit a pet if
 they are an adoptee. Otherwise, the profile is very simple. The home menu that immediately 
 follows the login screen also has different screens depending on the typ eof user. The home
 screen for an adopter is where you can like or dislike pets, while viewing their bio and an
 image of the pet, as well as other distinguishing factors. The adoptee on th eother hand, 
 can only see which pets they own, and can view each of their pets, also delting them if they
 need to, or if they get adopted. It is a heavy user-based system, here the adoptee will have 
 to manually delete the pet should it become adopted. The next screen that the user can navigate
 to is the liked Pets screen. Of course this iwll differ betweena dopter and adoptee, but this
 will be the area where users can message each other, which the messages will then be added
 to the conversation table in the database between users. The users can message each other, 
 discussing specific details regarding location and other things that they need to talk 
 about. 
 
 There are several other screens that branch off of the main three that they can navigate to. 
 Each is presented through the other screens, such as The chat information screen that can
 show both adoptee and oet info in a convenient place, or the preference tab that opens up 
 in the profile when an adopter wishes to edit their preferences. Each screen is used and 
 is included in the source code. 
