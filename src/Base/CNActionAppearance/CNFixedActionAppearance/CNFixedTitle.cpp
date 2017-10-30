#include "CNFixedTitle.h"

CNFixedTitlePtr CNFixedTitle::getNewInstance(std::string title) {
    return CNFixedTitlePtr(new CNFixedTitle(title));
}

CNFixedTitle::~CNFixedTitle() {}

CNFixedTitle::CNFixedTitle(std::string title) : title(title) {}

std::string CNFixedTitle::getTitle() {
    return title;
}
