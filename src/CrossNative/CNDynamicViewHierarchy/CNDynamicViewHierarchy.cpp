#include "CNDynamicViewHierarchy.h"

#include "CrossNative/CNView/CNView.h"
#include "CrossNative/CNMatcher/CNMatcher.h"

CNDynamicViewHierarchyPtr CNDynamicViewHierarchy::getNewInstance() {
    return CNDynamicViewHierarchyPtr(new CNDynamicViewHierarchy());
}

CNDynamicViewHierarchy::~CNDynamicViewHierarchy() {}

CNDynamicViewHierarchy::CNDynamicViewHierarchy() {}

void CNDynamicViewHierarchy::load(std::shared_ptr<CNView> view, std::shared_ptr<CNMatcher> matcher) {

}
