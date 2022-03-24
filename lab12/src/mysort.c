/* 
 * Author: Luke Hindman
 * Date: Fri 13 Nov 2020 12:21:37 PM PST
 * Description: Starter code for stream processing lab
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define READ_BUFFER_SIZE 1024
#define MAX_FILEPATH_SIZE 4096

void printUsage(void){
   fprintf(stderr, "Usage: mysort [-f <file>] [-r] [-h]\n");
   return;
}

int reverseFunction(const void *eA, const void *eB) {
   char *str1 = *(char**)eA;
   char *str2 = *(char**)eB;
   int result = strcmp(str2, str1);
  return result;
}

int compareFunction(const void *eA, const void *eB) {
   char *str1 = *(char**)eA;
   char *str2 = *(char**)eB;
   int result = strcmp(str1, str2);
  return result;
}

/* streamFile
 * @param FILE* int (an input stream)
 * @param FILE* out (an output stream)
 * @param int reverseFlag (reverse output)
 * returns 0 on success, non-zero on error 
*/
int streamFile(FILE *in, FILE *out, int reverseFlag) {
   const int MIN_SIZE = 16;
   char buffer[READ_BUFFER_SIZE];
   buffer[0] = '\0';

   char **lines = (char**) malloc(sizeof(char*) * MIN_SIZE);
   if(lines == NULL) {
      fprintf(stderr, "Malloc failed\n");
      return 1;
   }

   int currSize = MIN_SIZE;
   int newSize;
   int count;
   int lineCount = 0;
   while (NULL != fgets(buffer, READ_BUFFER_SIZE, in)){
      count = strlen(buffer);
      printf("# of chars in line %d: %d\n", lineCount, count);// TEST
      if(lineCount == currSize) {
         lines = realloc(lines, currSize * 2);
         if(lines == NULL) {
            fprintf(stderr, "Realloc failed\n");
            return 1;
         }
         newSize = currSize * 2;
         printf("Growing Array: %d -> %d\n", currSize, newSize);
         currSize = newSize;
      }
      //lines[lineCount] = (char*) malloc(sizeof(char) * count + 1);
      //if(lines[lineCount] == NULL) {
      char *str = (char*) malloc(sizeof(char) * count + 1);
      if(str == NULL) {
         fprintf(stderr, "Malloc failed\n");	  
         return 1;
      }
      //strcpy(lines[lineCount], buffer);
      strcpy(lines[lineCount], strcpy(str, buffer));
      printf("Copy of string in line %d: %s", lineCount, lines[count]); //TEST
      lineCount++;
   }
   if(reverseFlag) {
      qsort(lines, lineCount, sizeof(char*), reverseFunction);
   } else {
      qsort(lines, lineCount, sizeof(char*), compareFunction);
   }

   for(int i = 0; i < lineCount; i++) {
      fprintf(out, "lines[i]\n");
      free(lines[i]);
   }
   free(lines);

  return 0;
}

int main (int argc, char * argv[]) {
   int option;
   int hflag = 0;
   int rflag = 0;
   char filename[MAX_FILEPATH_SIZE];
   filename[0] = '\0';

   while((option = getopt(argc, argv, "rhf:")) != -1) {
      switch(option) {
      case 'h':
         hflag = 1;
         break;
      case 'r':
         rflag = 1;
         break;
      case 'f':
         strcpy(filename, optarg);
         break;
      default:
         printUsage();
         return 1;
      }
   }
   if(hflag) {
      printUsage();
      return 0;
   }

   int rc = 0;
   if(filename[0] == '\0')  {
      rc = streamFile(stdin, stdout, rflag);
   } else {
      FILE *dataFile = fopen(filename, "r");
      if(dataFile == NULL) {
         fprintf(stderr, "Unable to open file\n");
         return 1;
      }
      rc = streamFile(dataFile, stdout, rflag);
      fclose(dataFile);
   }
   if(rc != 0) {
      fprintf(stderr, "Streaming Failed\n");
      return 1;
   }
  return 0;
}
