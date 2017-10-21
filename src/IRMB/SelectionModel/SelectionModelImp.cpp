#include "SelectionModelImp.h"
#include "CodeBaseImp/CBSubject/CBSubject.h"

SelectionModelImpPtr SelectionModelImp::getNewInstance() {
    return SelectionModelImpPtr(new SelectionModelImp());
}

SelectionModelImp::~SelectionModelImp() {

}

SelectionModelImp::SelectionModelImp() : subject(CBSubject::getNewInstance()){}

bool SelectionModelImp::hasSelection() {
    return selectedIndex.isValid();
}

void SelectionModelImp::setSelectedIndex(const CNHierarchyIndex& index) {
    selectedIndex = index;
}

CNHierarchyIndex SelectionModelImp::getSelectedIndex() {
    return selectedIndex;
}

void SelectionModelImp::attach(std::shared_ptr<CBObserver> observer) {}
void SelectionModelImp::detach(std::shared_ptr<CBObserver> observer) {}
void SelectionModelImp::notifyObservers() {}
