#include "CNFixedAccessibility.h"

CNFixedAccessibilityPtr CNFixedAccessibility::getNewInstance(bool accessibility) {
    return CNFixedAccessibilityPtr(new CNFixedAccessibility(accessibility));
}

CNFixedAccessibility::~CNFixedAccessibility() {}

CNFixedAccessibility::CNFixedAccessibility(bool accessibility) : accessibility(accessibility) {}

bool CNFixedAccessibility::isAccessible() {
    return accessibility;
}
