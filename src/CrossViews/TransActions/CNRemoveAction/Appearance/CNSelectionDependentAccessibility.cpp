#include "CNSelectionDependentAccessibility.h"
#include "CrossViews/CNSelectionModel/CNSelectionModel.h"

CNSelectionDependentAccessibilityPtr CNSelectionDependentAccessibility::getNewInstance(CNSelectionModelPtr selectionModel) {
    return CNSelectionDependentAccessibilityPtr(new CNSelectionDependentAccessibility(selectionModel));
}

CNSelectionDependentAccessibility::~CNSelectionDependentAccessibility() {}

CNSelectionDependentAccessibility::CNSelectionDependentAccessibility(CNSelectionModelPtr selectionModel)
        : selectionModel(selectionModel) {}

bool CNSelectionDependentAccessibility::isAccessible() {
    return selectionModel->hasSelection();
}
