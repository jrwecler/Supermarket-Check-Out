// PurchasedItem.h
#ifndef PURCHASEDITEM_H
#define PURCHASEDITEM_H

#include "Item.h"

enum class DealType {
    NONE,
    TYPE1, // Buy 3 Identical Items, Pay for 2
    TYPE2  // Buy 3 Different Items from a Set, Cheapest is Free
};

class PurchasedItem {
public:
    PurchasedItem(Item* item);

    Item* getItem() const;
    bool isUsedInDeal() const;
    void setUsedInDeal(bool used);
    double getFinalPrice() const;
    void setFinalPrice(double price);

    // New methods for DealType
    DealType getDealType() const;
    void setDealType(DealType type);

private:
    Item* item;
    bool usedInDeal;
    double finalPrice;
    DealType dealType; // Tracks the deal type applied
};

#endif // PURCHASEDITEM_H