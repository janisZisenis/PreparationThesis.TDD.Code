#include "SelectionDependentAccessibility.h"
#include "CrossViews/SelectionModel/SelectionModel.h"

SelectionDependentAccessibilityPtr SelectionDependentAccessibility::getNewInstance(SelectionModelPtr selectionModel) {
    return SelectionDependentAccessibilityPtr(new SelectionDependentAccessibility(selectionModel));
}

SelectionDependentAccessibility::~SelectionDependentAccessibility() {}

SelectionDependentAccessibility::SelectionDependentAccessibility(SelectionModelPtr selectionModel)
        : selectionModel(selectionModel) {}

bool SelectionDependentAccessibility::isAccessible() {
    return selectionModel->hasSelection();
}
