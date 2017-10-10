#include "CNDynamicViewHierarchy.h"

#include "CrossNative/CNView/CNView.h"
#include "CrossNative/CNMatcher/CNMatcher.h"

CNDynamicViewHierarchyPtr CNDynamicViewHierarchy::getNewInstance() {
    return CNDynamicViewHierarchyPtr(new CNDynamicViewHierarchy());
}

CNDynamicViewHierarchy::~CNDynamicViewHierarchy() {}

CNDynamicViewHierarchy::CNDynamicViewHierarchy() {}

void CNDynamicViewHierarchy::load(CNViewPtr view, bool matches, CNMatcherPtr matcher) {
    if(!firstView) {
        firstView = view;
    } else if(!secondView) {
        secondView = view;
        if(matches) {
            firstView->add(view);
        }
    } else {
        if(matches) {
            firstView->add(view);
            if(!matcher->matches(firstView)) {
                secondView->add(view);
            }
        }

    }
}
