// Deal.h
#ifndef DEAL_H
#define DEAL_H

#include <string>
#include <vector>
#include <set>             
#include "PurchasedItem.h" 

// Abstract Base Class for Deals
class Deal {
public:
    virtual ~Deal() {}
    
    // Pure virtual function to apply the deal
    virtual void applyDeal(std::vector<PurchasedItem>& items, std::vector<std::string>& appliedDeals) = 0;
};

// Deal Type 1: Buy 3 Identical Items, Pay for 2
class DealType1 : public Deal {
public:
    DealType1(const std::set<std::string>& eligibleItemIds);
    void applyDeal(std::vector<PurchasedItem>& items, std::vector<std::string>& appliedDeals) override;

private:
    std::set<std::string> eligibleItemIds;
};

// Deal Type 2: Buy 3 Different Items from a Set, Cheapest is Free
class DealType2 : public Deal {
public:
    DealType2(const std::set<std::string>& eligibleItemIds);
    void applyDeal(std::vector<PurchasedItem>& items, std::vector<std::string>& appliedDeals) override;

private:
    std::set<std::string> eligibleItemIds;
};

#endif // DEAL_H
