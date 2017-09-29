#include <gmock/gmock.h>
#include <string>

#include "CNDynamicViewHierarchy.h"
#include "CNMatcherTestDoubles.h"

class CNDynamicViewHierarchyTest : public testing::Test {
protected:
    virtual CNDynamicViewHierarchyPtr makeCNDynamicViewHierarchy() {
        return CNDynamicViewHierarchy::getNewInstance();
    }
};
