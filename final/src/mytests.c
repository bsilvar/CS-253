#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ProcEntry.h"

int testCreateDestroy(void) {
   char testName[] = "Unit Test - Create/Destroy:";
   ProcEntry *testEntry = CreateProcEntry();
   if(testEntry == NULL) {
      fprintf(stderr, "%s failed\n", testName);
      return 1;
   }

   DestroyProcEntry(testEntry);
   fprintf(stderr, "%s passed\n", testName);
  return 0;
}

int testCreateFromFileDestroy(void) {
   char testName[] = "Unit Test - CreateFromFile/Destroy:";
   ProcEntry *testEntry = CreateProcEntryFromFile("./etc/test_data/budgie_proc/1/stat");
   if(testEntry == NULL) {
      fprintf(stderr, "%s failed\n", testName);
      return 1;
   }

   DestroyProcEntry(testEntry);
   fprintf(stderr, "%s passed\n", testName);
  return 0;
}

int testCreateFromFileNull(void) {
   char testName[] = "Unit Test - CreateFromFile NULL:";
   ProcEntry *testEntry = CreateProcEntryFromFile(NULL);
   if(testEntry == NULL) {
      fprintf(stderr, "%s passed\n", testName);
      return 0;
   } else {
      fprintf(stderr, "%s failed\n", testName);
      return 1;
   }
}

int testCreateFromFilePrintDestroy(void) {
   char testName[] = "Unit Test - CreateFromFile/Print/Destroy:";
   ProcEntry *testEntry = CreateProcEntryFromFile("./etc/test_data/budgie_proc/1/stat");
   if(testEntry == NULL) {
      fprintf(stderr, "%s failed\n", testName);
      return 1;
   } 
   PrintProcEntry(testEntry);
   DestroyProcEntry(testEntry);
   fprintf(stderr, "%s passed\n", testName);
  return 0;
}

int testCreateFromFileBlah(void) {
   char testName[] = "Unit Test - CreateFromFile BLAH:";
   ProcEntry *testEntry = CreateProcEntryFromFile("./etc/test_data/budgie_proc/blah/stat");
   if(testEntry == NULL) {
      fprintf(stderr, "%s passed\n", testName);
      return 1;
   }

   fprintf(stderr, "%s failed\n", testName);
  return 0;
}

int testFields(void) {
   char testName[] = "Unit Test - Fields Read:";
   ProcEntry *testEntryOne = CreateProcEntryFromFile("./etc/test_data/budgie_proc/1/stat");
   if(testEntryOne == NULL) {
      fprintf(stderr, "%s failed\n", testName);
      return 1;
   }

   if(testEntryOne->comm != NULL && 
      testEntryOne->pid == 1 && 
      testEntryOne->state == 'S' && 
      testEntryOne->ppid == 0 && 
      testEntryOne->utime != 0 && 
      testEntryOne->stime != 0 && 
      testEntryOne->num_threads == 1) 
   {
      fprintf(stderr, "%s passed\n", testName);  
      DestroyProcEntry(testEntryOne);
      return 0;
   } else {
      DestroyProcEntry(testEntryOne);
      fprintf(stderr, "%s failed\n", testName);
      return 1;
   }
}

int runall(void) {
   int status = 0;
   status += testCreateDestroy();
   status += testCreateFromFileDestroy();
   status += testCreateFromFileNull();
   status += testCreateFromFilePrintDestroy();
   status += testCreateFromFileBlah();
   status += testFields(); 
  return status;
}

int main(void) {
   int status = 0;

   status = runall();

  return status;
}
