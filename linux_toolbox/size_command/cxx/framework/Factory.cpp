#include "Factory.hpp"

Factory::~Factory() {}

Product* Factory::create(const std::string& owner) {
    Product* p = createProduct(owner);
    registerProduct(p);
    return p;
}
