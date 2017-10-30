#include "CNActionAppearanceFactory.h"
#include "Base/CNActionAppearance/CNTransActionAppearanceImp/CNTransActionAppearanceImp.h"
#include "Base/CNActionAppearance/CNFixedActionAppearance/CNFixedAppearance.h"
#include "Base/CNActionAppearance/CNFixedActionAppearance/CNFixedAccessibility.h"
#include "Base/CNActionAppearance/CNFixedActionAppearance/CNFixedState.h"
#include "Base/CNActionAppearance/CNFixedActionAppearance/CNFixedTitle.h"

CNActionAppearanceFactoryPtr CNActionAppearanceFactory::getNewInstance() {
    return CNActionAppearanceFactoryPtr(new CNActionAppearanceFactory());
}
CNActionAppearanceFactory::~CNActionAppearanceFactory() {}
CNActionAppearanceFactory::CNActionAppearanceFactory() {}

CNTransActionAppearancePtr CNActionAppearanceFactory::makeCNTransActionAppearance(
        std::shared_ptr<CNActionAccessibility> accessibility,
        std::shared_ptr<CNActionState> state,
        std::shared_ptr<CNActionTitle> title) {
    return CNTransActionAppearanceImp::getNewInstance(accessibility, state, title);
}

CNTransActionAppearancePtr CNActionAppearanceFactory::makeCNFixedTransActionAppearance(bool accessibility,
                                                                                       CNActionStates state,
                                                                                       std::string title) {
    return CNFixedAppearance::getNewInstance(accessibility, state, title);
}

CNActionAccessibilityPtr CNActionAppearanceFactory::makeCNFixedActionAccessibility(bool accessibility) {
    return CNFixedAccessibility::getNewInstance(accessibility);
}
CNActionStatePtr CNActionAppearanceFactory::makeCNFixedActionState(CNActionStates state) {
    return CNFixedState::getNewInstance(state);
}
CNActionTitlePtr CNActionAppearanceFactory::makeCNFixedActionTitle(std::string title) {
    return CNFixedTitle::getNewInstance(title);
}
