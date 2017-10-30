#include "CBFixedAccessibility.h"

CBFixedAccessibilityPtr CBFixedAccessibility::getNewInstance(bool accessibility) {
    return CBFixedAccessibilityPtr(new CBFixedAccessibility(accessibility));
}

CBFixedAccessibility::~CBFixedAccessibility() {}

CBFixedAccessibility::CBFixedAccessibility(bool accessibility) : accessibility(accessibility) {}

bool CBFixedAccessibility::isAccessible() {
    return accessibility;
}
