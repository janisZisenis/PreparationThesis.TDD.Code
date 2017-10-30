#include "CNRedoDependentAccessibility.h"
#include "Base/CNCommandHistory/CNCommandHistory.h"

CNRedoDependentAccessibilityPtr CNRedoDependentAccessibility::getNewInstance(CNCommandHistoryPtr commandHistory) {
    return CNRedoDependentAccessibilityPtr(new CNRedoDependentAccessibility(commandHistory));
}

CNRedoDependentAccessibility::~CNRedoDependentAccessibility() {}

CNRedoDependentAccessibility::CNRedoDependentAccessibility(CNCommandHistoryPtr commandHistory)
        : commandHistory(commandHistory) {}

bool CNRedoDependentAccessibility::isAccessible() {
    return commandHistory->redoIsPossible();
}
