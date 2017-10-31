#include "CNTransActionAppearanceImp.h"

#include "Base/CNTransActionAppearance/CNTransActionAccessibility.h"
#include "Base/CNTransActionAppearance/CNTransActionState.h"
#include "Base/CNTransActionAppearance/CNTransActionTitle.h"

CNTransActionAppearanceImpPtr CNTransActionAppearanceImp::getNewInstance(CNTransActionAccessibilityPtr accessibility,
                                                                         CNTransActionStatePtr state,
                                                                         CNTransActionTitlePtr title) {
    return CNTransActionAppearanceImpPtr(new CNTransActionAppearanceImp(accessibility, state, title));
}

CNTransActionAppearanceImp::~CNTransActionAppearanceImp() {}

CNTransActionAppearanceImp::CNTransActionAppearanceImp(CNTransActionAccessibilityPtr accessibility,
                                                       CNTransActionStatePtr state,
                                                       CNTransActionTitlePtr title)
        : accessibility(accessibility),
          state(state),
          title(title) {}

bool CNTransActionAppearanceImp::isAccessible() {
    return accessibility->isAccessible();
}
CNTransActionStateValues CNTransActionAppearanceImp::getState() {
    return state->getState();
}
std::string CNTransActionAppearanceImp::getTitle() {
    return title->getTitle();
}
