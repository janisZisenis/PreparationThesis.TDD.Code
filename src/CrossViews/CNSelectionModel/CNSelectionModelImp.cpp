#include "CNSelectionModelImp.h"
#include <Base/CNSubject/CNSubject.h>

CNSelectionModelImpPtr CNSelectionModelImp::getNewInstance() {
    return CNSelectionModelImpPtr(new CNSelectionModelImp());
}

CNSelectionModelImp::~CNSelectionModelImp() {

}

CNSelectionModelImp::CNSelectionModelImp() : subject(CNSubject::getNewInstance()){}

bool CNSelectionModelImp::hasSelection() {
    return selectedIndex.isValid();
}

void CNSelectionModelImp::setSelectedIndex(const CNHierarchyIndex& index) {
    selectedIndex = index;

    notifyObservers();
}

CNHierarchyIndex CNSelectionModelImp::getSelectedIndex() {
    return selectedIndex;
}

void CNSelectionModelImp::attach(std::shared_ptr<CNObserver> observer) {
    subject->attach(observer);
}
void CNSelectionModelImp::detach(std::shared_ptr<CNObserver> observer) {
    subject->detach(observer);
}
void CNSelectionModelImp::notifyObservers() {
    subject->notifyObservers();
}
