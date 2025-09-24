#include "IDCardFactory.hpp"
#include "IDCard.hpp"

Product* IDCardFactory::createProduct(const std::string& owner) {
    return new IDCard(owner);
}

void IDCardFactory::registerProduct(Product* product) {
    owners.push_back(static_cast<IDCard *>(product)->getOwner());
}

const std::vector<std::string>& IDCardFactory::getOwners() {
    return owners;
}
