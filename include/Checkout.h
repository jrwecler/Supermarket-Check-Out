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

/**
 * @class Checkout
 * @brief Manages the checkout process for a supermarket, including item scanning, deal application, and receipt generation.
 */
class Checkout {
public:
    /**
     * @brief Constructs a Checkout object.
     */
    Checkout();

    /**
     * @brief Loads items and deals from a JSON file.
     * @param filename Path to the JSON file.
     * @throws std::runtime_error if the file cannot be opened.
     */
    void loadItemsAndDeals(const std::string& filename);

    /**
     * @brief Loads items and deals from a JSON object.
     * @param data JSON object containing items and deals data.
     */
    void loadItemsAndDeals(const json& data);

    /**
     * @brief Scans an item, updating the cart.
     * @param input Item ID and quantity to be scanned.
     * @throws std::invalid_argument if the input format is invalid or item ID is not found.
     */
    void scanItem(const std::string& input);

    /**
     * @brief Applies all available deals to the items in the cart.
     */
    void applyDeals();

    /**
     * @brief Generates and prints the final receipt, including applied deals.
     */
    void generateReceipt() const;

    /**
     * @brief Gets the quantity of a specific item in the cart.
     * @param itemId ID of the item.
     * @return Quantity of the item in the cart.
     */
    int getCartQuantity(const std::string& itemId) const;

    /**
     * @brief Gets a list of applied deals.
     * @return Vector of strings containing descriptions of applied deals.
     */
    const std::vector<std::string>& getAppliedDeals() const;

private:
    // Available items in the store, keyed by item ID
    std::map<std::string, Item> availableItems;

    // List of available deals
    std::vector<std::shared_ptr<Deal>> deals;

    // List of purchased items with deal-specific information
    std::vector<PurchasedItem> purchasedItems;

    // Map to track quantities of each item in the cart
    std::map<std::string, int> cart;

    // List of applied deals descriptions
    std::vector<std::string> appliedDeals;

    /**
     * @brief Gets an item ID by its name.
     * @param itemName The name of the item.
     * @return The corresponding item ID, or an empty string if not found.
     */
    std::string getItemIdByName(const std::string& itemName) const;

    /**
     * @brief Loads items from a JSON object.
     * @param data JSON object containing item data.
     * @throws std::runtime_error if item data is invalid.
     */
    void loadItems(const json& data);

    /**
     * @brief Loads deals from a JSON object.
     * @param data JSON object containing deals data.
     * @throws std::runtime_error if deal data is invalid.
     */
    void loadDeals(const json& data);

    /**
     * @brief Prepares purchased items by iterating through the cart and converting to PurchasedItem instances.
     */
    void preparePurchasedItems();

    /**
     * @brief Processes the scanning of an item, adding or removing it from the cart.
     * @param itemIdInput The item ID.
     * @param quantity The quantity to add or remove.
     * @throws std::invalid_argument if item ID is invalid.
     */
    void processScannedItem(const std::string& itemIdInput, int quantity);

    /**
     * @brief Displays help information for the user, detailing the commands available.
     */
    void displayHelp() const;
};

#endif // CHECKOUT_H
