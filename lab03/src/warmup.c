#include <stdio.h>

int main(void) {

   int numInt;
   double numDouble;
   char letter;
   char string[10];
   printf("Enter integer:\n");
   scanf("%d", &numInt);
   printf("Enter double:\n");
   scanf("%lf", &numDouble);
   printf("Enter character:\n");
   scanf(" %c", &letter);
   printf("Enter string:\n");
   scanf("%s", string);
   printf("%d %lf %c %s\n", numInt, numDouble, letter, string);
   printf("%s %c %lf %d\n", string, letter, numDouble, numInt);
   printf("%lf cast to an integer is %d\n", numDouble, (int)numDouble);

  return 0;
}
