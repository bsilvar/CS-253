/* 
 * Author: Brayan Silva
 * Date: 11/30/2021
 * Description: Code for final project (myps)
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include "ProcEntry.h"

#define MAX_FILEPATH_SIZE 4096
#define UNUSED(x) (void)x

void helpMessg(void) {
   printf("Usage: bin/myps [-d <path>] [-p] [-c] [-z] [-h]\n");
   printf("\t-d <path> Directory containing proc entries (default: /proc)\n");
   printf("\t-p        Display proc entries sorted by pid (default)\n");
   printf("\t-c        Display proc entries sorted by command lexicographically\n");
   printf("\t-z        Display ONLY proc entries in the zombie state\n");
   printf("\t-h        Display this help message\n");
}

void usage(void) {
   fprintf(stderr, "Usage: bin/myps [-d <path>] [-p] [-c] [-z] [-h]\n");
}

int noSort(const struct dirent **eA, const struct dirent **eB) {
   UNUSED(eA);
   UNUSED(eB);
  return 0;
}

int commSort(const void *a, const void *b) {
   ProcEntry *f = *(ProcEntry **)a;
   ProcEntry *s = *(ProcEntry **)b;
   int rval = strcmp(f->comm, s->comm);
  return rval; 
}

static int pidSort(const void *a, const void *b) {
     ProcEntry *f = *(ProcEntry **)a;
     ProcEntry *s = *(ProcEntry **)b;
     int rval = f->pid - s->pid;
     return rval;
}

int dirFilter(const struct dirent *e) { 
   if(e->d_type == DT_DIR && isdigit(e->d_name[0])) {
      return 1;
   }
  return 0;
}

int main (int argc, char * argv[]) {
   struct dirent **eps; // array of dirent struct pointers

   int (*filterFunction)(const struct dirent *);
   filterFunction = dirFilter;
   int (*sortFunction)(const struct dirent **,const struct dirent **);
   sortFunction = noSort;

   int n;
   int option;
   int pflag = 0;
   int cflag = 0;
   int zflag = 0;
   int hflag = 0;
   char filePath[MAX_FILEPATH_SIZE] = "/proc";
   
   while((option = getopt(argc, argv, "d:pczh")) != -1) {
      switch(option) {
      case 'd':
          strcpy(filePath, optarg);
          break;
      case 'p':
          pflag = 1;
          break;
      case 'c':
          cflag = 1;
          break;
      case 'z':
          zflag = 1;
          break;
      case 'h':
          hflag = 1;
          break;
      default:
          usage();
          return 1;
      }
   }
   if(hflag) {
      helpMessg();
      return 0;
   }

   errno = 0;
   n = scandir(filePath, &eps, filterFunction, sortFunction);
   if(n < 0) {
      perror("scandir: ");
      return 1;
   }

   ProcEntry **myprocs = (ProcEntry**) malloc(sizeof(ProcEntry*) * n); // array of ProcEntry struct pointers

   for(int i = 0; i < n; i++) {
      int pathSize = strlen(filePath) + strlen(eps[i]->d_name) + 7;
      char path[pathSize];
      strcpy(path, filePath);
      strcat(path, "/");    
      strcat(path, eps[i]->d_name);
      strcat(path, "/stat");      
      myprocs[i] = CreateProcEntryFromFile(path);
      if(myprocs[i] == NULL) {
         myprocs[i] = myprocs[i-1];
      }
   }

   if(cflag) {
      qsort(myprocs, n, sizeof(ProcEntry*), commSort);
   } else if(pflag) {
      qsort(myprocs, n, sizeof(ProcEntry*), pidSort);
   } else {
      qsort(myprocs, n, sizeof(ProcEntry*), pidSort);
   }

   fprintf(stdout,"%7s %7s %5s %5s %5s %7s %-25s %-20s\n","PID","PPID","STATE","UTIME","STIME","THREADS","CMD","STAT_FILE");
   for(int i = 0; i < n; i++) {
      if(zflag && myprocs[i]->state == 'Z') {
         PrintProcEntry(myprocs[i]);
      } 
      if(!zflag) {
         PrintProcEntry(myprocs[i]);
      }
      free(eps[i]);
      // prevent double free
      if(i == n-1) {
         DestroyProcEntry(myprocs[i]);
      } else {
         if(myprocs[i] != myprocs[i+1]) {
            DestroyProcEntry(myprocs[i]);
         }  
      }
   }

   free(eps);
   free(myprocs);

  return 0;
}
