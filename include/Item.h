#ifndef ITEM_H
#define ITEM_H

#include <string>

/**
 * @class Item
 * @brief Represents a store item with an ID, name, and price.
 */
class Item {
public:
    /**
     * @brief Constructs an Item object.
     * 
     * @param id Unique identifier for the item.
     * @param name Name of the item.
     * @param price Price of the item.
     */
    Item(const std::string& id, const std::string& name, double price);

    /**
     * @brief Retrieves the ID of the item.
     * 
     * @return The ID of the item.
     */
    std::string getId() const;

    /**
     * @brief Retrieves the name of the item.
     * 
     * @return The name of the item.
     */
    std::string getName() const;

    /**
     * @brief Retrieves the price of the item.
     * 
     * @return The price of the item.
     */
    double getPrice() const;

private:
    std::string id;   ///< Unique identifier for the item.
    std::string name; ///< Name of the item.
    double price;     ///< Price of the item.
};

#endif // ITEM_H
