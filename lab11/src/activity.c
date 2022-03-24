/* 
 * Author: Luke Hindman
 * Date: Thu 05 Nov 2020 08:10:44 AM PST
 * Description:  Adapted from the Simple Directory Lister Mark II example
 *    provided in the libc manual.
 * https://www.gnu.org/software/libc/manual/html_node/Simple-Directory-Lister-Mark-II.html
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>

#define UNUSED(x) (void)x

static int one (const struct dirent *current) {
   UNUSED(current);
  return 1;
}


void usage(void) {
   printf("Usage: bin/myls [-d <path>] [-s] [-a] [-f] [-r]\n");
   printf("\t-d <path> Directory to list the contents of\n");
   printf("\t-a        Display all files, including hidden files\n");
   printf("\t-f        Display only regular files\n");
   printf("\t-r        Display entries alphabetically in descending order\n");
   printf("\t-s        Display entries alphabetically in ascending order\n");
}

int defaultSort(const struct dirent **eA, const struct dirent **eB) {
   UNUSED(eA);
   UNUSED(eB);
  return 0;
}

int reverseSort(const struct dirent **eA, const struct dirent **eB) {
   int retVal = alphasort(eA,eB) * -1;
  return retVal;
}

int showFilesOnly(const struct dirent *e) {
   if(e->d_type == DT_REG) {
      return 1;
   }
  return 0;
}

int showAll(const struct dirent *e) {
   if(e->d_name[0] != '.') {
      return 1;
   }
  return 0;
}

int main (int argc, char * argv[]) {
   struct dirent **eps;  
   
   int (*filterFunction)(const struct dirent *);
   filterFunction = one;
   int (*sortFunction)(const struct dirent **,const struct dirent **);
   sortFunction = defaultSort;
   int option;
   int n;
   int aflag = 0;
   int fflag = 0;
   int rflag = 0;
   int sflag = 0;
   char *dvalue = "./";

    opterr = 0;
    while((option = getopt(argc, argv, "afhsrd:")) != -1) {
       switch(option) {
       case 'a':
          aflag = 1;
          if(fflag == 0) {
             filterFunction = showAll;
          }
          break;
       case 'd':
          dvalue = optarg;
          break;
       case 'f':
          fflag = 1; 
          if(aflag == 0) { 
             filterFunction = showFilesOnly;
          }
          break;
       case 'r':
          rflag = 1; 
          if(sflag == 0) {
             sortFunction = reverseSort;
          }
          break;
       case 's':
          sflag = 1;
          if(rflag == 0) {
             sortFunction = alphasort;
          }
          break;
       case 'h':
          usage(); 
          exit(0);
       default:
          printf("Usage: %s [-d <path>] [-s] [-a] [-f] [-r]\n", argv[0]);
          return 1;
       }
    }
    // Behavior is undefined for filters
    if(aflag == 1 && fflag == 1) {
       filterFunction = one;
    }
    // Behavior is undefined for sorters 
    if(sflag == 1 && rflag == 1) {
       sortFunction = defaultSort;
    }

    errno = 0;
    n = scandir(dvalue, &eps, filterFunction, sortFunction);
	
    if (n < 0) {
       perror("scandir: ");
       return 1;
    }

    int cnt;
    for (cnt = 0; cnt < n; ++cnt) {
       fprintf(stdout, "%s\n", eps[cnt]->d_name);
    } 

    for (cnt = 0; cnt < n; ++cnt) {
       free(eps[cnt]);
    }

    free (eps);

  return 0;
}
