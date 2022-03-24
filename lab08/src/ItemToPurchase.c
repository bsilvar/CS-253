#include <stdio.h>
#include <string.h>
#include "ItemToPurchase.h"

/*
typedef struct ItemToPurchase_struct {
   char itemName[MAX_ITEM_NAME];
   char itemDescription[MAX_ITEM_DESCRIPTION];
   int itemPrice;
   int itemQuantity;
} ItemToPurchase;
*/

void MakeItemBlank(ItemToPurchase* item) {
   strcpy(item->itemName, "none");
   strcpy(item->itemDescription, "none");
   item->itemPrice = 0;
   item->itemQuantity = 0;
  return;
}
void PrintItemCost(ItemToPurchase item) {
   printf("%s %d @ $%d = $%d\n", item.itemName, item.itemQuantity, 
                                 item.itemPrice, 
                                 item.itemQuantity * item.itemPrice);
  return;
}

void PrintItemDescription(ItemToPurchase item) {
   printf("%s: %s\n", item.itemName, item.itemDescription);   
  return;
}
