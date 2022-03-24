#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ContactNode.h"

/*
struct ContactNode_struct {
   char contactName[CONTACT_FIELD_SIZE];
   char contactPhoneNum[CONTACT_FIELD_SIZE];
   struct ContactNode_struct* nextNodePtr;
};
typedef struct ContactNode_struct ContactNode;
*/

/* CreateContactNode: Allocate a ContactNode object in the heap using malloc
 *    the object will be initialized with the specified name and phone number
 *    and the nextNodePtr field will be set to NULL;
 * name - NULL terminated string containing contact name
 * phoneNum - NULL terminated string containing contact phone number
 * returns - Pointer to ContactNode object allocated on the heap
 */
ContactNode* CreateContactNode(char name[], char phoneNumInit[]) {
   if(NULL == name || NULL == phoneNumInit) {
      return NULL;
   }
   ContactNode* newNode = (ContactNode*) malloc(sizeof(ContactNode));
   if(NULL == newNode) {
      return NULL;
   }
   strcpy(newNode->contactName, name);
   strcpy(newNode->contactPhoneNum, phoneNumInit);
   newNode->nextNodePtr = NULL;
  return newNode;
}

/* InsertContactAfter: Insert a new ConactNode into the linked list
 *    immediately after the specified node. 
 * nodeInList - Pointer to the ContactNode that the new ContactNode 
 *                  should be inserted after in the list
 * newNode - Pointer to the new ContactNode to be added
 * returns - 0 on success, -1 on error
 */
int InsertContactAfter(ContactNode* nodeInList, ContactNode* newNode) {
   if(NULL == nodeInList || NULL == newNode) {
      return -1;
   }
   if(NULL != nodeInList->nextNodePtr) {
      return -1;
   }
   if(nodeInList == newNode) {
      return -1;
   }
   nodeInList->nextNodePtr = newNode;
  return 0;
}

/* GetNextContact: Return a pointer to the ContactNode that immediately
 *     follows the specified node in the list
 * nodeInList - Pointer to ContactNode that we want to get the next node of
 * returns - Pointer to next ContactNode, NULL on error or end of list
 */
ContactNode* GetNextContact(ContactNode* nodeInList) {
   if(NULL == nodeInList) {
      return NULL;
   }
  return nodeInList->nextNodePtr;
}

/* PrintContactNode: Write the fields of the ContactNode, nicely formatted,
 *     to stdout (console) using printf. 
 * thisNode - Pointer to ContactNode object to be displayed */
void PrintContactNode(ContactNode* thisNode) {
   if(NULL == thisNode) {
      return;
   }
   printf("Name: %s\n", thisNode->contactName);
   printf("Phone number: %s\n\n", thisNode->contactPhoneNum);
  return;
}

/* DestroyContactNode: Release memory allocated by malloc in the
 *    CreateContactNode function.  Does nothing if thisNode is NULL
 * thisNode - Pointer to ContactNode object to be freed.
 */
void DestroyContactNode(ContactNode* thisNode) {
   if(NULL == thisNode) {
      return;
   }
   free(thisNode);
   thisNode = NULL;
  return;
}
