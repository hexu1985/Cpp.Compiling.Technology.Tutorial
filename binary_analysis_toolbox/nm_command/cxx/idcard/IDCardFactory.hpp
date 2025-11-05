#pragma once

#include <vector>
#include "framework/Factory.hpp"

class IDCardFactory : public Factory {
private:
    std::vector<std::string> owners;

protected:
    Product* createProduct(const std::string& owner) override;

    void registerProduct(Product* product) override;

public:
    const std::vector<std::string>& getOwners();
};
