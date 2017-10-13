#include "CNDynamicViewHierarchy.h"

#include "CrossNative/CNView/CNView.h"
#include "CrossNative/CNMatcher/CNMatcher.h"

CNDynamicViewHierarchyPtr CNDynamicViewHierarchy::getNewInstance() {
    return CNDynamicViewHierarchyPtr(new CNDynamicViewHierarchy());
}

CNDynamicViewHierarchy::~CNDynamicViewHierarchy() {}

CNDynamicViewHierarchy::CNDynamicViewHierarchy() {}

void CNDynamicViewHierarchy::load(CNViewPtr view, CNMatcherPtr matcher) {
    for(int i = 0; i < views.size(); i++) {
        if (views[i] == view)
            throw CNViewAlreadyLoadedException();
        if (matcher->matches(views[i]))
            views[i]->add(view);
    }

    views.push_back(view);
}

void CNDynamicViewHierarchy::unload(CNViewPtr view) {
    if(views.size() == 0) throw CNViewNotLoadedException();
    if(views.size() == 1 && views[0] != view) throw CNViewNotLoadedException();

    for(int i = 0; i < views.size(); i++)
        if(views[i]->isParentOf(view))
            views[i]->remove(view);
}
