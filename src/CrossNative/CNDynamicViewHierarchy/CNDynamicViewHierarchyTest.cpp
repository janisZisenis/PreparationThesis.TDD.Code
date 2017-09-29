#include <gmock/gmock.h>
#include "CNDynamicViewHierarchy.h"

#include "CrossNative/CNView/CNViewTestDoubles.h"

class CNDynamicViewHierarchyTest : public testing::Test {
protected:
    virtual CNDynamicViewHierarchyPtr makeCNDynamicViewHierarchy() {
        return CNDynamicViewHierarchy::getNewInstance();
    }
};

TEST_F(CNDynamicViewHierarchyTest, Loaded_View__LoadSubView_Matching__SubView_ShouldBeAddedTo_View) {
    CNDynamicViewHierarchyPtr sut = makeCNDynamicViewHierarchy();
    CNViewSpyPtr view = CNViewSpy::getNewInstance();
    sut->load(view, false);

    CNViewDummyPtr subView = CNViewDummy::getNewInstance();
    sut->load(subView, true);

    CNViewPtr actual = view->getAddedView();
    CNViewPtr expected = subView;
    EXPECT_THAT(actual, testing::Eq(expected)) << "SubView should be added to View, but it was not!";
}

TEST_F(CNDynamicViewHierarchyTest, Loaded_View_LoadSubView_NotMatching_ShouldNotBeAddedTo_View) {
    CNDynamicViewHierarchyPtr sut = makeCNDynamicViewHierarchy();
    CNViewSpyPtr view = CNViewSpy::getNewInstance();
    sut->load(view, false);

    CNViewDummyPtr subView = CNViewDummy::getNewInstance();
    sut->load(subView, false);

    CNViewPtr actual = view->getAddedView();
    CNViewPtr expected = subView;
    EXPECT_THAT(actual, testing::Ne(expected)) << "SubView should not be added to View, but it was!";
}
