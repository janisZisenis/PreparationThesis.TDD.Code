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
    } else if(!secondView) {
        secondView = view;
        if(matches) {
            firstView->add(view);
        }
    } else {
        if(matches) {
            secondView->add(view);
        }
        firstView->add(view);
    }
}
