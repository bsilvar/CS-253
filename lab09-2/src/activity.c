#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataNode.h"

int main(void) {
   srand(time(0)); 
   enum Lists {HOME_LIST, FEMALE_SPOUSE_LIST, MALE_SPOUSE_LIST, 
          OCCUPATION_LIST, TRANSPORTATION_LIST, HOMETOWN_LIST};

   char* homeList[5]   = {"mansion","apartment","shack","house","ice house"};
   char* femaleList[6] = {"Robin","Lily","Nora","Patrice","Zoey","Quinn"};
   char* maleList[6]   = {"Ted","Marshall","Barney","Ranjit","Carl","Linus"};
   char* workList[5]   = {"teacher","architect","lawyer","newscaster","undercover agent"};
   char* transList[5]  = {"walk","ride the train","ride a bus","fly an airplane","carpool"};
   char* townList[6]   = {"Cleveland","Queens","The Bronx","Brooklyn","Manhattan","Staten Island"};
   
   DataNode* database[6];
   database[HOME_LIST]           = BuildDataList(homeList, 5);
   database[FEMALE_SPOUSE_LIST]  = BuildDataList(femaleList, 6);
   database[MALE_SPOUSE_LIST]    = BuildDataList(maleList, 6);
   database[OCCUPATION_LIST]     = BuildDataList(workList, 5);
   database[TRANSPORTATION_LIST] = BuildDataList(transList, 5);
   database[HOMETOWN_LIST]       = BuildDataList(townList, 6);

   printf("--------------------- Future Possibilities Database ------------------------\n");
   printf("Home List: ");
   PrintDataList(database[HOME_LIST]);
   printf("Female Spouse: ");
   PrintDataList(database[FEMALE_SPOUSE_LIST]);
   printf("Male Spouse: ");
   PrintDataList(database[MALE_SPOUSE_LIST]);
   printf("Occupation List: ");
   PrintDataList(database[OCCUPATION_LIST]);
   printf("Transportation List: ");
   PrintDataList(database[TRANSPORTATION_LIST]);
   printf("Hometown List: ");
   PrintDataList(database[HOMETOWN_LIST]);
   printf("----------------------------------------------------------------------------\n");

   char usrName[15];
   printf("\nPlease enter your name: ");
   if(NULL == fgets(usrName, 15, stdin)) {
      return 1;
   }
   char* ptr = strstr(usrName, "\n");
   if(NULL != ptr) {
      *ptr = '\0';
   }
   ptr = strstr(usrName, "\r");
   if(NULL != ptr) {
      *ptr = '\0';
   }

   DataNode* randNode = GetRandomDataNode(database[HOME_LIST]);
   char* home = randNode->dataValue;
   randNode = GetRandomDataNode(database[HOMETOWN_LIST]);
   char* town = randNode->dataValue;
   randNode = GetRandomDataNode(database[OCCUPATION_LIST]);
   char* job = randNode->dataValue;
   randNode = GetRandomDataNode(database[FEMALE_SPOUSE_LIST]);
   char* spouse = randNode->dataValue;
   randNode = GetRandomDataNode(database[TRANSPORTATION_LIST]);
   char* transp = randNode->dataValue;

   printf("\nWelcome %s, this is your future...\n", usrName);
   printf("You will marry %s and live in a %s.\n", spouse, home);
   printf("After 7 years of marriage, ");
   printf("you will finally get your dream job of being a %s.\n", job);
   randNode = GetRandomDataNode(database[HOME_LIST]);
   home = randNode->dataValue;
   printf("Your family will move to a %s in %s ", home, town);
   printf("where you will %s to work each day.\n", transp);

   for(int i = 0; i < 6; i++) {
      DestroyDataList(database[i]);
   }

  return 0;
}
