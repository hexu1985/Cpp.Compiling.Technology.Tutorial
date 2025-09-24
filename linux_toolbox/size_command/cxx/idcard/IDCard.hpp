#pragma once

#include "framework/Product.hpp"
#include <string>

class IDCard : public Product {
private:
    std::string owner;

public:
    IDCard(const std::string& owner);

    void use() override;

    std::string getOwner();
};
