// PurchasedItem.cpp
#include "PurchasedItem.h"

PurchasedItem::PurchasedItem(Item* item)
    : item(item), usedInDeal(false), finalPrice(item->getPrice()), dealType(DealType::NONE) {}

Item* PurchasedItem::getItem() const {
    return item;
}

bool PurchasedItem::isUsedInDeal() const {
    return usedInDeal;
}

void PurchasedItem::setUsedInDeal(bool used) {
    usedInDeal = used;
}

double PurchasedItem::getFinalPrice() const {
    return finalPrice;
}

void PurchasedItem::setFinalPrice(double price) {
    finalPrice = price;
}

DealType PurchasedItem::getDealType() const {
    return dealType;
}

void PurchasedItem::setDealType(DealType type) {
    dealType = type;
}