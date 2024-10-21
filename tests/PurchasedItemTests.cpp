// PurchasedItemTests.cpp
#include "catch.hpp"

#include "PurchasedItem.h"

TEST_CASE("PurchasedItem class functionality", "[PurchasedItem]") {
    Item item("A1", "Apple", 1.00);
    PurchasedItem purchasedItem(&item);

    REQUIRE(purchasedItem.getItem() == &item);
    REQUIRE_FALSE(purchasedItem.isUsedInDeal());
    REQUIRE(purchasedItem.getFinalPrice() == Approx(1.00));
    REQUIRE(purchasedItem.getDealType() == DealType::NONE);

    // Test modifying PurchasedItem
    purchasedItem.setUsedInDeal(true);
    REQUIRE(purchasedItem.isUsedInDeal());

    purchasedItem.setFinalPrice(0.50);
    REQUIRE(purchasedItem.getFinalPrice() == Approx(0.50));

    purchasedItem.setDealType(DealType::TYPE1);
    REQUIRE(purchasedItem.getDealType() == DealType::TYPE1);
}
