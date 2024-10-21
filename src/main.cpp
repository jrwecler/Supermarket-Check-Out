// main.cpp
#include "Checkout.h"
#include <iostream>
#include <string>

int main() {
    try {
        Checkout checkout;
        checkout.loadItemsAndDeals(std::string("data/data.json"));

        std::cout << "Welcome to the Supermarket Checkout System!\n";
        std::cout << "Type 'help' to see available commands and items.\n";

        std::string input;
        while (true) {
            std::cout << "\nScan item (or 'done' to finish): ";
            std::getline(std::cin, input);

            // Trim whitespace
            input.erase(0, input.find_first_not_of(" \t\n\r\f\v"));
            input.erase(input.find_last_not_of(" \t\n\r\f\v") + 1);

            if (input.empty()) {
                continue; // Skip empty inputs
            }

            if (input == "done") {
                break;
            }

            checkout.scanItem(input);
        }

        checkout.applyDeals();
        checkout.generateReceipt();

    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << "\n";
        std::cerr << "Please contact support.\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}