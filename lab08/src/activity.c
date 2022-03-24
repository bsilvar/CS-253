#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "ItemToPurchase.h"
#include "ShoppingCart.h"
#define BASE 10
#define MAX_SIZE 50
#define MAX_DESC 80

char PrintMenu(void) {
   char option;
   printf("\nPROGRAM MENU\n");
   printf("a - Add item to cart\n");
   printf("r - Remove item from cart\n");
   printf("c - Change item quantity\n");
   printf("i - Output item's descriptions\n");
   printf("o - Output shopping cart\n");
   printf("q - Quit\n");
   printf("\nChoose an option:\n");
   scanf(" %c", &option);
   while(!(option == 'a' || option == 'r' || option == 'c' || 
           option == 'i' || option == 'o' || option == 'q' )) {
      printf("Choose an option:\n");
      scanf(" %c", &option);
   }
   fgetc(stdin); // gets rid of '\n' in scanf
  return option;
}

int main(void) {
   ShoppingCart cart;
   cart.cartSize = 0;
   char buffer[BASE];
   char option;
   char* endptr;
   char* ptr;
   long value;
   //NAME
   printf("Enter Customer's Name:\n");
   if(NULL == fgets(cart.customerName, MAX_SIZE, stdin)) {
      return 1;
   }
   ptr = strstr(cart.customerName, "\n");
   if(NULL != ptr) {
      *ptr = '\0';
   }
   ptr = strstr(cart.customerName, "\r");
   if(NULL != ptr) {
      *ptr = '\0';
   }
   //DATE
   printf("Enter Today's Date:\n");
   if(NULL == fgets(cart.currentDate, MAX_SIZE, stdin)) {
      return 1;
   }
   ptr = strstr(cart.currentDate, "\n");
   if(NULL != ptr) {
      *ptr = '\0';
   }
   ptr = strstr(cart.currentDate, "\r");
   if(NULL != ptr) {
      *ptr = '\0';
   }
   printf("\nCustomer Name: %s\n", cart.customerName);
   printf("Today's Date: %s\n", cart.currentDate);
   do {
      option = PrintMenu();
      if(option == 'a') { //ADD
         if (cart.cartSize == 10) {
            printf("Error: ShoppingCart is full\n");
         } else {
            printf("ADD ITEM TO CART\n");
            ItemToPurchase item;
            //NAME
            printf("Enter the item name:\n");
            if(NULL == fgets(item.itemName, MAX_SIZE, stdin)) {
               return 1;
            }
            ptr = strstr(item.itemName, "\n");
            if(NULL != ptr) {
               *ptr = '\0';
            }
            ptr = strstr(item.itemName, "\r");
            if(NULL != ptr) {
               *ptr = '\0';
            }
            //DESCRIPTION
            printf("Enter the item description:\n");
            if(NULL == fgets(item.itemDescription, MAX_DESC, stdin)) {
               return 1;
            }
            ptr = strstr(item.itemDescription, "\n");
            if(NULL != ptr) {
               *ptr = '\0';
            }
            ptr = strstr(item.itemDescription, "\r");
            if(NULL != ptr) {
               *ptr = '\0';
            }
            //PRICE
            printf("Enter the item price:\n");
            if(NULL == fgets(buffer, MAX_SIZE, stdin)) {
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
            item.itemPrice = (int) value;
            //QUANTITY
            printf("Enter the item quantity:\n");
            if(NULL == fgets(buffer, MAX_SIZE, stdin)) {
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
            item.itemQuantity = (int) value;   
            //ADD ITEM
            cart = AddItem(item, cart);
         }
      }
      if(option == 'r') { //REMOVE
         if(cart.cartSize == 0) {
            printf("Error: ShoppingCart is empty\n");
         } else {
            char itemName[MAX_SIZE];
            printf("Enter name of item to remove:\n"); 
            if(NULL == fgets(itemName, MAX_SIZE, stdin)) {
               return 1;
            }
            ptr = strstr(itemName, "\n");
            if(NULL != ptr) {
               *ptr = '\0';
            }
            ptr = strstr(itemName, "\r");
            if(NULL != ptr) {
               *ptr = '\0';
            }
            cart = RemoveItem(itemName, cart);
         }
      }
      if(option == 'c') { //CHANGE
         if(cart.cartSize == 0) {
            printf("Error: ShoppingCart is empty\n");
         } else {
            ItemToPurchase item;
            MakeItemBlank(&item);
            printf("Enter the item name:\n"); 
            if(NULL == fgets(item.itemName, MAX_SIZE, stdin)) {
               return 1;
            }
            ptr = strstr(item.itemName, "\n");
            if(NULL != ptr) {
               *ptr = '\0';
            }
            ptr = strstr(item.itemName, "\r");
            if(NULL != ptr) {
               *ptr = '\0';
            }
            printf("Enter the new quantity:\n");
            if(NULL == fgets(buffer, MAX_SIZE, stdin)) {
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
            item.itemQuantity = (int) value; 
            cart = ModifyItem(item, cart);
         }
      }
      if(option == 'i') { //OUTPUT ITEM'S DESC
         if(cart.cartSize == 0) {
            printf("Error: ShoppingCart is empty\n");
         } else {
            PrintDescriptions(cart);
         }
      }
      if(option == 'o') { //OUTPUT SHOPPING CART
         PrintInvoice(cart);
      }
   } while(option != 'q');
  return 0;
}
