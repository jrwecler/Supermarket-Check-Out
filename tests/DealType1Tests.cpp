// DealType1Tests.cpp
#include "catch.hpp"

#include "Deal.h"

TEST_CASE("DealType1 functionality", "[DealType1]") {
    // Set up items and purchased items
    Item item1("A1", "Apple", 1.00);
    Item item2("B2", "Banana", 0.50);

    std::set<std::string> eligibleItems = {"A1"};

    DealType1 dealType1(eligibleItems);

    // Create purchased items
    std::vector<PurchasedItem> purchasedItems = {
        PurchasedItem(&item1),
        PurchasedItem(&item1),
        PurchasedItem(&item1),
        PurchasedItem(&item2) // Not eligible
    };

    std::vector<std::string> appliedDeals;

    // Apply the deal
    dealType1.applyDeal(purchasedItems, appliedDeals);

    // Check that the deal was applied correctly
    REQUIRE(purchasedItems[0].isUsedInDeal());
    REQUIRE(purchasedItems[1].isUsedInDeal());
    REQUIRE(purchasedItems[2].isUsedInDeal());
    REQUIRE(purchasedItems[2].getFinalPrice() == Approx(0.0));
    REQUIRE(purchasedItems[2].getDealType() == DealType::TYPE1);

    // Check that the non-eligible item was not affected
    REQUIRE_FALSE(purchasedItems[3].isUsedInDeal());

    // Check that the applied deal is recorded
    REQUIRE(appliedDeals.size() == 1);
    REQUIRE(appliedDeals[0].find("Deal Type 1 applied to 3 x Apple") != std::string::npos);
}
