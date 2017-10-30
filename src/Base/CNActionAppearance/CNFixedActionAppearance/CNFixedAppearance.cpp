#include "CNFixedAppearance.h"

CNFixedAppearancePtr CNFixedAppearance::getNewInstance(bool accessibility,
                                                                         CNActionStates state,
                                                                         std::string title) {
    return CNFixedAppearancePtr(new CNFixedAppearance(accessibility, state, title));
}

CNFixedAppearance::~CNFixedAppearance() {}

CNFixedAppearance::CNFixedAppearance(bool accessibility,
                                                       CNActionStates state,
                                                       std::string title)
        : accessibility(accessibility),
          state(state),
          title(title) {}

bool CNFixedAppearance::isAccessible() {
    return accessibility;
}
CNActionStates CNFixedAppearance::getState() {
    return state;
}
std::string CNFixedAppearance::getTitle() {
    return title;
}
