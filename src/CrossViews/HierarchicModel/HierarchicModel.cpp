#include "HierarchicModel.h"
#include "HierarchicModelListener.h"
#include <CrossNative/CNHierarchy/CNHierarchy.h>
#include <CrossNative/CNComponent/CNComponent.h>

HierarchicModelPtr HierarchicModel::getNewInstance() {
    return HierarchicModelPtr(new HierarchicModel());
}
HierarchicModel::~HierarchicModel() {}
HierarchicModel::HierarchicModel()
        : hierarchy(CNHierarchy::getNewInstance()) {}


void HierarchicModel::add(CNComponentPtr component, const CNHierarchyIndex& parent) {
    hierarchy->add(component, parent);

    notifyInserted(component, parent, hierarchy->retrieve(parent)->getChildCount() - 1);
}

void HierarchicModel::remove(CNComponentPtr component, const CNHierarchyIndex& parent) {
    int childPos = -1;
    for(int i = 0; i < hierarchy->retrieve(parent)->getChildCount(); i++) {
        if(hierarchy->retrieve(CNHierarchyIndex(parent, i)) == component) {
            childPos = i;
            break;
        }
    }
    hierarchy->remove(component, parent);

    notifyRemoved(CNHierarchyIndex(parent, childPos));
}

void HierarchicModel::insert(CNComponentPtr component, const CNHierarchyIndex& parent, int childPos) {
    hierarchy->insert(component, parent, childPos);

    notifyInserted(component, parent, childPos);
}

void HierarchicModel::remove(const CNHierarchyIndex& parent, int childPos) {
    hierarchy->remove(parent, childPos);

    notifyRemoved(CNHierarchyIndex(parent, childPos));
}

CNComponentPtr HierarchicModel::retrieve(const CNHierarchyIndex& index) {
    return hierarchy->retrieve(index);
}


void HierarchicModel::attach(HierarchicModelListenerPtr listener) {
    listeners.push_back(listener);
}

void HierarchicModel::detach(HierarchicModelListenerPtr listener) {
    for(int i = 0; i < listeners.size(); i++) {
        if(!listeners[i].lock() || listeners[i].lock() == listener) {
            listeners.erase(listeners.begin() + i);
            i--;
        }
    }
}

void HierarchicModel::notifyInserted(CNVisitablePtr visitable, const CNHierarchyIndex& parent, int childPos) {
    for(int i = 0; i < listeners.size(); i++)
        if(listeners[i].lock()) listeners[i].lock()->onInsert(visitable, parent, childPos);
        else listeners.erase(listeners.begin() + i--);
}

void HierarchicModel::notifyRemoved(const CNHierarchyIndex& index) {
    for(int i = 0; i < listeners.size(); i++)
        if(listeners[i].lock()) listeners[i].lock()->onRemove(index);
        else listeners.erase(listeners.begin() + i--);
}