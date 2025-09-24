#pragma once

#include <string>
#include "Product.hpp"

class Factory {
public:
    Product* create(const std::string& owner); 
    virtual ~Factory();

protected:
    virtual Product* createProduct(const std::string& owner) = 0;
    virtual void registerProduct(Product* product) = 0;
};
