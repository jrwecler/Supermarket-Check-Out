// Item.cpp
#include "Item.h"

Item::Item(const std::string& id, const std::string& name, double price)
    : id(id), name(name), price(price) {}

std::string Item::getId() const { return id; }

std::string Item::getName() const { return name; }

double Item::getPrice() const { return price; }
