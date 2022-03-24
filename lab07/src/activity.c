#include <stdio.h>
#include <ctype.h>
#define MAX_LEN 500

void ShortenSpace(char usrStr[]) {
   char tempStr[MAX_LEN];
   int j = 0;
   for(int i = 0; usrStr[i] != '\0'; i++) {
      if(usrStr[i] != ' ') {
         tempStr[j] = usrStr[i];
         j++;
      } else {
         tempStr[j] = usrStr[i];
         j++;
         while(usrStr[i+1] == ' ') {
            i++;
         }   
      }
   }
   tempStr[j] = '\0';
   int index;
   for(int i = 0; tempStr[i] != '\0'; i++) {
      index = i;
      usrStr[i] = tempStr[i];
   }
   usrStr[index+1] = '\0';
  return;
}

void ReplaceExclamation(char usrStr[]) {
   for(int i = 0; usrStr[i] != '\0'; i++) {
      if(usrStr[i] == '!') {
         usrStr[i] = '.';
      }
   }
  return;
}

void FixCapitalization(char usrStr[]) {
   for(int i = 0; usrStr[i] != '\0'; i++) {
      if(i == 0 && isalpha(usrStr[i])) {
         usrStr[i] = toupper(usrStr[i]);
      }
	  if(usrStr[i] == '.' || usrStr[i] == '?' || usrStr[i] == '!') {
         while(!isalpha(usrStr[i])) {
            i++;
         }
         usrStr[i] = toupper(usrStr[i]);
      }
   }
  return;
}

int GetNumOfWords(const char usrStr[]) {
   int numOfWords = 0;
   for(int i = 0; usrStr[i] != '\0'; i++) {
      if(usrStr[i] == ' ' || usrStr[i] == '\n' || usrStr[i] == '\t') {
         numOfWords++;
         while(usrStr[i+1] == ' ') {
            i++;
         }
      }
   }
  return numOfWords;
}

int GetNumOfNonWSCharacters(const char usrStr[]) {
   int numOfChars = 0;
   for(int i = 0; usrStr[i] != '\n'; i++) {
      if(usrStr[i] != ' ' && usrStr[i] != '\t') {
         numOfChars++;
      }
   }
  return numOfChars;
}

char PrintMenu(char usrStr[]) {
   char option;
   printf("\nMENU\n");
   printf("c - Number of non-whitespace characters\n");
   printf("w - Number of words\n");
   printf("f - Fix capitalization\n");
   printf("r - Replace all !'s\n");
   printf("s - Shorten spaces\n");
   printf("q - Quit\n");
   printf("\nChoose an option:\n");
   scanf(" %c", &option);
   while(!(option == 'q' || option == 'c' || option == 'w' ||
           option == 'f' || option == 'r' || option == 's' )) {
      printf("Choose an option:\n");
      scanf(" %c", &option);
   }
   if(option == 'c') {
      int nonWSChars = GetNumOfNonWSCharacters(usrStr);
      printf("Number of non-whitespace characters: %d\n", nonWSChars);
   } 
   if(option == 'w') {
      int numOfWords = GetNumOfWords(usrStr);
      printf("Number of words: %d\n", numOfWords);
   } 
   if(option == 'f') {
      FixCapitalization(usrStr);
      printf("Edited text: %s", usrStr);
   } 
   if(option == 'r') {
      ReplaceExclamation(usrStr);
      printf("Edited text: %s", usrStr);
   } 
   if(option == 's') {
      ShortenSpace(usrStr);
      printf("Edited text: %s", usrStr);
   }
  return option;
}

int main(void) {
   char usrStr[MAX_LEN];
   char usrOpt;
   printf("Enter a sample text:\n");
   if(NULL == fgets(usrStr, MAX_LEN, stdin)) {
      return 1;
   }

   printf("\nYou entered: %s", usrStr);

   do {
      usrOpt = PrintMenu(usrStr);
   } while(usrOpt != 'q');

  return 0;
}
