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
   fprintf(stderr, "Usage: mygrep -s <filter> [-f <file>] [-h]\n");
}

/* streamFile
 * @param FILE* int (an input stream)
 * @param FILE* out (an output stream)
 * @param char* filter (patter to search for)
 * returns 0 on success, non-zero on error 
*/
int streamFile(FILE *in, FILE *out, char *filter) {
   char *buffer = (char*) malloc(sizeof(char) * READ_BUFFER_SIZE);
   if(buffer == NULL) {
      fprintf(stderr, "Malloc failed\n");
      return 1;
   }
   buffer[0] = '\0';
   char *readPtr = buffer;
   int currSize = READ_BUFFER_SIZE;
   int prevSize = currSize;

   while (NULL != fgets(buffer, READ_BUFFER_SIZE, in)){
      if(strstr(buffer, "\n")) {
         if(strstr(buffer, filter)) {
            fprintf(out, "%s", buffer);
         }
         readPtr = buffer;
      } else {
         buffer = realloc(buffer, currSize * 2);
         if(buffer == NULL) {
            fprintf(stderr, "Realloc failed\n");
            return 1;
         }
         prevSize = currSize;
         currSize *= 2;
         readPtr = &buffer[prevSize];
      }
   }
   free(buffer);
  return 0;
}

int main (int argc, char * argv[]) {
   int option;
   int hflag = 0;
   char filename[MAX_FILEPATH_SIZE];
   char filter[MAX_FILEPATH_SIZE];
   filename[0] = '\0';
   filter[0] = '\0';

   while((option = getopt(argc, argv, "hs:f:")) != -1) {
      switch(option) {
      case 'h':
         hflag = 1;
         break;
      case 's':
         strcpy(filter, optarg);
         break;
      case 'f':
         strcpy(filename, optarg);
         break;
      default:
         printUsage();
         return 1;
      }
   }

   if(filter[0] == '\0') {
      printUsage();
      return 1;
   }

   if(hflag) {
      printUsage();
      return 0;
   }

   int rc = 0;
   if(filename[0] == '\0')  {
      rc = streamFile(stdin, stdout, filter);
   } else {
      FILE *dataFile = fopen(filename, "r");
      if(dataFile == NULL) {
         fprintf(stderr, "Unable to open file\n");
         return 1;
      }
      rc = streamFile(dataFile, stdout, filter);
      fclose(dataFile);
   }
   if(rc) {
      fprintf(stderr, "Streaming Failed\n");
      return 1;
   }
  return 0;
}
