#include <stdio.h>

int main(void){
   int userNum;
   printf("Enter integer:\n");
   scanf("%d", &userNum);
   printf("You entered: %d\n", userNum);
   int numSqrd = userNum * userNum;
   printf("%d squared is %d\n", userNum, numSqrd);
   int numCubed = userNum * numSqrd;
   printf("And %d cubed is %d!!\n", userNum, numCubed);
   printf("Enter another integer:\n");
   int userNum2;
   scanf("%d", &userNum2);
   printf("%d + %d is %d\n", userNum, userNum2, userNum + userNum2);
   printf("%d * %d is %d\n", userNum, userNum2, userNum * userNum2);
  return 0;
}
