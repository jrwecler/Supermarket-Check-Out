// Item.h
#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
public:
    Item(const std::string& id, const std::string& name, double price);

    std::string getId() const;
    std::string getName() const;
    double getPrice() const;

private:
    std::string id;
    std::string name;
    double price;
};

#endif // ITEM_H
