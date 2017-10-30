#include "CBTransActionAppearanceImp.h"

#include "Base/CBTransActionAppearance/CBActionAccessibility.h"
#include "Base/CBTransActionAppearance/CBActionState.h"
#include "Base/CBTransActionAppearance/CBActionTitle.h"

CBTransActionAppearanceImpPtr CBTransActionAppearanceImp::getNewInstance(CBActionAccessibilityPtr accessibility,
                                                                         CBActionStatePtr state,
                                                                         CBActionTitlePtr title) {
    return CBTransActionAppearanceImpPtr(new CBTransActionAppearanceImp(accessibility, state, title));
}

CBTransActionAppearanceImp::~CBTransActionAppearanceImp() {}

CBTransActionAppearanceImp::CBTransActionAppearanceImp(CBActionAccessibilityPtr accessibility,
                                                       CBActionStatePtr state,
                                                       CBActionTitlePtr title)
        : accessibility(accessibility),
          state(state),
          title(title) {}

bool CBTransActionAppearanceImp::isAccessible() {
    return accessibility->isAccessible();
}
CBActionStates CBTransActionAppearanceImp::getState() {
    return state->getState();
}
std::string CBTransActionAppearanceImp::getTitle() {
    return title->getTitle();
}
