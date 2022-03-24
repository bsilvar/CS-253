#include <stdio.h>

int main(void) {
   int arrowBaseHeight;
   int arrowBaseWidth;
   int arrowHeadWidth;

   printf("Enter arrow base height:\n");
   scanf("%d", &arrowBaseHeight);

   printf("Enter arrow base width:\n");
   scanf("%d", &arrowBaseWidth);

   printf("Enter arrow head width:\n");
   scanf("%d", &arrowHeadWidth);
   while(arrowHeadWidth <= arrowBaseWidth) {
      printf("Enter arrow head width:\n");
      scanf("%d", &arrowHeadWidth);
   }

   printf("\n\n");
   // Arrow Body
   for(int i = 0; i < arrowBaseHeight; i++) {   // Rows
      for(int j = 0; j < arrowBaseWidth; j++) { // Columns
         printf("*");
      }
      printf("\n");
   }
   // Arrow Head
   for(int i = arrowHeadWidth; i > 0; i--) {  // Rows
      for(int j = i; j > 0; j--) {   // Columns
         printf("*");
      }
      printf("\n");
   }

  return 0;
}
