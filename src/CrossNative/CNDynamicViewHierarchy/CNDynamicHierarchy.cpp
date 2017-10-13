#include "CNDynamicHierarchy.h"

#include "CrossNative/CNComponent/CNComponent.h"
#include "CrossNative/CNMatcher/CNMatcher.h"

CNDynamicHierarchyPtr CNDynamicHierarchy::getNewInstance() {
    return CNDynamicHierarchyPtr(new CNDynamicHierarchy());
}

CNDynamicHierarchy::~CNDynamicHierarchy() {}

CNDynamicHierarchy::CNDynamicHierarchy() {}

void CNDynamicHierarchy::load(CNComponentPtr view, CNMatcherPtr matcher) {
    if (isAlreadyLoaded(view))
        throw CNComponentAlreadyLoadedException();

    loadView(view, matcher);
}

void CNDynamicHierarchy::unload(CNComponentPtr view) {
    if(!isAlreadyLoaded(view))
        throw CNComponentNotLoadedException();

    unloadView(view);
}

void CNDynamicHierarchy::move(CNComponentPtr view, CNMatcherPtr matcher) {
    unload(view);
    loadView(view, matcher);
}

void CNDynamicHierarchy::loadView(CNComponentPtr view, CNMatcherPtr matcher) {
    addToParent(view, matcher);
    addToViewList(view);
}

void CNDynamicHierarchy::unloadView(std::shared_ptr<CNComponent> view) {
    removeFromViewList(view);
    removeFromParent(view);
}

void CNDynamicHierarchy::addToViewList(CNComponentPtr view) {
    views.push_back(view);
}

void CNDynamicHierarchy::addToParent(CNComponentPtr view, CNMatcherPtr matcher) {
    for(int i = 0; i < views.size(); i++)
        if (matcher->matches(views[i]))
            views[i]->add(view);
}

void CNDynamicHierarchy::removeFromViewList(CNComponentPtr view) {
    views.erase(views.begin()+findPosition(view));
}

void CNDynamicHierarchy::removeFromParent(CNComponentPtr view) {
    for(int i = 0; i < views.size(); i++)
        if(views[i]->isParentOf(view))
            views[i]->remove(view);
}

bool CNDynamicHierarchy::isAlreadyLoaded(CNComponentPtr view) {
    return findPosition(view) > -1;
}

int CNDynamicHierarchy::findPosition(std::shared_ptr<CNComponent> view) {
    for(int i = 0; i < views.size(); i++) {
        if(views[i] == view)
            return i;
    }

    return -1;
}

