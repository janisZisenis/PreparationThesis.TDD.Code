#include "CBUndoDependentAccessibility.h"
#include "Base/CBCommandHistory/CBCommandHistory.h"

CBUndoDependentAccessibilityPtr CBUndoDependentAccessibility::getNewInstance(CBCommandHistoryPtr commandHistory) {
    return CBUndoDependentAccessibilityPtr(new CBUndoDependentAccessibility(commandHistory));
}

CBUndoDependentAccessibility::~CBUndoDependentAccessibility() {}

CBUndoDependentAccessibility::CBUndoDependentAccessibility(CBCommandHistoryPtr commandHistory)
        : commandHistory(commandHistory) {}

bool CBUndoDependentAccessibility::isAccessible() {
    return commandHistory->undoIsPossible();
}
