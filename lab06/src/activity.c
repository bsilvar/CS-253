#include <stdio.h>
#define MAX_SIZE 5

void printMenu(void) {
   printf("\nMENU\n");
   printf("u - Update player rating\n");
   printf("a - Output players above a rating\n");
   printf("r - Replace player\n");
   printf("o - Output roster\n");
   printf("q - Quit\n");
  return;
}

int main(void) {
   int jersey[MAX_SIZE];
   int rating[MAX_SIZE];
   int jerseyNum;
   int ratingNum;
   int found;
   char option;

   for(int i = 0; i < MAX_SIZE; i++) {
      printf("Enter player %d's jersey number:\n", i+1);
      scanf("%d", &(jersey[i]));
      while(jersey[i] < 0 || jersey[i] > 99) {
         printf("Enter player %d's jersey number:\n", i+1);
         scanf("%d", &(jersey[i]));
      }
      printf("Enter player %d's rating:\n", i+1);
      scanf("%d", &(rating[i]));
      while(rating[i] < 1 || rating[i] > 9) {
         printf("Enter player %d's rating:\n", i+1);
         scanf("%d", &(rating[i]));
      }
      printf("\n");
   }

   printf("ROSTER\n");
   for(int i = 0; i < MAX_SIZE; i++) {
      printf("Player %d -- Jersey number: %d, Rating: %d\n", i+1, jersey[i], rating[i]);
   }

   do {
      printMenu();
      printf("\nChoose an option:\n");
      scanf(" %c", &option);
      // Quit
      if(option == 'q') {
         return 0;
      // Update player rating
      } else if(option == 'u') {
         found = 0;
         printf("Enter a jersey number:\n");
         scanf("%d", &jerseyNum);
         while(jerseyNum < 0 || jerseyNum > 99) {
            printf("Enter a jersey number:\n");
            scanf("%d", &jerseyNum);
         }
         for(int i = 0; i < MAX_SIZE; i++) {
            if(jersey[i] == jerseyNum) {
               found = 1;
               printf("Enter a new rating for player:\n");
               scanf("%d", &(rating[i]));
               while(rating[i] < 1 || rating[i] > 9) {
                  printf("Enter a new rating for player:\n");
                  scanf("%d", &(rating[i]));
               }
            }
         }
         if(found == 0) {
            printf("Error: player not in roster\n");
         }
      // Output players above a rating
      } else if (option == 'a') {
         printf("Enter a rating:\n"); 
         scanf("%d", &ratingNum);
         while(ratingNum < 1 || ratingNum > 9) {
            printf("Enter a rating:\n"); 
            scanf("%d", &ratingNum);
         }
         printf("\nABOVE %d\n", ratingNum);
         for(int i = 0; i < MAX_SIZE; i++) {
            if(rating[i] > ratingNum) {
               printf("Player %d -- Jersey number: %d, Rating: %d\n", i+1, jersey[i], rating[i]);
            }
         }
      // Replace player
      } else if (option == 'r') {
         found = 0;
         printf("Enter a jersey number:\n"); 
         scanf("%d", &jerseyNum);
         while(jerseyNum < 0 || jerseyNum > 99) {
            printf("Enter a jersey number:\n"); 
            scanf("%d", &jerseyNum);
         }
         for(int i = 0; i < MAX_SIZE; i++) {
            if(jersey[i] == jerseyNum) {
               found = 1;
               printf("Enter a new jersey number:\n");
               scanf("%d", &(jersey[i]));
               while(jersey[i] < 0 || jersey[i] > 99) {
                  printf("Enter a new jersey number:\n");
                  scanf("%d", &(jersey[i]));
               }
               printf("Enter a rating for the new player:\n");
               scanf("%d", &(rating[i]));
               while(rating[i] < 1 || rating[i] > 9) {
                  printf("Enter a rating for the new player:\n");
                  scanf("%d", &(rating[i]));
               }
            }
         }
         if(found == 0) {
            printf("Error: player not in roster\n");
         }
      // Output roster
      } else if (option == 'o') {
         printf("\nROSTER\n");
         for(int i = 0; i < MAX_SIZE; i++) {
            printf("Player %d -- Jersey number: %d, Rating: %d\n", i+1, jersey[i], rating[i]);
         }
      // Invalid option
      } else {
         printf("Error: not a valid option\n"); 
      }
   } while(option != 'q');

  return 0;
}
