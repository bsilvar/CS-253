/* :
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
#include <ctype.h>

#define READ_BUFFER_SIZE 1024
#define MAX_FILEPATH_SIZE 4096

void printUsage(void){
   fprintf(stderr, "Usage: mywc [-f <file>] [-c] [-w] [-l] [-h]\n");
  return;
}

typedef struct DataStats_struct {
   int numChars;
   int numWords;
   int numLines;
} DataStats;

DataStats streamFile(FILE *in) {
   DataStats stats;
   stats.numChars = 0;
   stats.numWords = 0;
   stats.numLines = 0;

   char buffer[READ_BUFFER_SIZE];
   int count;

   while (NULL != fgets(buffer, READ_BUFFER_SIZE, in)){
      count = strlen(buffer);
	  if(buffer[count] != '\n') {
         fprintf(stderr, "Error with buffer\n");
         exit(1);
      }
      // Number of chars
      stats.numChars += count;
      // Number of lines
      stats.numLines++;
      // Number of words
      for(int i = 0; i < count; i++) {
         if(buffer[i] == ' ' || buffer[i] == '\t') {
            int next = 1;
            while(isspace(buffer[i+next])) {
               next++;			
            }
            stats.numWords++;
            i = (i + next) - 1;
         } else if(buffer[i] == '\n') {
            stats.numWords++;
         }
      }
   }
  return stats;
}

int main (int argc, char * argv[]) {
   int option;
   int hflag = 0;
   int cflag = 0;
   int wflag = 0;
   int lflag = 0;
   char filename[MAX_FILEPATH_SIZE];
   filename[0] = '\0';

   while((option = getopt(argc, argv, "cwlhf:")) != -1) {
      switch(option) {
      case 'h':
         hflag = 1;
         break;
      case 'c':
         cflag = 1;
         break;
      case 'w':
         wflag = 1;
         break;
      case 'l':
         lflag = 1;
         break;
      case 'f':
         strcpy(filename, optarg);
         break;
      default:
         printUsage();
         exit(1);
      }
   }

   if(hflag) {
      printUsage();
      return 0;
   }

   DataStats stats;
   if(filename[0] == '\0')  {
      stats = streamFile(stdin);
   } else {
      FILE *dataFile = fopen(filename, "r");
      if(dataFile == NULL) {
         fprintf(stderr, "Unable to open file\n");
         return 1;
      }
      stats = streamFile(dataFile);
      fclose(dataFile);
   }

   if((lflag + wflag + cflag) == 0) {
      fprintf(stdout, " %d  %d %d %s\n", 
              stats.numLines, stats.numWords, 
              stats.numChars, filename);
   } else {
      if(lflag) {
         fprintf(stdout, "%d ", stats.numLines);
      }
      if(wflag) {
         fprintf(stdout, "%d ", stats.numWords);
      }
      if(cflag) {
         fprintf(stdout, "%d ", stats.numChars);
      }
      fprintf(stdout, " %s\n", filename);
   }   
  return 0;
}
