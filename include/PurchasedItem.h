#ifndef PURCHASEDITEM_H
#define PURCHASEDITEM_H

#include "Item.h"

/**
 * @enum DealType
 * @brief Represents the type of deal applied to an item.
 */
enum class DealType {
    NONE,  ///< No deal applied.
    TYPE1, ///< Buy 3 Identical Items, Pay for 2.
    TYPE2  ///< Buy 3 Different Items from a Set, Cheapest is Free.
};

/**
 * @class PurchasedItem
 * @brief Represents an item that has been added to the cart, including deal and price information.
 */
class PurchasedItem {
public:
    /**
     * @brief Constructs a PurchasedItem object.
     * 
     * @param item Pointer to the Item object representing the purchased item.
     */
    PurchasedItem(Item* item);

    /**
     * @brief Retrieves the associated Item object.
     * 
     * @return Pointer to the Item object.
     */
    Item* getItem() const;

    /**
     * @brief Checks if the item is used in a deal.
     * 
     * @return True if the item is used in a deal, false otherwise.
     */
    bool isUsedInDeal() const;

    /**
     * @brief Sets whether the item is used in a deal.
     * 
     * @param used Boolean indicating if the item is used in a deal.
     */
    void setUsedInDeal(bool used);

    /**
     * @brief Retrieves the final price of the item, considering applied deals.
     * 
     * @return The final price of the item.
     */
    double getFinalPrice() const;

    /**
     * @brief Sets the final price of the item.
     * 
     * @param price The price to set for the item after applying deals.
     */
    void setFinalPrice(double price);

    /**
     * @brief Retrieves the type of deal applied to the item.
     * 
     * @return The deal type applied to the item.
     */
    DealType getDealType() const;

    /**
     * @brief Sets the type of deal applied to the item.
     * 
     * @param type The type of deal to apply.
     */
    void setDealType(DealType type);

private:
    Item* item;          ///< Pointer to the associated Item object.
    bool usedInDeal;     ///< Indicates if the item is used in a deal.
    double finalPrice;   ///< The final price of the item after deal application.
    DealType dealType;   ///< Type of deal applied to the item.
};

#endif // PURCHASEDITEM_H
