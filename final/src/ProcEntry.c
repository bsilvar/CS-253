/*
 * File: ProcEntry.c
 * Author(s): 
 * Date: 11/30/2021 
 * Description: Definition of ProcEntry struct and declaration
 *   of support functions used in the myps project.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "ProcEntry.h"

/*
typedef struct proc_entry {
     int pid;
     int ppid;
     char *comm;
     char state;
     unsigned long int utime;
     unsigned long int stime;
     long num_threads;
     char *path; 
} ProcEntry;
*/

/* CreateProcEntry: Allocate a ProcEntry struct in the heap using malloc.
 *   All fields will be initialized to zero or NULL based upon data type.
 * 
 * returns - Pointer to ProcEntry allocated on the heap, NULL on error
 */
ProcEntry * CreateProcEntry(void) {
   ProcEntry *newEntry = (ProcEntry*) malloc(sizeof(ProcEntry));
   if(newEntry == NULL) {
      //fprintf(stderr, "Error: malloc failed for ProcEntry\n");
      return NULL;
   }

   newEntry->pid = 0;           
   newEntry->ppid = 0;          
   newEntry->comm = NULL;       
   newEntry->state = 0;         
   newEntry->utime = 0;         
   newEntry->stime = 0;         
   newEntry->num_threads = 0;   
   newEntry->path = NULL;       

   return newEntry;
}

/* CreateProcEntryFromFile: Allocate a ProcEntry struct in the heap 
 *    using malloc and initialize the fields with data provided from
 *    the specified statFile. The command field (comm) and path field 
 *    will be allocated on the heap using malloc. 
 * 
 * The statFile parameter must reference a stat file, formatted as 
 *    described in the /proc manpage entry. The statFile will be
 *    opened and the required fields extract to properly initialize
 *    the ProcEntry struct.
 *
 * If the statFile parameter is NULL or if the file does not exist, 
 *    return NULL. 
 * 
 * If the statFile exists, but an error occurs while attempting to 
 *    extract the field data because is not a properly formatted
 *    stat file, return NULL.
 *  
 * returns - Pointer to ProcEntry allocated on the heap, NULL on error
 */
ProcEntry * CreateProcEntryFromFile(const char statFile[]) {
   if(statFile == NULL) {
      //fprintf(stderr, "Error: path to stat file\n");
      return NULL;
   }
   FILE *file = fopen(statFile, "r");
   if(file == NULL) {
      //fprintf(stderr, "Error: opening stat file\n");
      return NULL;
   }
   ProcEntry *newEntry = CreateProcEntry();
   if(newEntry == NULL) {
      DestroyProcEntry(newEntry);
      return NULL;
   }
   newEntry->path = (char*) malloc(sizeof(char) * (strlen(statFile) + 1));
   if(newEntry->path == NULL) {
      //fprintf(stderr, "Error: malloc failed for path\n");
      DestroyProcEntry(newEntry);   
      return NULL;
   }
   strcpy(newEntry->path, statFile);
   newEntry->comm = (char*) malloc(sizeof(char) * 256);
   if(newEntry->comm == NULL) {
      //fprintf(stderr, "Error: malloc failed for comm\n");
      DestroyProcEntry(newEntry);   
      return NULL;
   }
   int fieldsRead = fscanf(file, "%d %s %c %d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu %*d %*d %*d %*d %ld", 
                               &newEntry->pid,
                               newEntry->comm,
                               &newEntry->state,
                               &newEntry->ppid,
                               &newEntry->utime,
                               &newEntry->stime,
                               &newEntry->num_threads);
   if(fieldsRead != 7) {
      //fprintf(stderr, "Error: stat fields weren't properly read\n");
      DestroyProcEntry(newEntry);
      return NULL;
   }

   fclose(file);

  return newEntry;
}

/* DestroyProcEntry: Release memory allocated by malloc in the
 *    CreateProcEntry or CreateProcEntryFromFile functions.  
 *    Does nothing if thisNode is NULL.
 * 
 * entry - Pointer to ProcEntry object to be freed.
 */
void DestroyProcEntry(ProcEntry *entry) {
   if(entry == NULL) {
      return;
   }
   if(entry->comm != NULL) {
      free(entry->comm);
   }
   if(entry->path != NULL) {
      free(entry->path);
   }
   free(entry);
}

/* PrintProcEntry: Write the fields of the specified ProcEntry
 *    to stdout (console) using the exact format specified
 *    in the project guide.
 * 
 * entry - Pointer to ProcEntry object to be displayed
 */
void PrintProcEntry(ProcEntry *entry) {
     unsigned long int utime = entry->utime / sysconf(_SC_CLK_TCK);
     unsigned long int stime = entry->stime / sysconf(_SC_CLK_TCK);
     fprintf(stdout, "%7d %7d %5c %5lu %5lu %7ld %-25s %-20s\n",
             entry->pid,
             entry->ppid,
             entry->state,
             utime,
             stime,
             entry->num_threads,
             entry->comm,
             entry->path);
}
