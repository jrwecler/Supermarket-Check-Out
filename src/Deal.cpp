// Deal.cpp
#include "Deal.h"
#include <algorithm>
#include <map>
#include <iostream>
#include <sstream>
#include <iomanip>

DealType1::DealType1(const std::set<std::string>& eligibleItemIds)
    : eligibleItemIds(eligibleItemIds) {}

void DealType1::applyDeal(std::vector<PurchasedItem>& items, std::vector<std::string>& appliedDeals) {
    // Group eligible items by item ID
    std::map<std::string, std::vector<PurchasedItem*>> itemGroups;

    for (auto& purchasedItem : items) {
        Item* item = purchasedItem.getItem();
        if (eligibleItemIds.find(item->getId()) != eligibleItemIds.end() && !purchasedItem.isUsedInDeal()) {
            itemGroups[item->getId()].push_back(&purchasedItem);
        }
    }

    // Apply Deal Type 1 to each group
    for (auto& pair : itemGroups) {
        const std::string& itemId = pair.first;
        std::vector<PurchasedItem*>& group = pair.second;

        int eligibleSets = group.size() / 3; // Number of times the deal can be applied

        for (int i = 0; i < eligibleSets; ++i) {
            // Get three items
            PurchasedItem* item1 = group[i * 3];
            PurchasedItem* item2 = group[i * 3 + 1];
            PurchasedItem* item3 = group[i * 3 + 2];

            // Mark items as used
            item1->setUsedInDeal(true);
            item2->setUsedInDeal(true);
            item3->setUsedInDeal(true);

            // Set the final price of one item to zero (the third item)
            item3->setFinalPrice(0.0);
            item3->setDealType(DealType::TYPE1); // Assign Deal Type 1

            // Record the applied deal with discount amount
            double discountAmount = item3->getItem()->getPrice();
            std::ostringstream dealDescription;
            dealDescription << "Deal Type 1 applied to 3 x " << item1->getItem()->getName() 
                           << " (-$" << std::fixed << std::setprecision(2) << discountAmount << ")";
            appliedDeals.push_back(dealDescription.str());
        }
    }
}

DealType2::DealType2(const std::set<std::string>& eligibleItemIds)
    : eligibleItemIds(eligibleItemIds) {}

void DealType2::applyDeal(std::vector<PurchasedItem>& items, std::vector<std::string>& appliedDeals) {
    // Collect eligible and unused items
    std::map<std::string, std::vector<PurchasedItem*>> availableItemsMap;

    for (auto& purchasedItem : items) {
        Item* item = purchasedItem.getItem();
        if (eligibleItemIds.find(item->getId()) != eligibleItemIds.end() && !purchasedItem.isUsedInDeal()) {
            availableItemsMap[item->getId()].push_back(&purchasedItem);
        }
    }

    // Continue applying Deal Type 2 as long as possible
    while (true) {
        std::vector<PurchasedItem*> dealItems;

        // Attempt to collect one of each eligible item in the set
        for (const std::string& itemId : eligibleItemIds) {
            if (availableItemsMap[itemId].empty()) {
                // Cannot apply the deal anymore
                goto DEAL_TYPE_2_DONE;
            } else {
                // Take the last available item
                PurchasedItem* pItem = availableItemsMap[itemId].back();
                availableItemsMap[itemId].pop_back();
                dealItems.push_back(pItem);
            }
        }

        // Find the cheapest item among the three
        PurchasedItem* cheapestItem = dealItems[0];
        for (auto& pItem : dealItems) {
            if (pItem->getItem()->getPrice() < cheapestItem->getItem()->getPrice()) {
                cheapestItem = pItem;
            }
        }

        // Apply the deal
        for (auto& pItem : dealItems) {
            pItem->setUsedInDeal(true);
        }

        // Set the final price of the cheapest item to zero
        cheapestItem->setFinalPrice(0.0);
        cheapestItem->setDealType(DealType::TYPE2); // Assign Deal Type 2

        // Construct the item names string
        std::string itemNames;
        for (size_t i = 0; i < dealItems.size(); ++i) {
            itemNames += dealItems[i]->getItem()->getName();
            if (i < dealItems.size() - 1) {
                itemNames += ", ";
            }
        }

        // Record the applied deal with discount amount
        double discountAmount = cheapestItem->getItem()->getPrice();
        std::ostringstream dealDescription;
        dealDescription << "Deal Type 2 applied to " << itemNames << " (-$" 
                       << std::fixed << std::setprecision(2) << discountAmount << ")";
        appliedDeals.push_back(dealDescription.str());
    }

DEAL_TYPE_2_DONE:
    return;
}