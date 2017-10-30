#include "CNUndoDependentAccessibility.h"
#include "Base/CNCommandHistory/CNCommandHistory.h"

CNUndoDependentAccessibilityPtr CNUndoDependentAccessibility::getNewInstance(CNCommandHistoryPtr commandHistory) {
    return CNUndoDependentAccessibilityPtr(new CNUndoDependentAccessibility(commandHistory));
}

CNUndoDependentAccessibility::~CNUndoDependentAccessibility() {}

CNUndoDependentAccessibility::CNUndoDependentAccessibility(CNCommandHistoryPtr commandHistory)
        : commandHistory(commandHistory) {}

bool CNUndoDependentAccessibility::isAccessible() {
    return commandHistory->undoIsPossible();
}
