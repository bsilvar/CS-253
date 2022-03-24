#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "PlaylistNode.h"

#define MAX_SIZE 50
#define BASE 10

char PrintMenu(char title[]) {
   char option;
   printf("\n%s PLAYLIST MENU\n", title);
   printf("a - Add song\n");
   printf("r - Remove song\n");
   printf("c - Change position of song\n");
   printf("s - Output songs by specific artist\n");
   printf("t - Output total time of playlist (in seconds)\n");
   printf("o - Output full playlist\n");
   printf("q - Quit\n");
   printf("\nChoose an option:\n");
   scanf(" %c", &option);
   while(!(option == 'a' || option == 'r' || option == 'c' || option == 's' 
        || option == 't' || option == 'o' || option == 'q' )) {
      printf("Choose an option:\n");
      scanf(" %c", &option);
   }
   fgetc(stdin); // fix scanf's '\n'
  return option;
}

int main(void) {
   PlaylistNode* headNode = NULL;
   PlaylistNode* currNode = NULL;
   PlaylistNode* tailNode = NULL;
   char title[MAX_SIZE];
   char buffer[BASE];
   char option;
   char* endptr;
   char* ptr;
   long value;
   printf("Enter playlist's title:\n");
   if(NULL == fgets(title, MAX_SIZE, stdin)) {
      return 1;
   }
   ptr = strstr(title, "\n");
   if(NULL != ptr) {
      *ptr = '\0';
   }
   ptr = strstr(title, "\r");
   if(NULL != ptr) {
      *ptr = '\0';
   }
   do {
      option = PrintMenu(title);
      int found;
      int songLength;
      char id[MAX_SIZE];
      char songName[MAX_SIZE];
      char artistName[MAX_SIZE];
      //ADD SONG
      if(option == 'a') { 
         printf("ADD SONG\n");      
         //SONG ID
         printf("Enter song's unique ID:\n");      
         if(NULL == fgets(id, MAX_SIZE, stdin)) {
            return 1;
         }
         ptr = strstr(id, "\n");
         if(NULL != ptr) {
            *ptr = '\0';
         }
         ptr = strstr(id, "\r");
         if(NULL != ptr) {
            *ptr = '\0';
         }
         //SONG NAME
         printf("Enter song's name:\n");      
         if(NULL == fgets(songName, MAX_SIZE, stdin)) {
            return 1;
         }
         ptr = strstr(songName, "\n");
         if(NULL != ptr) {
            *ptr = '\0';
         }
         ptr = strstr(songName, "\r");
         if(NULL != ptr) {
            *ptr = '\0';
         }
         //ARTIST NAME
         printf("Enter artist's name:\n");      
         if(NULL == fgets(artistName, MAX_SIZE, stdin)) {
            return 1;
         }
         ptr = strstr(artistName, "\n");
         if(NULL != ptr) {
            *ptr = '\0';
         }
         ptr = strstr(artistName, "\r");
         if(NULL != ptr) {
            *ptr = '\0';
         }
         //SONG LENGTH
         printf("Enter song's length (in seconds):\n");
         if(NULL == fgets(buffer, BASE, stdin)) {
            return 1;
         }
         errno = 0;
         value = strtol(buffer, &endptr, BASE);
         if(errno != 0) {
            perror("strtol");
            return 1;   
         }
         if(endptr == buffer) {
            fprintf(stderr, "No digits were found\n");
            return 1;
         }
         songLength = (int) value;
         if(headNode == NULL) {
            headNode = CreatePlaylistNode(id, songName, artistName, songLength);
            tailNode = headNode;
         } else {
            currNode = CreatePlaylistNode(id, songName, artistName, songLength);
            int rval = InsertPlaylistNodeAfter(tailNode, currNode);
            if(rval == -1) {
               return 1;
            } else {
               tailNode = currNode;
            }
         }
      }
      //REMOVE SONG
      if(option == 'r') {
         if(headNode == NULL) {
            printf("Playlist is empty\n");
         } else {
            found = 0;
            printf("REMOVE SONG\n");
            printf("Enter song's unique ID:\n");
            if(NULL == fgets(id, MAX_SIZE, stdin)) {
               return 1;
            }
            ptr = strstr(id, "\n");
            if(NULL != ptr) {
               *ptr = '\0';
            }
            ptr = strstr(id, "\r");
            if(NULL != ptr) {
               *ptr = '\0';
            }
            currNode = headNode;
            PlaylistNode* prevNode = currNode;
            while(NULL != currNode) {
               if(0 == strcmp(currNode->uniqueID, id)) {
                  found = 1;
                  if(currNode == headNode) { 
                  //REMOVING HEAD NODE
                     headNode = GetNextPlaylistNode(headNode);
                     printf("\"%s\" removed\n", currNode->songName);
                     DestroyPlaylistNode(currNode);
                     currNode = NULL;
                  } else if(currNode == tailNode) { 
                  //REMOVING TAIL NODE
                     tailNode = prevNode;
                     tailNode->nextNodePtr = NULL; 
                     printf("\"%s\" removed\n", currNode->songName);
                     DestroyPlaylistNode(currNode);
                     currNode = NULL;
                  } else {                          
                  //REMOVING IN BETWEEN NODE
                     prevNode->nextNodePtr = currNode->nextNodePtr;
                     printf("\"%s\" removed\n", currNode->songName);
                     DestroyPlaylistNode(currNode);
                     currNode = NULL;
                  }
               }
               prevNode = currNode;
               currNode = GetNextPlaylistNode(currNode);
            }
            if(found == 0) {
               printf("Error: song not found\n");
            }
         }
      }
      //CHANGE POSITION OF SONG
      if(option == 'c') { 
         if(headNode == NULL) {
            printf("Playlist is empty\n");
         } else {
            int newPos;
            int currPos;
            int numOfNodes = 0;
            //Calculating number of NODES
            currNode = headNode;
            while(currNode != NULL) {
               numOfNodes++;
               currNode = GetNextPlaylistNode(currNode);
            }
            printf("CHANGE POSITION OF SONG\n");
            printf("Enter song's current position:\n");
            if(NULL == fgets(buffer, BASE, stdin)) {
               return 1;
            }
            errno = 0;
            value = strtol(buffer, &endptr, BASE);
            if(errno != 0) {
               perror("strtol");
               return 1;   
            }
            if(endptr == buffer) {
               fprintf(stderr, "No digits were found\n");
               return 1;
            }
            currPos = (int) value;
            //Checking valid input for current position
            while(currPos < 1 || currPos > numOfNodes) {
               printf("Enter a valid position:\n");
               if(NULL == fgets(buffer, BASE, stdin)) {
                  return 1;
               }
               errno = 0;
               value = strtol(buffer, &endptr, BASE);
               if(errno != 0) {
                  perror("strtol");
                  return 1;   
               }
               if(endptr == buffer) {
                  fprintf(stderr, "No digits were found\n");
                  return 1;
               }
               currPos = (int) value;
            }
            printf("Enter new position for song:\n");
            if(NULL == fgets(buffer, BASE, stdin)) {
               return 1;
            }
            errno = 0;
            value = strtol(buffer, &endptr, BASE);
            if(errno != 0) {
               perror("strtol");
               return 1;   
            }
            if(endptr == buffer) {
               fprintf(stderr, "No digits were found\n");
               return 1;
            }
            newPos = (int) value;
            //Check if node is already in desired position 
            if(newPos == currPos) {
               printf("already in desired position\n");
            } else {
               if(newPos < 1) {
                  newPos = 1;
               }
               if(newPos > numOfNodes) {
                  newPos = numOfNodes;
               }
               if(newPos == currPos) {
                  printf("already in desired position\n");
               } else {
                  int index = 1;
                  currNode = headNode;
                  PlaylistNode* oldNode = NULL; // Ptr to the MOVING node
                  PlaylistNode* newNode = NULL; // Ptr to the NEW position for MOVING NODE
                  PlaylistNode* nodeLeftOfOld;  // Ptr to node left of MOVING node
                  PlaylistNode* nodeLeftOfNew;  // Ptr to node left of node in NEW position
                  PlaylistNode* prvNode = currNode;
                  //Assigning the Ptrs above
                  while(currNode != NULL) {
                     if(index == currPos) { 
                        nodeLeftOfOld = prvNode; 
                        oldNode = currNode;
                        strcpy(songName, oldNode->songName);
                     }
                     if(index == newPos) {  
                        nodeLeftOfNew = prvNode; 
                        newNode = currNode;
                     }
                     prvNode = currNode;
                     currNode = GetNextPlaylistNode(currNode);
                     index++;
                  }
                  //CHANGING NODE POSITION
                  if(oldNode == headNode) { 
                  /*The moving node is the HEAD node*/
                     if(newNode == tailNode) {
                        //New position is @ the TAIL
                        headNode = GetNextPlaylistNode(headNode);
                        tailNode->nextNodePtr = oldNode;
                        tailNode = oldNode;
                     } else { 
                        //New position is anywhere else
                        headNode = GetNextPlaylistNode(headNode);
                        oldNode->nextNodePtr = newNode->nextNodePtr;
                        newNode->nextNodePtr = oldNode;
                     }
                  } else if(oldNode == tailNode) { 
                  /*The moving node is the TAIL node*/
                     if(newNode == headNode) { 
                        //New position is @ the HEAD
                        tailNode = nodeLeftOfOld;
                        oldNode->nextNodePtr = headNode; 
                        headNode = oldNode; 
                     } else { 
                        //New position is anywhere else
                        tailNode = nodeLeftOfOld;
                        nodeLeftOfNew->nextNodePtr = oldNode;
                        oldNode->nextNodePtr = newNode;
                     }          
                  } else {  
                  /*The moving node is BETWEEN the head & tail*/
                     if(newNode == headNode) { 
                        //New position is @ the HEAD
                        nodeLeftOfOld->nextNodePtr = oldNode->nextNodePtr;
                        oldNode->nextNodePtr = headNode; 
                        headNode = oldNode; 
                     } else if(newNode == tailNode) { 
                        //New position is @ the TAIL
                        nodeLeftOfOld->nextNodePtr = oldNode->nextNodePtr;
                        tailNode->nextNodePtr = oldNode; 
                        tailNode = oldNode; 
                     } else { 
                        //New position is anywhere else
                        PlaylistNode* nodeNextToOld; 
                        PlaylistNode* nodeNextToNew; 
                        if(currPos < newPos) { 
                           //Moving DOWN the list
                           nodeNextToOld = oldNode->nextNodePtr; 
                           nodeNextToNew = newNode->nextNodePtr; 
                           if(nodeNextToOld == newNode) { 
                              //Next to each other
                              nodeLeftOfOld->nextNodePtr = newNode;
                              oldNode->nextNodePtr = nodeNextToNew;
                              newNode->nextNodePtr = oldNode;
                           } else {
                              nodeLeftOfOld->nextNodePtr = newNode;
                              newNode->nextNodePtr = nodeNextToOld;
                              nodeLeftOfNew->nextNodePtr = oldNode;
                              oldNode->nextNodePtr = nodeNextToNew;
                           }
                        }
                        if(currPos > newPos) { 
                           //Moving UP the list
                           nodeNextToOld = oldNode->nextNodePtr;
                           nodeNextToNew = newNode->nextNodePtr;
                           if(nodeLeftOfOld == newNode) { 
                              //Next to each other
                              nodeLeftOfNew->nextNodePtr = oldNode;
                              newNode->nextNodePtr = nodeNextToOld;
                              oldNode->nextNodePtr = newNode;
                           } else {
                              nodeLeftOfNew->nextNodePtr = oldNode;
                              oldNode->nextNodePtr = nodeNextToNew;
                              nodeLeftOfOld->nextNodePtr = newNode;
                              newNode->nextNodePtr = nodeNextToOld;
                           }
                        }
                     } 
                  }
                  tailNode->nextNodePtr = NULL; 
                  printf("\"%s\" moved to position %d\n", songName, newPos);			  
               }
            }
         }
      }
      //OUTPUT SONG BY SPECIFIC ARTIST
      if(option == 's') { 
         if(headNode == NULL) {
            printf("Playlist is empty\n");
         } else {
            found = 0;
            printf("OUTPUT SONGS BY SPECIFIC ARTIST\n");
            printf("Enter artist's name:\n");
            if(NULL == fgets(artistName, MAX_SIZE, stdin)) {
               return 1;
            }
            ptr = strstr(artistName, "\n");
            if(NULL != ptr) {
               *ptr = '\0';
            }
            ptr = strstr(artistName, "\r");
            if(NULL != ptr) {
               *ptr = '\0';
            }
            currNode = headNode;
            int count = 1;
            while(NULL != currNode) {
               if(0 == strcmp(currNode->artistName, artistName)) {
                  found = 1;
                  printf("\n%d.\n", count);
                  PrintPlaylistNode(currNode);
               }
               currNode = GetNextPlaylistNode(currNode);
               count++;
            }
            if(found == 0) {
               printf("Error: artist not found\n");
            }
         }
      }
      //OUTPUT TOTAL TIME OF PLAYLIST
      if(option == 't') { 
         if(headNode == NULL) {
            printf("Playlist is empty\n");
         } else {
            int total = 0;
            currNode = headNode;
            while(currNode != NULL) {
               total += currNode->songLength;  
               currNode = GetNextPlaylistNode(currNode);
            }
            printf("OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)\n");
            printf("Total time: %d seconds\n", total);
         }
      }
      //OUTPUT FULL PLAYLIST
      if(option == 'o') { 
         if(headNode == NULL) {
            printf("Playlist is empty\n");
         } else {
            int songNum = 1;
            currNode = headNode;
            printf("%s - OUPUT FULL PLAYLIST", title);
            while(NULL != currNode) {
               printf("\n%d.\n", songNum);
               PrintPlaylistNode(currNode);
               currNode = GetNextPlaylistNode(currNode);
               songNum++;
            }
         }
      }
   } while(option != 'q');
   //CLEAN UP
   currNode = headNode;
   while(currNode != NULL) {
      PlaylistNode* prevNode = currNode;
      currNode = GetNextPlaylistNode(currNode);
      DestroyPlaylistNode(prevNode);
   }
  return 0;
}
