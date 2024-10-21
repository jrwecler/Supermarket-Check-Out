// Checkout.h
#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <set>
#include <regex>    
#include <algorithm>
#include <cctype>   
#include "Item.h"
#include "PurchasedItem.h"
#include "Deal.h"
#include "CustomExceptions.h"
#include "json.hpp"
using json = nlohmann::json;

class Checkout {
public:
    Checkout();
    void loadItemsAndDeals(const std::string& filename);
    void loadItemsAndDeals(const json& data);
    void scanItem(const std::string& input);
    void applyDeals();
    void generateReceipt() const;
    int getCartQuantity(const std::string& itemId) const;
    const std::vector<std::string>& getAppliedDeals() const;
private:
    std::map<std::string, Item> availableItems;
    std::vector<std::shared_ptr<Deal>> deals;
    std::vector<PurchasedItem> purchasedItems;
    std::map<std::string, int> cart; // To track quantities
    std::vector<std::string> appliedDeals;
    std::string getItemIdByName(const std::string& itemName) const;
    void loadItems(const json& data);
    void loadDeals(const json& data);
    void preparePurchasedItems();
    void processScannedItem(const std::string& itemIdInput, int quantity);
    void displayHelp() const;
};

#endif // CHECKOUT_H