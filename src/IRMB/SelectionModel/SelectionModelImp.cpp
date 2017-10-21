#include "SelectionModelImp.h"
#include "CodeBaseImp/CBSubject/CBSubject.h"

SelectionModelImpPtr SelectionModelImp::getNewInstance() {
    return SelectionModelImpPtr(new SelectionModelImp());
}

SelectionModelImp::~SelectionModelImp() {

}

SelectionModelImp::SelectionModelImp() : subject(CBSubject::getNewInstance()){}

bool SelectionModelImp::hasSelection() {
    return true;
}

void SelectionModelImp::setSelectedIndex(const CNHierarchyIndex& index) {}

CNHierarchyIndex SelectionModelImp::getSelectedIndex() {
    return CNHierarchyIndex();
}

void SelectionModelImp::attach(std::shared_ptr<CBObserver> observer) {}
void SelectionModelImp::detach(std::shared_ptr<CBObserver> observer) {}
void SelectionModelImp::notifyObservers() {}
