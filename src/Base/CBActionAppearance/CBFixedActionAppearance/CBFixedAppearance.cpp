#include "CBFixedAppearance.h"

CBFixedAppearancePtr CBFixedAppearance::getNewInstance(bool accessibility,
                                                                         CBActionStates state,
                                                                         std::string title) {
    return CBFixedAppearancePtr(new CBFixedAppearance(accessibility, state, title));
}

CBFixedAppearance::~CBFixedAppearance() {}

CBFixedAppearance::CBFixedAppearance(bool accessibility,
                                                       CBActionStates state,
                                                       std::string title)
        : accessibility(accessibility),
          state(state),
          title(title) {}

bool CBFixedAppearance::isAccessible() {
    return accessibility;
}
CBActionStates CBFixedAppearance::getState() {
    return state;
}
std::string CBFixedAppearance::getTitle() {
    return title;
}
