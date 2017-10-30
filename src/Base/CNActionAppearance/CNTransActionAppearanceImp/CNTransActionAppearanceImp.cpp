#include "CNTransActionAppearanceImp.h"

#include "Base/CNTransActionAppearance/CNActionAccessibility.h"
#include "Base/CNTransActionAppearance/CNActionState.h"
#include "Base/CNTransActionAppearance/CNActionTitle.h"

CNTransActionAppearanceImpPtr CNTransActionAppearanceImp::getNewInstance(CNActionAccessibilityPtr accessibility,
                                                                         CNActionStatePtr state,
                                                                         CNActionTitlePtr title) {
    return CNTransActionAppearanceImpPtr(new CNTransActionAppearanceImp(accessibility, state, title));
}

CNTransActionAppearanceImp::~CNTransActionAppearanceImp() {}

CNTransActionAppearanceImp::CNTransActionAppearanceImp(CNActionAccessibilityPtr accessibility,
                                                       CNActionStatePtr state,
                                                       CNActionTitlePtr title)
        : accessibility(accessibility),
          state(state),
          title(title) {}

bool CNTransActionAppearanceImp::isAccessible() {
    return accessibility->isAccessible();
}
CNActionStates CNTransActionAppearanceImp::getState() {
    return state->getState();
}
std::string CNTransActionAppearanceImp::getTitle() {
    return title->getTitle();
}
