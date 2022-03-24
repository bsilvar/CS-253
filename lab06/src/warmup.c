#include <stdio.h>
#define MAX_SIZE 5

int main(void) {
   double weight[MAX_SIZE];
   double total = 0;
   double max = 0;

   for(int i = 0; i < MAX_SIZE; i++) {
      printf("Enter weight %d:\n", i+1);
      scanf("%lf", &(weight[i]));
      total += weight[i];
      if(weight[i] > max) {
         max = weight[i];
      }
   }

   printf("You entered: ");
   for(int i = 0; i < MAX_SIZE; i++) {
      printf("%0.2lf ", weight[i]);
   }

   printf("\n\nTotal weight: %0.2lf\n", total);
   printf("Average weight: %0.2lf\n", total/MAX_SIZE);
   printf("Max weight: %0.2lf\n", max);

  return 0;
}
