// Checkout.cpp
#include "Checkout.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm> 
#include <cctype> 
#include <regex>  

#include "CustomExceptions.h"

using json = nlohmann::json;

Checkout::Checkout() {}

int Checkout::getCartQuantity(const std::string& itemId) const {
    auto it = cart.find(itemId);
    if (it != cart.end()) {
        return it->second;
    }
    return 0;
}

const std::vector<std::string>& Checkout::getAppliedDeals() const {
    return appliedDeals;
}

void Checkout::loadItemsAndDeals(const std::string& filename) {
    try {
        // Attempt to open the file
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Cannot open data file: " + filename);
        }

        // Attempt to parse the JSON data
        json data;
        file >> data;

        // Validate and load items and deals
        loadItems(data);
        loadDeals(data);
    } catch (const json::parse_error& e) {
        std::cerr << "JSON Parsing Error: " << e.what() << std::endl;
        std::cerr << "Please check the JSON file for syntax errors.\n";
        exit(EXIT_FAILURE);
    } catch (const InvalidItemException& e) { // Changed
        std::cerr << "Item Loading Error: " << e.what() << "\n";
        exit(EXIT_FAILURE);
    } catch (const InvalidDealException& e) { // Changed
        std::cerr << "Deal Loading Error: " << e.what() << "\n";
        exit(EXIT_FAILURE);
    } catch (const std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Checkout::loadItemsAndDeals(const json& data) {
    try {
        // Validate and load items and deals
        loadItems(data);
        loadDeals(data);
    } catch (const json::parse_error& e) {
        std::cerr << "JSON Parsing Error: " << e.what() << std::endl;
        std::cerr << "Please check the JSON data for syntax errors.\n";
        exit(EXIT_FAILURE);
    } catch (const InvalidItemException& e) {
        std::cerr << "Item Loading Error: " << e.what() << "\n";
        exit(EXIT_FAILURE);
    } catch (const InvalidDealException& e) {
        std::cerr << "Deal Loading Error: " << e.what() << "\n";
        exit(EXIT_FAILURE);
    } catch (const std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Checkout::loadItems(const json& data) {
    if (!data.contains("items") || !data["items"].is_array()) {
        throw InvalidItemException("Invalid or missing 'items' array in JSON data.");
    }

    for (const auto& itemData : data["items"]) {
        if (!itemData.contains("id") || !itemData.contains("name") || !itemData.contains("price")) {
            throw InvalidItemException("Item data missing required fields (id, name, price).");
        }

        std::string id = itemData["id"].get<std::string>();
        std::string name = itemData["name"].get<std::string>();
        double price = itemData["price"].get<double>();

        if (id.empty() || name.empty() || price < 0.0) {
            throw InvalidItemException("Invalid item data: ID, name cannot be empty, price cannot be negative.");
        }

        availableItems.emplace(id, Item(id, name, price));
    }
}

void Checkout::loadDeals(const json& data) {
    if (!data.contains("deals") || !data["deals"].is_object()) {
        throw InvalidDealException("Invalid or missing 'deals' object in JSON data.");
    }

    const auto& dealsData = data["deals"];

    // Load Deal Type 1
    if (dealsData.contains("deal_type_1")) {
        if (!dealsData["deal_type_1"].is_array()) {
            throw InvalidDealException("'deal_type_1' should be an array.");
        }

        std::set<std::string> dealType1Items;
        for (const auto& itemId : dealsData["deal_type_1"]) {
            std::string id = itemId.get<std::string>();
            if (availableItems.find(id) == availableItems.end()) {
                throw InvalidDealException("Deal Type 1 contains unknown item ID: " + id);
            }
            dealType1Items.insert(id);
        }
        if (!dealType1Items.empty()) {
            deals.push_back(std::make_shared<DealType1>(dealType1Items));
        }
    }

    // Load Deal Type 2
    if (dealsData.contains("deal_type_2")) {
        if (!dealsData["deal_type_2"].is_array()) {
            throw InvalidDealException("'deal_type_2' should be an array.");
        }

        for (const auto& dealSet : dealsData["deal_type_2"]) {
            if (!dealSet.is_array() || dealSet.size() != 3) {
                throw InvalidDealException("Each 'deal_type_2' entry should be an array of exactly 3 item IDs.");
            }

            std::set<std::string> dealType2Items;
            for (const auto& itemId : dealSet) {
                std::string id = itemId.get<std::string>();
                if (availableItems.find(id) == availableItems.end()) {
                    throw InvalidDealException("Deal Type 2 contains unknown item ID: " + id);
                }
                dealType2Items.insert(id);
            }
            if (!dealType2Items.empty()) {
                deals.push_back(std::make_shared<DealType2>(dealType2Items));
            }
        }
    }
}

void Checkout::scanItem(const std::string& input) {
    // Trim whitespace
    std::string trimmedInput = input;
    trimmedInput.erase(0, trimmedInput.find_first_not_of(" \t\n\r\f\v"));
    trimmedInput.erase(trimmedInput.find_last_not_of(" \t\n\r\f\v") + 1);

    // Check for help command
    if (trimmedInput == "help") {
        displayHelp();
        return;
    }

    // Updated regular expression to match alphanumeric IDs with max 5 characters
    std::regex pattern(R"(^([A-Za-z0-9]{1,5})\s*(-?\d+)?$)", std::regex_constants::icase);
    std::smatch matches;

    if (std::regex_match(trimmedInput, matches, pattern)) {
        std::string itemId = matches[1];
        int quantity = 1; // Default quantity

        // Check if quantity is provided
        if (matches[2].matched) {
            try {
                quantity = std::stoi(matches[2]);
            } catch (const std::invalid_argument& e) {
                std::cout << "Invalid quantity format. Please enter a valid integer.\n";
                return;
            } catch (const std::out_of_range& e) {
                std::cout << "Quantity is out of acceptable range.\n";
                return;
            }
        }

        // Process the item
        try {
            processScannedItem(itemId, quantity);
        } catch (const std::exception& e) {
            std::cout << "Error processing item: " << e.what() << "\n";
        }
    } else {
        std::cout << "Invalid input format. Please enter the item ID and quantity (e.g., 'A1 3').\n";
        std::cout << "Type 'help' for a list of available commands and items.\n";
    }
}

void Checkout::processScannedItem(const std::string& itemIdInput, int quantity) {
    try {
        std::string itemId = itemIdInput;
        // Convert itemId to uppercase to match the stored IDs
        std::transform(itemId.begin(), itemId.end(), itemId.begin(), ::toupper);

        auto it = availableItems.find(itemId);
        if (it != availableItems.end()) {
            // Adjust the quantity in the cart
            cart[itemId] += quantity;

            // Ensure quantity is within bounds [0, 100]
            if (cart[itemId] > 100) {
                std::cout << "Total quantity for item ID '" << itemId << "' cannot exceed 100. Setting quantity to 100.\n";
                cart[itemId] = 100;
            } else if (cart[itemId] < 0) {
                cart[itemId] = 0;
                std::cout << "No items of ID '" << itemId << "' left in your cart.\n";
                return;
            }

            std::cout << "Updated " << it->second.getName() << " quantity to " << cart[itemId] << ".\n";
        } else {
            throw std::runtime_error("Item ID '" + itemId + "' not found.");
        }
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
        std::cout << "Type 'help' for a list of available items.\n";
    }
}

void Checkout::preparePurchasedItems() {
    purchasedItems.clear();
    for (const auto& pair : cart) {
        const std::string& itemId = pair.first;
        int quantity = pair.second;

        auto it = availableItems.find(itemId);
        if (it != availableItems.end()) {
            Item* item = &it->second;
            for (int i = 0; i < quantity; ++i) {
                purchasedItems.emplace_back(item);
            }
        }
    }
}

void Checkout::applyDeals() {
    try {
        preparePurchasedItems();

        // Apply Deal Type 1 first
        for (const auto& deal : deals) {
            auto* dealType1 = dynamic_cast<DealType1*>(deal.get());
            if (dealType1) {
                dealType1->applyDeal(purchasedItems, appliedDeals);
            }
        }

        // Then apply Deal Type 2
        for (const auto& deal : deals) {
            auto* dealType2 = dynamic_cast<DealType2*>(deal.get());
            if (dealType2) {
                dealType2->applyDeal(purchasedItems, appliedDeals);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error applying deals: " << e.what() << "\n";
    }
}

std::string Checkout::getItemIdByName(const std::string& itemName) const {
    for (const auto& pair : availableItems) {
        if (pair.second.getName() == itemName) {
            return pair.first;
        }
    }
    return "";
}

void Checkout::displayHelp() const {
    std::cout << "\n--- Help ---\n";
    std::cout << "Available commands:\n";
    std::cout << " - Enter the item ID followed by the quantity (e.g., 'A1 3').\n";
    std::cout << " - To add a single item, simply enter the item ID (e.g., 'A1').\n";
    std::cout << " - To remove items, enter a negative quantity (e.g., 'A1 -2').\n";
    std::cout << " - To clear all items of a type, enter the item ID followed by '0' (e.g., 'A1 0').\n";
    std::cout << " - Type 'done' when you have finished scanning items.\n";
    std::cout << " - Type 'help' to display this help message.\n";

    std::cout << "\nAvailable items:\n";
    std::cout << std::left << std::setw(10) << "Item ID"
              << std::left << std::setw(25) << "Item Name"
              << std::left << std::setw(10) << "Price\n";
    std::cout << "-------------------------------------------------\n";
    for (const auto& pair : availableItems) {
        const Item& item = pair.second;
        std::cout << std::left << std::setw(10) << item.getId()
                  << std::left << std::setw(25) << item.getName()
                  << "$" << std::fixed << std::setprecision(2) << item.getPrice() << "\n";
    }
    std::cout << "-------------------------------------------------\n";
}

void Checkout::generateReceipt() const {
    std::cout << "\n--- Customer Receipt ---\n";
    std::cout << std::fixed << std::setprecision(2);

    double totalPreDiscount = 0.0;
    double totalSavings = 0.0;
    double total = 0.0;

    // Summarize items and calculate totals
    std::map<std::string, std::pair<int, double>> itemSummary;
    std::map<std::string, double> itemDiscounts; // To track discounts per item
    std::map<std::string, DealType> itemDealTypes; // To track deal types per item

    for (const PurchasedItem& purchasedItem : purchasedItems) {
        Item* item = purchasedItem.getItem();
        std::string itemName = item->getName();
        double finalPrice = purchasedItem.getFinalPrice();
        double originalPrice = item->getPrice();

        itemSummary[itemName].first += 1;
        itemSummary[itemName].second += finalPrice;

        totalPreDiscount += originalPrice;
        total += finalPrice;

        // Calculate savings per item
        double discount = originalPrice - finalPrice;
        if (discount > 0) {
            itemDiscounts[itemName] += discount;
            totalSavings += discount;
            itemDealTypes[itemName] = purchasedItem.getDealType();
        }
    }

    // Determine the width for alignment
    const int ITEM_NAME_WIDTH = 30;
    const int PRICE_WIDTH = 10;

    // Display items with discounts
    for (const auto& entry : itemSummary) {
        const std::string& itemName = entry.first;
        int quantity = entry.second.first;
        double lineTotal = entry.second.second;
        std::string itemId = getItemIdByName(itemName);
        double originalPrice = availableItems.at(itemId).getPrice();
        double lineOriginalTotal = quantity * originalPrice;

        // Item line: Left-aligned item name and quantity, right-aligned original total price
        std::cout << std::left << std::setw(ITEM_NAME_WIDTH) << (itemName + " x" + std::to_string(quantity))
                  << " $" << std::right << std::setw(PRICE_WIDTH) << lineOriginalTotal << "\n";

        // If there is a discount for this item, display it
        if (itemDiscounts.count(itemName)) {
            double discount = itemDiscounts[itemName];
            DealType dealType = itemDealTypes[itemName];
            std::ostringstream discountOss;
            discountOss << "Discount ("; 
            if (dealType == DealType::TYPE1) {
                discountOss << "Type 1";
            } else if (dealType == DealType::TYPE2) {
                discountOss << "Type 2";
            } else {
                discountOss << "N/A";
            }
            discountOss << ")";

            std::cout << std::left << std::setw(ITEM_NAME_WIDTH) << ("  " + discountOss.str())
                      << "-$" << std::right << std::setw(PRICE_WIDTH) << discount << "\n";
        }
    }

    // Display applied deals (optional)
    if (!appliedDeals.empty()) {
        std::cout << "\n--- Discounts Applied ---\n";
        for (const std::string& deal : appliedDeals) {
            std::cout << deal << "\n";
        }
    }

    // Display totals
    std::cout << "\n";
    std::cout << std::left << std::setw(ITEM_NAME_WIDTH) << "Total before discounts"
              << " $" << std::right << std::setw(PRICE_WIDTH) << totalPreDiscount << "\n";
    std::cout << std::left << std::setw(ITEM_NAME_WIDTH) << "Total savings"
              << "-$" << std::right << std::setw(PRICE_WIDTH) << totalSavings << "\n";
    std::cout << std::left << std::setw(ITEM_NAME_WIDTH) << "Total after discounts"
              << " $" << std::right << std::setw(PRICE_WIDTH) << total << "\n";

    std::cout << "Thank you for shopping with us!\n";
}