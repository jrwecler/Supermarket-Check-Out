// ItemTests.cpp
#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

#include "Item.h"

TEST_CASE("Item class functionality", "[Item]") {
    // Test item creation and getters
    Item item("A1", "Apple", 1.00);

    REQUIRE(item.getId() == "A1");
    REQUIRE(item.getName() == "Apple");
    REQUIRE(item.getPrice() == Approx(1.00));
}
