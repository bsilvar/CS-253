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

int main (int argc, char * argv[]) {
    struct dirent **eps;
    
    int option;
	int n;
	int sort = 0;
	char *dvalue = NULL;

    opterr = 0;
    while((option = getopt(argc, argv, "sd:")) != -1) {
       switch(option) {
       case 'd':
          dvalue = optarg;
          break;
       case 's':
          sort = 1;
          break;
       default:
          printf("Usage: %s [-d <path>] [-s]\n", argv[0]);
          return 1;
       }
    }
    errno = 0;

    /* check if user specified a directory on the command line */
    if (NULL != dvalue) {
       if(sort) {
          n = scandir (dvalue, &eps, one, alphasort);
       } else {
          n = scandir (dvalue, &eps, one, NULL);
       }
    } else {
       /* start in the current directory */
	   if(sort) {
	      n = scandir("./", &eps, one, alphasort);
       } else {
	      n = scandir("./", &eps, one, NULL);
	   }
    }

    /* validate directory was opened successfully */
    if (n < 0) {
        perror("scandir: ");
        return 1;
    }

    int cnt;
    for (cnt = 0; cnt < n; ++cnt) {
        fprintf(stdout,"%s\n", eps[cnt]->d_name);
    }

    for (cnt = 0; cnt < n; ++cnt) {
        free(eps[cnt]);
    }

    free (eps);

  return 0;
}
