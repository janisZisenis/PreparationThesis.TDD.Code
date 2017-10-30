#include "CBRedoDependentAccessibility.h"
#include "Base/CBCommandHistory/CBCommandHistory.h"

CBRedoDependentAccessibilityPtr CBRedoDependentAccessibility::getNewInstance(CBCommandHistoryPtr commandHistory) {
    return CBRedoDependentAccessibilityPtr(new CBRedoDependentAccessibility(commandHistory));
}

CBRedoDependentAccessibility::~CBRedoDependentAccessibility() {}

CBRedoDependentAccessibility::CBRedoDependentAccessibility(CBCommandHistoryPtr commandHistory)
        : commandHistory(commandHistory) {}

bool CBRedoDependentAccessibility::isAccessible() {
    return commandHistory->redoIsPossible();
}
