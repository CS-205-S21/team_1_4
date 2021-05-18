create table adoptee (
      username        CHAR NOT NULL UNIQUE,
      password        CHAR NOT NULL,
      shelter         CHAR NOT NULL,
      petIds          CHAR NOT NULL,   
      bio             CHAR NOT NULL             );
      
create table adopter (
      username              CHAR NOT NULL UNIQUE,
      password              CHAR NOT NULL,
      likedPetIds           CHAR NOT NULL,
      dislikedPetIds        CHAR NOT NULL,
      prefSpecies           CHAR NOT NULL,
      prefSpeciesReq        BOOLEAN NOT NULL,
      prefBreed             CHAR NOT NULL, 
      prefBreedReq          BOOLEAN NOT NULL,  
      prefAge               CHAR NOT NULL, 
      prefAgeReq            BOOLEAN NOT NULL,
      prefWeight            DOUBLE NOT NULL,
      prefWeightReq         BOOLEAN NOT NULL,
      prefColor             DOUBLE NOT NULL,
      prefColorReq          BOOLEAN NOT NULL,
      prefHypoallergenic    BOOLEAN NOT NULL, 
      prefHypoallergenicReq BOOLEAN NOT NULL,
      prefSex               CHAR NOT NULL,
      prefSexReq            INT NOT NULL,
      bio                   CHAR NOT NULL           );

create table conversation (
      usernameAdopter CHAR NOT NULL,
      petId           INT NOT NULL,
      usernameAdoptee CHAR NOT NULL,
      messages        CHAR NOT NULL        );
      

create table pet (
      petId          INT NOT NULL UNIQUE,
      name           CHAR NOT NULL,
      species        CHAR NOT NULL,
      breed          CHAR NOT NULL,
      age            INT NOT NULL,
      weight         DOUBLE NOT NULL,
      color          CHAR NOT NULL,
      hypoallergenic BOOLEAN NOT NULL, 
      sex            CHAR NOT NULL, 
      bio            CHAR NOT NULL,
      image          BLOB NOT NULL          );
      
.separator ","
.mode csv
.import "00_build_db/adoptee.csv"  adoptee
.import "00_build_db/adopter.csv"  adopter
.import "00_build_db/conversation.csv" conversation
.import "00_build_db/pet.csv"      pet