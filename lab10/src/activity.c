#include<stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "../include/Student.h"

int main(int argc, char** argv) {
   int arrSize = 8;
   if(argc != 2) {
      fprintf(stderr, "Usage: bin/activity <gradebook.csv>\n");
      return 1;
   }
   
   FILE *gradebookFile = fopen(argv[1], "r");
   if(gradebookFile == NULL) {
      perror("fopen");      
      return 1;
   }

   Student **studentList = (Student**) malloc(sizeof(Student*) * arrSize);
   if(NULL == studentList) {
      fclose(gradebookFile);
      fprintf(stderr, "Malloc failed\n");
      return 1;
   }

   int MAX_FIELD_SIZE = 20;
   char lastName[MAX_FIELD_SIZE];
   char firstName[MAX_FIELD_SIZE];
   int id;
   int score;
   int fieldsRead;
   int studentsRead = 0;
   int newSize = 0;

   while(!feof(gradebookFile)) {
      fieldsRead = fscanf(gradebookFile, "%19[^,],%19[^,],%d,%d\n",
                                        lastName, firstName, &id, &score);
      if(fieldsRead == 4) {
         studentList[studentsRead] = CreateStudent(lastName, firstName, id, score);
         studentsRead++;
      } else {
         fprintf(stderr, "Error: Only read %d of 4\n", fieldsRead);
      }
      if(studentsRead == arrSize) {
         newSize = arrSize * 2;
         printf("Growing Array: %d -> %d\n", arrSize, newSize); 
         arrSize = newSize;
       //studentList = (Student**) realloc(studentList, sizeof(Student*) * arrSize) 
         studentList = realloc(studentList, sizeof(Student*) * arrSize);
         if(NULL == studentList) {
            fclose(gradebookFile);		 
            fprintf(stderr, "Realloc failed\n");		 
            return 1;		 
         }
      }
   }

   fclose(gradebookFile);
   printf("Successfully loaded %d Students!\n", studentsRead);

   qsort(studentList, studentsRead, sizeof(Student*), CompareStudents);

   for(int i = 0; i < studentsRead; i++) {
      PrintStudent(studentList[i]);
      DestroyStudent(studentList[i]);
   }

   free(studentList);

  return 0;
}
