#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PlaylistNode.h"

/*
struct PlaylistNode_struct {
   char uniqueID[50];
   char songName[50];
   char artistName[50];
   int songLength;
   struct PlaylistNode_struct* nextNodePtr;
};
typedef struct PlaylistNode_struct PlaylistNode;
*/

/* CreatePlaylistNode: Allocate a PlaylistNode in the heap using malloc
 *    the object will be initialized with the specified unique id, song name,
 *    artist name and song length. The nextNodePtr field will be set to NULL;
 * id - NULL terminated string containing unique id
 * songName - NULL terminated string containing the song name
 * artistName - NULL terminated string containing the name of the artist
 * songLength - int value with duration of song in seconds
 * 
 * returns - Pointer to PlaylistNode allocated on the heap
 */
PlaylistNode* CreatePlaylistNode(char id[], char songName[], char artistName[], int songLength) {
   if(NULL == id || NULL == songName || NULL == artistName || songLength == 0) {
      return NULL;
   }
   PlaylistNode* newNode = (PlaylistNode*) malloc(sizeof(PlaylistNode));
   if(NULL == newNode) {
      return NULL;
   }
   strcpy(newNode->uniqueID, id);
   strcpy(newNode->songName, songName);
   strcpy(newNode->artistName, artistName);
   newNode->songLength = songLength;
   newNode->nextNodePtr = NULL;
  return newNode;
}

/* InsertPlaylistNodeAfter: Insert a new PlaylistNode into the linked list
 *    immediately after the specified node. 
 * nodeInList - Pointer to the PlaylistNode that the new PlaylistNode 
 *                  should be inserted after in the list
 * newNode - Pointer to the new PlaylistNode to be added
 * returns - 0 on success, -1 on error
 */
int InsertPlaylistNodeAfter(PlaylistNode* nodeInList, PlaylistNode* newNode) {
   if(NULL == nodeInList || NULL == newNode) {
      return -1;
   }
   if(newNode == nodeInList) {
      return -1;
   }
   if(NULL != nodeInList->nextNodePtr) {
      return -1;
   }
   nodeInList->nextNodePtr = newNode;
  return 0;
}

/* SetNextPlaylistNode: Update the nextNodePtr field of the specified nodeInList 
 *     to point to newNode.  It is valid for newNode to be NULL, but not nodeInList.
 * nodeInList - Pointer to PlaylistNode whose nextNodePtr field will be updated
 * newNode - Pointer PlaylistNode to be set in the nextNodePtr
 * returns - 0 on success, -1 on error
 */
int SetNextPlaylistNode(PlaylistNode* nodeInList, PlaylistNode* newNode) {
   if(NULL == nodeInList) {
      return -1;
   }
   if(newNode == nodeInList) {
      return -1;
   }
   if(NULL != nodeInList->nextNodePtr) {
      return -1;
   }
   nodeInList->nextNodePtr = newNode;
  return 0;
}

/* GetNextPlaylistNode: Return a pointer to the PlaylistNode that immediately
 *     follows the specified node in the list
 * nodeInList - Pointer to PlaylistNode that we want to get the next node of
 * returns - Pointer to next PlaylistNode, NULL on error or end of list
 */
PlaylistNode* GetNextPlaylistNode(PlaylistNode* nodeInList) {
   if(NULL == nodeInList) {
      return NULL;
   }
  return nodeInList->nextNodePtr;
}

/* PrintPlaylistNode: Write the fields of the PlaylistNode, nicely formatted,
 *     to stdout (console) using printf. 
 * thisNode - Pointer to PlaylistNode object to be displayed */
void PrintPlaylistNode(PlaylistNode* thisNode) {
   printf("Unique ID: %s\n", thisNode->uniqueID);
   printf("Song Name: %s\n", thisNode->songName);
   printf("Artist Name: %s\n", thisNode->artistName);
   printf("Song Length (in seconds): %d\n", thisNode->songLength);
  return;
}

/* DestroyPlaylistNode: Release memory allocated by malloc in the
 *    CreatePlaylistNode function.  Does nothing if thisNode is NULL
 * thisNode - Pointer to PlaylistNode object to be freed.
 */
void DestroyPlaylistNode(PlaylistNode* thisNode) {
   if(NULL == thisNode) {
      return;
   }
   free(thisNode);
   //thisNode = NULL;
  return;
}
