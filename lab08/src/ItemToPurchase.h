#ifndef ITEM_TO_PURCHASE_H
#define ITEM_TO_PURCHASE_H

#define MAX_ITEM_NAME 50
#define MAX_ITEM_DESCRIPTION 80

typedef struct ItemToPurchase_struct {
   char itemName[MAX_ITEM_NAME];
   int itemPrice;
   int itemQuantity;
   char itemDescription[MAX_ITEM_DESCRIPTION];
} ItemToPurchase;

void MakeItemBlank(ItemToPurchase *item);
void PrintItemCost(ItemToPurchase item);
void PrintItemDescription(ItemToPurchase item);

#endif
