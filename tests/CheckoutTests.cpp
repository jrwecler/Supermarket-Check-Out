// CheckoutTests.cpp
#include "catch.hpp"
#include "Checkout.h"
#include "json.hpp"

using json = nlohmann::json;

struct CheckoutFixture {
    Checkout checkout;
    json testData;

    CheckoutFixture() {
        testData = R"(
        {
          "items": [
            {"id": "A1", "name": "Apple", "price": 1.00},
            {"id": "B2", "name": "Banana", "price": 0.50},
            {"id": "C3", "name": "Cherry", "price": 2.00}
          ],
          "deals": {
            "deal_type_1": ["A1"],
            "deal_type_2": [["A1", "B2", "C3"]]
          }
        }
        )"_json;

        checkout.loadItemsAndDeals(testData);
    }
};

TEST_CASE_METHOD(CheckoutFixture, "Checkout process", "[Checkout]") {
    // Simulate scanning items
    REQUIRE_NOTHROW(checkout.scanItem("A1 4")); // Should trigger Deal Type 1
    REQUIRE_NOTHROW(checkout.scanItem("B2 1"));
    REQUIRE_NOTHROW(checkout.scanItem("C3 1")); // Should trigger Deal Type 2

    // Apply deals
    REQUIRE_NOTHROW(checkout.applyDeals());

    // Verify that the cart has correct quantities
    REQUIRE(checkout.getCartQuantity("A1") == 4);
    REQUIRE(checkout.getCartQuantity("B2") == 1);
    REQUIRE(checkout.getCartQuantity("C3") == 1);

    // Verify that the applied deals are recorded
    REQUIRE(checkout.getAppliedDeals().size() == 2);
    REQUIRE(checkout.getAppliedDeals()[0].find("Deal Type 1 applied to 3 x Apple") != std::string::npos);
    REQUIRE(checkout.getAppliedDeals()[1].find("Deal Type 2 applied to") != std::string::npos);
}
