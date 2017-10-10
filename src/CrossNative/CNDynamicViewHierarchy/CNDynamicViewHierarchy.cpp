#include "CNDynamicViewHierarchy.h"

#include "CrossNative/CNView/CNView.h"
#include "CrossNative/CNMatcher/CNMatcher.h"

CNDynamicViewHierarchyPtr CNDynamicViewHierarchy::getNewInstance() {
    return CNDynamicViewHierarchyPtr(new CNDynamicViewHierarchy());
}

CNDynamicViewHierarchy::~CNDynamicViewHierarchy() {}

CNDynamicViewHierarchy::CNDynamicViewHierarchy() {}

void CNDynamicViewHierarchy::load(CNViewPtr view, CNMatcherPtr matcher) {
    views.push_back(view);

    if(views.size() == 1) {
        for(int i = 0; i < 1; i++) {
            if (matcher->matches(views[i])) {
                views[i]->add(view);
            }
        }
    } else {
        for(int i = 0; i < 2; i++) {
            if (matcher->matches(views[i])) {
                views[i]->add(view);
            }
        }
    }
}
