#include <gmock/gmock.h>
#include "CNDynamicViewHierarchy.h"

#include <string>

#include "CrossNative/CNView/CNViewTestDoubles.h"

#include "CrossNative/CNMatcher/CNFakeMatcher.h"
#include "CrossNative/CNMatcher/CNMatcherTestDoubles.h"

class CNDynamicViewHierarchyTest : public testing::Test {
protected:
    virtual CNDynamicViewHierarchyPtr makeCNDynamicViewHierarchy() {
        return CNDynamicViewHierarchy::getNewInstance();
    }
};

TEST_F(CNDynamicViewHierarchyTest, Loaded_View__LoadSubView__SubView_ShouldBeAddedTo_View) {
    CNDynamicViewHierarchyPtr sut = makeCNDynamicViewHierarchy();
    CNViewSpyPtr view = CNViewSpy::getNewInstance();
    sut->load(view);

    CNViewDummyPtr subView = CNViewDummy::getNewInstance();
    sut->load(subView);

    CNViewPtr actual = view->getAddedView();
    CNViewPtr expected = subView;
    EXPECT_THAT(actual, testing::Eq(expected)) << "SubView was added to View";
}
