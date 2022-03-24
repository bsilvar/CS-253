#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "ItemToPurchase.h"

#define BASE 10
#define MAX_ITEMS 2
#define MAX_ITEM_NAME 50

int main(void) {
   ItemToPurchase item[MAX_ITEMS];
   char buffer[BASE];
   char* endptr;
   long value;
   for(int i = 0; i < MAX_ITEMS; i++) {
      MakeItemBlank(&item[i]);
      printf("Item %d\n", i+1);
      // ITEM NAME
      printf("Enter the item name:\n");
      if(NULL == fgets(item[i].itemName, MAX_ITEM_NAME, stdin)) {
         return 1;
      }
      char* ptr = strstr(item[i].itemName, "\n");
      if(NULL != ptr) {
         *ptr = '\0';
      }
      ptr = strstr(item[i].itemName, "\r");
      if(NULL != ptr) {
         *ptr = '\0';
      }
      // ITEM PRICE
      printf("Enter the item price:\n");
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
      item[i].itemPrice = (int) value;
      // ITEM QUANTITY
      printf("Enter the item quantity:\n");
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
      item[i].itemQuantity = (int) value;
      printf("\n");
   }
   int total = 0;
   printf("TOTAL COST\n");
   for(int i = 0; i < MAX_ITEMS; i++) {
      PrintItemCost(item[i]);
      total += item[i].itemPrice * item[i].itemQuantity;
   }
   printf("\nTotal: $%d\n", total);
  return 0;
}
