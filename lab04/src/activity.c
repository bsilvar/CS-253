#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX_SIZE 50

int main(void) {
   // Service Station
   char userOpt1[MAX_SIZE];
   char userOpt2[MAX_SIZE];
   char* ptr;
   int oilCost = 35;
   int tireCost = 19;
   int washCost = 7;
   int waxCost = 12;
   int serv1Cost = 0;
   int serv2Cost = 0;

   printf("Davy's auto shop services\n");
   printf("Oil change -- $%d\n", oilCost);
   printf("Tire rotation -- $%d\n", tireCost);
   printf("Car wash -- $%d\n", washCost);
   printf("Car wax -- $%d\n", waxCost);

   printf("\nSelect first service:\n");
   fgets(userOpt1, MAX_SIZE, stdin);
   ptr = userOpt1;
   while(*ptr != '\0') {
      if(*ptr == '\n') {
         *ptr = '\0';
      }
      ptr++;
   }

   printf("Select second service:\n");
   fgets(userOpt2, MAX_SIZE, stdin);
   ptr = userOpt2;
   while(*ptr != '\0') {
      if(*ptr == '\n') {
         *ptr = '\0';
      }
      ptr++;
   }

   if(strcmp(userOpt1, "-") != 0) {
      for(size_t i = 0; i < strlen(userOpt1); i++) {
         userOpt1[i] = tolower(userOpt1[i]);
      }
   }
   if(strcmp(userOpt2, "-") != 0) {
      for(size_t i = 0; i < strlen(userOpt2); i++) {
         userOpt2[i] = tolower(userOpt2[i]);
      }
   }
   printf("\nDavy's auto shop invoice\n\n");
   // Service 1
   if(strcmp(userOpt1, "oil change") == 0) {
      printf("Service 1: Oil change, $%d\n", oilCost);
      serv1Cost = oilCost;
   } else if(strcmp(userOpt1, "tire rotation") == 0) {
      printf("Service 1: Tire rotation, $%d\n", tireCost);
      serv1Cost = tireCost;
   } else if(strcmp(userOpt1, "car wash") == 0) {
      printf("Service 1: Car wash, $%d\n", washCost);
      serv1Cost = washCost;
   } else if(strcmp(userOpt1, "car wax") == 0) {
      printf("Service 1: Car wax, $%d\n", waxCost);
      serv1Cost = waxCost;
   } else if(strcmp(userOpt1, "-") == 0) {
      printf("Service 1: No service\n");
   } else {
      printf("Error: Requested service is not recognized\n");
   }
   // Service 2
   if(strcmp(userOpt2, "oil change") == 0) {
      printf("Service 2: Oil change, $%d\n", oilCost);
      serv2Cost = oilCost;
   } else if(strcmp(userOpt2, "tire rotation") == 0) {
      printf("Service 2: Tire rotation, $%d\n", tireCost);
      serv2Cost = tireCost;
   } else if(strcmp(userOpt2, "car wash") == 0) {
      printf("Service 2: Car wash, $%d\n", washCost);
      serv2Cost = washCost;
   } else if(strcmp(userOpt2, "car wax") == 0) {
      printf("Service 2: Car wax, $%d\n", waxCost);
      serv2Cost = waxCost;
   } else if(strcmp(userOpt2, "-") == 0) {
      printf("Service 2: No service\n");
   } else {
      printf("Error: Requested service is not recognized\n");
   }
   printf("\nTotal: $%d\n", serv1Cost + serv2Cost);
  return 0;
}
