#include <stdio.h>

int main(void) {
   const double GALLON_PER_SQF = 350;
   double height;
   double width;
   double area;
   printf("Enter wall height (feet):\n");
   scanf("%lf", &height);
   printf("Enter wall width (feet):\n");
   scanf("%lf", &width);
   area = height * width;
   printf("Wall area: %0.2lf square feet\n", area);
   double gallons = area / GALLON_PER_SQF; 
   printf("Paint needed: %0.2lf gallons\n", gallons);
   int cans = gallons;
   printf("Cans needed: %d can(s)\n", cans);

  return 0;
}

