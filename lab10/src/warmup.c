#include<stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "../include/Song.h"

int main(int argc, char** argv) {
   int numRecords = 0;

   if(argc != 3) {
      fprintf(stderr, "Usage: bin/warmup <catalog.csv> <size>\n");
      return 1;
   }
   
   FILE *musicFile = fopen(argv[1], "r");
   if(musicFile == NULL) {
      perror("fopen");      
      return 1;
   }
   char *endptr;
   errno = 0;
   long value = strtol(argv[2], &endptr, 10); 
   if(errno != 0) {
      fprintf(stderr, "Error: Invalid size specified: %s\n", argv[2]);
      perror("strtol");
      return 1;
   }
   if(endptr == argv[2]) {
      fprintf(stderr, "Error: Invalid size specified: %s\n", argv[2]);
      perror("strtol");
      return 1;
   }
   numRecords = (int) value;
   Song **songList = (Song**) malloc(sizeof(Song*) * numRecords);
   if(NULL == songList) {
      fclose(musicFile);
      fprintf(stderr, "Malloc failed\n");
      return 1;
   }

   int MAX_FIELD_SIZE = 80;
   char artist[MAX_FIELD_SIZE];
   char album[MAX_FIELD_SIZE];
   char title[MAX_FIELD_SIZE];
   int duration;
   int fieldsRead;
   int recordsRead = 0;

   while(!feof(musicFile) && recordsRead < numRecords) {
      fieldsRead = fscanf(musicFile, "%79[^,],%79[^,],%79[^,],%d\n", 
                                       artist, album, title, &duration);
      if(fieldsRead == 4) {
         songList[recordsRead] = CreateSong(artist, album, title, duration);
         recordsRead++;
      } else {
         fprintf(stderr, "Error: Only read %d of 4\n", fieldsRead);
      }
   }
   fclose(musicFile);
   printf("Successfully loaded %d songs!\n", recordsRead);

   qsort(songList, recordsRead, sizeof(Song*), CompareSongs);

   for(int i = 0; i < recordsRead; i++) {
      PrintSong(songList[i]);
      DestroySong(songList[i]);
   }

   free(songList);
   
  return 0;
}
