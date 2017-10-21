#include "CNDynamicHierarchy.h"

#include "CrossNative/CNComponent/CNComponent.h"
#include "CrossNative/CNMatcher/CNMatcher.h"

CNDynamicHierarchyPtr CNDynamicHierarchy::getNewInstance() {
    return CNDynamicHierarchyPtr(new CNDynamicHierarchy());
}

CNDynamicHierarchy::~CNDynamicHierarchy() {}

CNDynamicHierarchy::CNDynamicHierarchy() {}

void CNDynamicHierarchy::load(CNComponentPtr component, CNMatcherPtr matcher) {
    if (isAlreadyLoaded(component))
        throw CNHierarchyNodeAlreadyLoadedException();

    loadComponent(component, matcher);
}

void CNDynamicHierarchy::unload(CNComponentPtr component) {
    if(!isAlreadyLoaded(component))
        throw CNHierarchyNodeNotLoadedException();

    unloadComponent(component);
}

void CNDynamicHierarchy::move(CNComponentPtr component, CNMatcherPtr matcher) {
    unload(component);
    loadComponent(component, matcher);
}

void CNDynamicHierarchy::loadComponent(CNComponentPtr component, CNMatcherPtr matcher) {
    addToParent(component, matcher);
    addToComponentList(component);
}

void CNDynamicHierarchy::unloadComponent(CNComponentPtr component) {
    removeFromComponentList(component);
    removeFromParent(component);
}

void CNDynamicHierarchy::addToComponentList(CNComponentPtr component) {
    components.push_back(component);
}

void CNDynamicHierarchy::addToParent(CNComponentPtr component, CNMatcherPtr matcher) {
    for(int i = 0; i < components.size(); i++)
        if (matcher->matches(components[i]))
            components[i]->add(component);
}

void CNDynamicHierarchy::removeFromComponentList(CNComponentPtr component) {
    components.erase(components.begin()+findPosition(component));
}

void CNDynamicHierarchy::removeFromParent(CNComponentPtr component) {
    for(int i = 0; i < components.size(); i++)
        if(components[i]->isParentOf(component))
            components[i]->remove(component);
}

bool CNDynamicHierarchy::isAlreadyLoaded(CNComponentPtr component) {
    return findPosition(component) > -1;
}

int CNDynamicHierarchy::findPosition(CNComponentPtr component) {
    std::vector< std::shared_ptr<CNComponent> >::iterator it;
    it = std::find(components.begin(), components.end(), component);

    return it == components.end() ? -1 : (int)(it - components.begin());
}

