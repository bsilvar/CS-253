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

/* streamFile
 * @param FILE* int (an input stream)
 * @param FILE* out (an output stream)
 * returns 0 on success, non-zero on error 
*/
int streamFile(FILE *in, FILE *out) {
   char buffer[READ_BUFFER_SIZE];
   int count = 0;
   while (NULL != fgets(buffer, READ_BUFFER_SIZE, in)){
      count = strlen(buffer);
      if(buffer[count] == '\n') {
         fprintf(out, "%s", buffer);
	  } else {
         return 1;   
      }
   }
  return 0;
}

int main (int argc, char * argv[]) {
   int option;
   int hflag = 0;
   char filename[MAX_FILEPATH_SIZE];
   filename[0] = '\0';

   while((option = getopt(argc, argv, "hf:")) != -1) {
      switch(option) {
      case 'h':
         hflag = 1;
         break;
      case 'f':
         strcpy(filename, optarg);
         break;
      default:
         fprintf(stderr, "Usage: mycat [-f <file>] [-h]\n"); 
         return 1;
      }
   }

   if(hflag) {
      fprintf(stdout, "Usage: mycat [-f <file>] [-h]\n"); 
      return 0;
   }
   
   int rc = 0;
   if(filename[0] == '\0')  {
      rc = streamFile(stdin, stdout);
   } else {
      FILE *dataFile = fopen(filename, "r");
      if(dataFile == NULL) {
         fprintf(stderr, "Unable to open file\n");
         return 1;
      }
      rc = streamFile(dataFile, stdout);
      fclose(dataFile);
   }
   if(rc != 0) {
      fprintf(stderr, "Streaming Failed\n");
      return 1;
   }
  return 0;
}
