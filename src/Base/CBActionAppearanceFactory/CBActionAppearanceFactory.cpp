#include "CBActionAppearanceFactory.h"
#include "Base/CBActionAppearance/CBTransActionAppearanceImp/CBTransActionAppearanceImp.h"
#include "Base/CBActionAppearance/CBFixedActionAppearance/CBFixedAppearance.h"
#include "Base/CBActionAppearance/CBFixedActionAppearance/CBFixedAccessibility.h"
#include "Base/CBActionAppearance/CBFixedActionAppearance/CBFixedState.h"
#include "Base/CBActionAppearance/CBFixedActionAppearance/CBFixedTitle.h"

CBActionAppearanceFactoryPtr CBActionAppearanceFactory::getNewInstance() {
    return CBActionAppearanceFactoryPtr(new CBActionAppearanceFactory());
}
CBActionAppearanceFactory::~CBActionAppearanceFactory() {}
CBActionAppearanceFactory::CBActionAppearanceFactory() {}

CBTransActionAppearancePtr CBActionAppearanceFactory::makeCBTransActionAppearance(std::shared_ptr<CBActionAccessibility> accessibility,
                                                                                  std::shared_ptr<CBActionState> state,
                                                                                  std::shared_ptr<CBActionTitle> title) {
    return CBTransActionAppearanceImp::getNewInstance(accessibility, state, title);
}

CBTransActionAppearancePtr CBActionAppearanceFactory::makeCBFixedTransActionAppearance(bool accessibility,
                                                                                       CBActionStates state,
                                                                                       std::string title) {
    return CBFixedAppearance::getNewInstance(accessibility, state, title);
}

CBActionAccessibilityPtr CBActionAppearanceFactory::makeCBFixedActionAccessibility(bool accessibility) {
    return CBFixedAccessibility::getNewInstance(accessibility);
}
CBActionStatePtr CBActionAppearanceFactory::makeCBFixedActionState(CBActionStates state) {
    return CBFixedState::getNewInstance(state);
}
CBActionTitlePtr CBActionAppearanceFactory::makeCBFixedActionTitle(std::string title) {
    return CBFixedTitle::getNewInstance(title);
}
