#include "CNDynamicViewHierarchy.h"

#include "CrossNative/CNView/CNView.h"

CNDynamicViewHierarchyPtr CNDynamicViewHierarchy::getNewInstance() {
    return CNDynamicViewHierarchyPtr(new CNDynamicViewHierarchy());
}

CNDynamicViewHierarchy::~CNDynamicViewHierarchy() {}

CNDynamicViewHierarchy::CNDynamicViewHierarchy() {}

void CNDynamicViewHierarchy::load(CNViewPtr view, bool matches) {
    if(!firstView) {
        firstView = view;
        return;
    }

    if(!secondView) {
        secondView = view;
        if (matches)
            firstView->add(view);
    }

    secondView->add(view);
}
