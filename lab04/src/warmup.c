#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_SIZE 50

int main(void) {
   // Service Station
   char userOpt[MAX_SIZE];
   printf("Enter desired auto service:\n");
   fgets(userOpt, MAX_SIZE, stdin);
   char* ptr = userOpt;
   while(*ptr != '\0') {
      if(*ptr == '\n') {
         *ptr = '\0';
      }
      ptr++;
   }
   printf("You entered: %s\n", userOpt);
   for(int i = 0; i < strlen(userOpt); i++) {
      userOpt[i] = tolower(userOpt[i]);
   }
   int servCost;
   if(strcmp(userOpt, "oil change") == 0) {
      servCost = 35;
      printf("Cost of oil change: $%d\n", servCost);
   } else if(strcmp(userOpt, "tire rotation") == 0) {
      servCost = 19;
      printf("Cost of tire rotation: $%d\n", servCost);
   } else if(strcmp(userOpt, "car wash") == 0) {
      servCost = 7;
      printf("Cost of car wash: $%d\n", servCost);
   } else {
      printf("Error: Requested service is not recognized\n");
   }

  return 0;
}
