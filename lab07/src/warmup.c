#include <stdio.h>
#define MAX_LEN 50 

//Returns the number of characters in usrStr
int GetNumOfCharacters(const char usrStr[]) {
   int numChars = 0;
   for(int i = 0; usrStr[i] != '\0'; i++) {
      numChars++;
   }
  return numChars; 
}

//Prints string without spaces
void OutputWithoutWhitespace(const char usrStr[]) {
   char tempStr[MAX_LEN];
   int j = 0;
   for(int i = 0; usrStr[i] != '\0'; i++) {
      if(usrStr[i] != ' ' && usrStr[i] != '\t') {
		 tempStr[j] = usrStr[i];
		 j++;
      }
   }
   tempStr[j] = '\0';
   printf("String with no whitespace: %s", tempStr);
  return;
}

int main(void) {
   char usrStr[MAX_LEN];
   printf("Enter a sentence or phrase:\n");
   if(NULL == fgets(usrStr, MAX_LEN, stdin)) {
      return 1;
   }
   printf("\nYou entered: %s\n", usrStr);
   printf("Number of characters: %d\n", GetNumOfCharacters(usrStr));
   OutputWithoutWhitespace(usrStr);

  return 0;
}
