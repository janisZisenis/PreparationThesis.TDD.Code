#include "CNDynamicViewHierarchy.h"

#include "CNView.h"
#include "CNMatcher.h"

CNDynamicViewHierarchyPtr CNDynamicViewHierarchy::getNewInstance() {
    return CNDynamicViewHierarchyPtr(new CNDynamicViewHierarchy());
}

CNDynamicViewHierarchy::~CNDynamicViewHierarchy() {}

CNDynamicViewHierarchy::CNDynamicViewHierarchy() {}

void CNDynamicViewHierarchy::load(std::shared_ptr<CNView> view, std::shared_ptr<CNMatcher> matcher) {

}
