#include "CNDynamicViewHierarchy.h"

#include "CrossNative/CNView/CNView.h"
#include "CrossNative/CNMatcher/CNMatcher.h"

CNDynamicViewHierarchyPtr CNDynamicViewHierarchy::getNewInstance() {
    return CNDynamicViewHierarchyPtr(new CNDynamicViewHierarchy());
}

CNDynamicViewHierarchy::~CNDynamicViewHierarchy() {}

CNDynamicViewHierarchy::CNDynamicViewHierarchy() {}

void CNDynamicViewHierarchy::load(CNViewPtr view, CNMatcherPtr matcher) {
    if (isAlreadyLoaded(view))
        throw CNViewAlreadyLoadedException();

    loadView(view, matcher);
}

void CNDynamicViewHierarchy::unload(CNViewPtr view) {
    if(!isAlreadyLoaded(view))
        throw CNViewNotLoadedException();

    unloadView(view);
}

void CNDynamicViewHierarchy::move(CNViewPtr view, CNMatcherPtr matcher) {
    unloadView(view);
    loadView(view, matcher);
}

void CNDynamicViewHierarchy::loadView(CNViewPtr view, CNMatcherPtr matcher) {
    addToParent(view, matcher);
    addToViewList(view);
}

void CNDynamicViewHierarchy::unloadView(std::shared_ptr<CNView> view) {
    removeFromViewList(view);
    removeFromParent(view);
}

void CNDynamicViewHierarchy::addToViewList(CNViewPtr view) {
    views.push_back(view);
}

void CNDynamicViewHierarchy::addToParent(CNViewPtr view, CNMatcherPtr matcher) {
    for(int i = 0; i < views.size(); i++)
        if (matcher->matches(views[i]))
            views[i]->add(view);
}

void CNDynamicViewHierarchy::removeFromViewList(CNViewPtr view) {
    views.erase(views.begin()+findPosition(view));
}

void CNDynamicViewHierarchy::removeFromParent(CNViewPtr view) {
    for(int i = 0; i < views.size(); i++)
        if(views[i]->isParentOf(view))
            views[i]->remove(view);
}

bool CNDynamicViewHierarchy::isAlreadyLoaded(CNViewPtr view) {
    return findPosition(view) > -1;
}

int CNDynamicViewHierarchy::findPosition(std::shared_ptr<CNView> view) {
    for(int i = 0; i < views.size(); i++) {
        if(views[i] == view)
            return i;
    }

    return -1;
}

