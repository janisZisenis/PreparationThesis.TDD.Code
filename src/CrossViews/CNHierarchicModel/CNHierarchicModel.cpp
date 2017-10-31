#include "CNHierarchicModel.h"
#include "CNHierarchicModelListener.h"
#include <Hierarchies/CNHierarchy/CNHierarchy.h>
#include <Hierarchies/CNComponent/CNComponent.h>

CNHierarchicModelPtr CNHierarchicModel::getNewInstance() {
    return CNHierarchicModelPtr(new CNHierarchicModel());
}
CNHierarchicModel::~CNHierarchicModel() {}
CNHierarchicModel::CNHierarchicModel()
        : hierarchy(CNHierarchy::getNewInstance()) {}


void CNHierarchicModel::add(CNComponentPtr component, const CNHierarchyIndex& parent) {
    hierarchy->add(component, parent);

    notifyInserted(component, parent, hierarchy->getChildCountFor(parent) - 1);
}
void CNHierarchicModel::remove(CNComponentPtr component, const CNHierarchyIndex& parent) {
    int childPos = -1;
    for(int i = 0; i < hierarchy->getChildCountFor(parent); i++) {
        if(hierarchy->retrieve(CNHierarchyIndex(parent, i)) == component) {
            childPos = i;
            break;
        }
    }
    hierarchy->remove(component, parent);

    notifyRemoved(CNHierarchyIndex(parent, childPos));
}

void CNHierarchicModel::insert(CNComponentPtr component, const CNHierarchyIndex& parent, int childPos) {
    hierarchy->insert(component, parent, childPos);

    notifyInserted(component, parent, childPos);
}
void CNHierarchicModel::remove(const CNHierarchyIndex& parent, int childPos) {
    hierarchy->remove(parent, childPos);

    notifyRemoved(CNHierarchyIndex(parent, childPos));
}

CNComponentPtr CNHierarchicModel::retrieve(const CNHierarchyIndex& index) {
    return hierarchy->retrieve(index);
}


void CNHierarchicModel::addListener(CNHierarchicModelListenerPtr listener) {
    listeners.push_back(listener);
}
void CNHierarchicModel::removeListener(CNHierarchicModelListenerPtr listener) {
    for(int i = 0; i < listeners.size(); i++) {
        if(!listeners[i].lock() || listeners[i].lock() == listener) {
            listeners.erase(listeners.begin() + i);
            i--;
        }
    }
}

void CNHierarchicModel::notifyInserted(CNVisitablePtr visitable, const CNHierarchyIndex& parent, int childPos) {
    for(int i = 0; i < listeners.size(); i++)
        if(listeners[i].lock()) listeners[i].lock()->onInsert(visitable, parent, childPos);
        else listeners.erase(listeners.begin() + i--);
}
void CNHierarchicModel::notifyRemoved(const CNHierarchyIndex& index) {
    for(int i = 0; i < listeners.size(); i++)
        if(listeners[i].lock()) listeners[i].lock()->onRemove(index);
        else listeners.erase(listeners.begin() + i--);
}