#include "CNDynamicViewHierarchy.h"

#include "CrossNative/CNView/CNView.h"
#include "CrossNative/CNMatcher/CNMatcher.h"

CNDynamicViewHierarchyPtr CNDynamicViewHierarchy::getNewInstance() {
    return CNDynamicViewHierarchyPtr(new CNDynamicViewHierarchy());
}

CNDynamicViewHierarchy::~CNDynamicViewHierarchy() {}

CNDynamicViewHierarchy::CNDynamicViewHierarchy() {}

void CNDynamicViewHierarchy::load(CNViewPtr view, CNMatcherPtr matcher) {
    if(views.size() == 0) {
        views.push_back(view);
    } else if(views.size() == 1) {
        views.push_back(view);
        if(matcher->matches(views[0])) {
            views[0]->add(view);
        }
    } else {
        if(matcher->matches(views[0])) {
            views[0]->add(view);
        }
        if(matcher->matches(views[1])) {
            views[1]->add(view);
        }
    }
}
