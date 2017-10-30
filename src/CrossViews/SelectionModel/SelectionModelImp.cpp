#include "SelectionModelImp.h"
#include "Base/CNSubject/CNSubject.h"

SelectionModelImpPtr SelectionModelImp::getNewInstance() {
    return SelectionModelImpPtr(new SelectionModelImp());
}

SelectionModelImp::~SelectionModelImp() {

}

SelectionModelImp::SelectionModelImp() : subject(CNSubject::getNewInstance()){}

bool SelectionModelImp::hasSelection() {
    return selectedIndex.isValid();
}

void SelectionModelImp::setSelectedIndex(const CNHierarchyIndex& index) {
    selectedIndex = index;

    notifyObservers();
}

CNHierarchyIndex SelectionModelImp::getSelectedIndex() {
    return selectedIndex;
}

void SelectionModelImp::attach(std::shared_ptr<CNObserver> observer) {
    subject->attach(observer);
}
void SelectionModelImp::detach(std::shared_ptr<CNObserver> observer) {
    subject->detach(observer);
}
void SelectionModelImp::notifyObservers() {
    subject->notifyObservers();
}
