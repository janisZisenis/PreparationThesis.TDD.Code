#include "CNActionAppearanceFactory.h"
#include "Base/TransActionAppearances/CNTransActionAppearanceImp/CNTransActionAppearanceImp.h"
#include "Base/TransActionAppearances/CNFixedActionAppearance/CNFixedAppearance.h"
#include "Base/TransActionAppearances/CNFixedActionAppearance/CNFixedAccessibility.h"
#include "Base/TransActionAppearances/CNFixedActionAppearance/CNFixedState.h"
#include "Base/TransActionAppearances/CNFixedActionAppearance/CNFixedTitle.h"

CNActionAppearanceFactoryPtr CNActionAppearanceFactory::getNewInstance() {
    return CNActionAppearanceFactoryPtr(new CNActionAppearanceFactory());
}
CNActionAppearanceFactory::~CNActionAppearanceFactory() {}
CNActionAppearanceFactory::CNActionAppearanceFactory() {}

CNTransActionAppearancePtr CNActionAppearanceFactory::makeCNTransActionAppearance(
        std::shared_ptr<CNTransActionAccessibility> accessibility,
        std::shared_ptr<CNTransActionState> state,
        std::shared_ptr<CNTransActionTitle> title) {
    return CNTransActionAppearanceImp::getNewInstance(accessibility, state, title);
}

CNTransActionAppearancePtr CNActionAppearanceFactory::makeCNFixedTransActionAppearance(bool accessibility,
                                                                                       CNTransActionStateValues state,
                                                                                       std::string title) {
    return CNFixedAppearance::getNewInstance(accessibility, state, title);
}

CNTransActionAccessibilityPtr CNActionAppearanceFactory::makeCNFixedActionAccessibility(bool accessibility) {
    return CNFixedAccessibility::getNewInstance(accessibility);
}
CNTransActionStatePtr CNActionAppearanceFactory::makeCNFixedActionState(CNTransActionStateValues state) {
    return CNFixedState::getNewInstance(state);
}
CNTransActionTitlePtr CNActionAppearanceFactory::makeCNFixedActionTitle(std::string title) {
    return CNFixedTitle::getNewInstance(title);
}
