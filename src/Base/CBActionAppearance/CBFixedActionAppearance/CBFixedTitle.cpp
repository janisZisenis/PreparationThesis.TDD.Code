#include "CBFixedTitle.h"

CBFixedTitlePtr CBFixedTitle::getNewInstance(std::string title) {
    return CBFixedTitlePtr(new CBFixedTitle(title));
}

CBFixedTitle::~CBFixedTitle() {}

CBFixedTitle::CBFixedTitle(std::string title) : title(title) {}

std::string CBFixedTitle::getTitle() {
    return title;
}
