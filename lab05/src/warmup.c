#include <stdio.h>

int main(void) {
   char userChar;
   int height;
   
   printf("Enter a character:\n");
   scanf(" %c", &userChar);

   printf("Enter triangle height:\n");
   scanf("%d", &height);

   for(int i = 0; i < height; i++) { // Row
      for(int j = 0; j <= i; j++) {  // Column
         printf("%c", userChar);
      }
      printf("\n");
   }

  return 0;
}
