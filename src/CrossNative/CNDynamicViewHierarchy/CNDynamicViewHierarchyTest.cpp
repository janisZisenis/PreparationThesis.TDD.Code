#include <gmock/gmock.h>
#include <string>

#include "CNDynamicViewHierarchy.h"

#include "CrossNative/CNView/CNViewTestDoubles.h"

class CNDynamicViewHierarchyTest : public testing::Test {
protected:
    virtual CNDynamicViewHierarchyPtr makeCNDynamicViewHierarchy() {
        return CNDynamicViewHierarchy::getNewInstance();
    }
    virtual CNViewSpyPtr makeCNViewSpy() {
        return CNViewSpy::getNewInstance();
    }

    virtual CNViewDummyPtr makeCNViewDummy() {
        return CNViewDummy::getNewInstance();
    }

    virtual void expectEquals(CNViewPtr actual, CNViewPtr expected, std::string errorMessage) {
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectUnequals(CNViewPtr actual, CNViewPtr unexpected, std::string errorMessage) {
        EXPECT_THAT(actual, testing::Ne(unexpected)) << errorMessage;
    }

    virtual void expect_View_Added_View(CNViewSpyPtr receiver, CNViewPtr view, std::string errorMessage) {
        CNViewPtr expected = view;
        CNViewPtr actual = receiver->getAddedView();

        expectEquals(actual, expected, errorMessage);
    }
    virtual void expect_Receiver_DidNotAdd_View(CNViewSpyPtr receiver, CNViewPtr view, std::string errorMessage) {
        CNViewPtr unexpected = view;
        CNViewPtr actual = receiver->getAddedView();

        expectUnequals(actual, unexpected, errorMessage);
    }
};

TEST_F(CNDynamicViewHierarchyTest, Loaded_View__LoadSubView_Matching__SubView_ShouldBeAddedTo_View) {
    CNDynamicViewHierarchyPtr sut = makeCNDynamicViewHierarchy();
    CNViewSpyPtr view = makeCNViewSpy();
    sut->load(view, false);

    CNViewDummyPtr subView = makeCNViewDummy();
    sut->load(subView, true);

    std::string errorMessage = "SubView should be added to View, but it was not!";
    expect_View_Added_View(view, subView, errorMessage);
}

TEST_F(CNDynamicViewHierarchyTest, Loaded_View_LoadSubView_NotMatching_ShouldNotBeAddedTo_View) {
    CNDynamicViewHierarchyPtr sut = makeCNDynamicViewHierarchy();
    CNViewSpyPtr view = makeCNViewSpy();
    sut->load(view, false);

    CNViewDummyPtr subView = makeCNViewDummy();
    sut->load(subView, false);

    std::string errorMessage = "SubView should not be added to View, but it was!";
    expect_Receiver_DidNotAdd_View(view, subView, errorMessage);
}
