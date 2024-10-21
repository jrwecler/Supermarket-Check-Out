#ifndef DEAL_H
#define DEAL_H

#include <string>
#include <vector>
#include <set>
#include "PurchasedItem.h"

/**
 * @class Deal
 * @brief Abstract base class representing a promotional deal.
 * 
 * This class provides a common interface for all types of deals that can be applied to purchased items.
 */
class Deal {
public:
    /**
     * @brief Virtual destructor for proper cleanup in derived classes.
     */
    virtual ~Deal() {}

    /**
     * @brief Pure virtual function to apply a deal to the given items.
     * 
     * @param items The list of purchased items to which the deal may be applied.
     * @param appliedDeals The list to store descriptions of applied deals.
     */
    virtual void applyDeal(std::vector<PurchasedItem>& items, std::vector<std::string>& appliedDeals) = 0;
};

/**
 * @class DealType1
 * @brief Represents a "Buy 3 identical items, pay for 2" promotional deal.
 */
class DealType1 : public Deal {
public:
    /**
     * @brief Constructs a DealType1 object.
     * 
     * @param eligibleItemIds The set of item IDs eligible for this deal.
     */
    DealType1(const std::set<std::string>& eligibleItemIds);

    /**
     * @brief Applies the deal to the given items.
     * 
     * If three identical items are present, the customer only pays for two of them.
     * 
     * @param items The list of purchased items to which the deal may be applied.
     * @param appliedDeals The list to store descriptions of applied deals.
     */
    void applyDeal(std::vector<PurchasedItem>& items, std::vector<std::string>& appliedDeals) override;

private:
    std::set<std::string> eligibleItemIds; ///< Set of eligible item IDs for this deal.
};

/**
 * @class DealType2
 * @brief Represents a "Buy 3 different items, get the cheapest one free" promotional deal.
 */
class DealType2 : public Deal {
public:
    /**
     * @brief Constructs a DealType2 object.
     * 
     * @param eligibleItemIds The set of item IDs eligible for this deal.
     */
    DealType2(const std::set<std::string>& eligibleItemIds);

    /**
     * @brief Applies the deal to the given items.
     * 
     * If three different eligible items are present, the cheapest item is provided for free.
     * 
     * @param items The list of purchased items to which the deal may be applied.
     * @param appliedDeals The list to store descriptions of applied deals.
     */
    void applyDeal(std::vector<PurchasedItem>& items, std::vector<std::string>& appliedDeals) override;

private:
    std::set<std::string> eligibleItemIds; ///< Set of eligible item IDs for this deal.
};

#endif // DEAL_H
