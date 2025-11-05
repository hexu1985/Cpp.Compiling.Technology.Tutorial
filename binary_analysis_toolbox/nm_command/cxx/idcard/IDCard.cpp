#include "IDCard.hpp"
#include <iostream>

IDCard::IDCard(const std::string& owner_): owner(owner_) {
    std::cout << "制作" << owner << "的ID卡。" << std::endl;
}

void IDCard::use() {
    std::cout << "使用" << owner << "的ID卡。" << std::endl;
}

std::string IDCard::getOwner() {
    return owner;
}
