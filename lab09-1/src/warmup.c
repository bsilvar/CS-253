#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "ContactNode.h"

#define MAX_CONTACTS 3
#define MAX_SIZE 50

int main(void) {
   ContactNode* headNode = NULL;
   ContactNode* currNode = NULL;
   ContactNode* tailNode = NULL;
   for(int i = 0; i < MAX_CONTACTS; i++) {
      char name[MAX_SIZE];
      char phone[MAX_SIZE];
      char* ptr;
      printf("Person %d\n", i+1);
      //NAME
      printf("Enter name:\n");
      if(NULL == fgets(name, MAX_SIZE, stdin)) {
         return 1;
      }
      ptr = strstr(name, "\n");
      if(NULL != ptr) {
         *ptr = '\0';
      }
      ptr = strstr(name, "\r");
      if(NULL != ptr) {
         *ptr = '\0';
      }
      //PHONE #
      printf("Enter phone number:\n");
      if(NULL == fgets(phone, MAX_SIZE, stdin)) {
         return 1;
      }
      ptr = strstr(phone, "\n");
      if(NULL != ptr) {
         *ptr = '\0';
      }
      ptr = strstr(phone, "\r");
      if(NULL != ptr) {
         *ptr = '\0';
      }
      //SUMMARY
      printf("You entered: %s, %s\n\n", name, phone);
      if(headNode == NULL) {
         headNode = CreateContactNode(name, phone);
         tailNode = headNode;
      } else {
         currNode = CreateContactNode(name, phone);
         int rval = InsertContactAfter(tailNode, currNode);
         if(rval == 0) {
            tailNode = currNode;
         } else {
            return -1;
         }
      }
   }
   //Print/Destroy each ContactNode
   ContactNode* prevNode;
   currNode = headNode;
   printf("\nCONTACT LIST\n");
   while(currNode != NULL) {
      PrintContactNode(currNode);
      prevNode = currNode;
      currNode = GetNextContact(currNode);
      DestroyContactNode(prevNode);
   }
   headNode = NULL;
   tailNode = NULL;
  return 0;
}
