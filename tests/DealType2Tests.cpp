// DealType2Tests.cpp
#include "catch.hpp"

#include "Deal.h"

TEST_CASE("DealType2 functionality", "[DealType2]") {
    // Set up items
    Item item1("A1", "Apple", 1.00);
    Item item2("B2", "Banana", 0.50);
    Item item3("C3", "Cherry", 2.00);

    std::set<std::string> eligibleItems = {"A1", "B2", "C3"};

    DealType2 dealType2(eligibleItems);

    // Create purchased items
    std::vector<PurchasedItem> purchasedItems = {
        PurchasedItem(&item1),
        PurchasedItem(&item2),
        PurchasedItem(&item3)
    };

    std::vector<std::string> appliedDeals;

    // Apply the deal
    dealType2.applyDeal(purchasedItems, appliedDeals);

    // Check that the deal was applied correctly
    REQUIRE(purchasedItems[0].isUsedInDeal());
    REQUIRE(purchasedItems[1].isUsedInDeal());
    REQUIRE(purchasedItems[2].isUsedInDeal());

    // The cheapest item (Banana) should be free
    REQUIRE(purchasedItems[1].getFinalPrice() == Approx(0.0));
    REQUIRE(purchasedItems[1].getDealType() == DealType::TYPE2);

    // Check that the applied deal is recorded
    REQUIRE(appliedDeals.size() == 1);
    REQUIRE(appliedDeals[0].find("Deal Type 2 applied to") != std::string::npos);
}
