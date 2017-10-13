#include <gmock/gmock.h>
#include <string>

#include "CNDynamicViewHierarchy.h"

#include "CrossNative/CNView/CNViewTestDoubles.h"
#include "CrossNative/CNView/CNFakeView.h"

#include "CrossNative/CNMatcher/CNMatcherTestDoubles.h"
#include "CrossNative/CNMatcher/CNFakeMatcher.h"

class CNDynamicViewHierarchyTest : public testing::Test {
protected:
    virtual CNDynamicViewHierarchyPtr makeCNDynamicViewHierarchy() {
        return CNDynamicViewHierarchy::getNewInstance();
    }
    virtual CNViewPtr makeCNViewDummy() {
        return CNViewDummy::getNewInstance();
    }
    virtual CNViewSpyPtr makeCNViewSpy() {
        return CNViewSpy::getNewInstance();
    }
    virtual CNViewPtr makeCNFakeView() {
        return CNFakeView::getNewInstance();
    }

    virtual CNFakeMatcherPtr makeCNFakeMatcher(CNViewPtr matchingView) {
        return CNFakeMatcher::getNewInstance(matchingView);
    }
    virtual CNMatcherStubPtr makeNotMatchingCNMatcher() {
        CNMatcherStubPtr matcher = makeCNMatcherStub();
        matcher->setIsMatching(false);
        return matcher;
    }
    virtual CNMatcherStubPtr makeCNMatcherStub() {
        return CNMatcherStub::getNewInstance();
    }

    virtual void expectEquals(CNViewPtr actual, CNViewPtr expected, std::string errorMessage) {
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectUnequals(CNViewPtr actual, CNViewPtr unexpected, std::string errorMessage) {
        EXPECT_THAT(actual, testing::Ne(unexpected)) << errorMessage;
    }

    virtual void expectReceiverAddedView(CNViewSpyPtr receiver, CNViewPtr view, std::string errorMessage) {
        CNViewPtr expected = view;
        CNViewPtr actual = receiver->getAddedView();

        expectEquals(actual, expected, errorMessage);
    }
    virtual void expectReceiverDidNotAddView(CNViewSpyPtr receiver, CNViewPtr view, std::string errorMessage) {
        CNViewPtr unexpected = view;
        CNViewPtr actual = receiver->getAddedView();

        expectUnequals(actual, unexpected, errorMessage);
    }

    virtual std::string getReceiverAddedViewErrorMessage(std::string receiverName, std::string viewName) {
        return viewName + " should be added to " + receiverName + ", but it was not!";
    }
    virtual std::string getReceiverDidNotAddViewErrorMessage(std::string receiverName, std::string viewName) {
        return viewName + " should not be added to " + receiverName + ", but it was!";
    }
};

TEST_F(CNDynamicViewHierarchyTest, LoadedFirstView__LoadSecondViewMatching__SecondViewShouldBeAddedToFirstView) {
    CNDynamicViewHierarchyPtr sut = makeCNDynamicViewHierarchy();
    CNViewSpyPtr firstView = makeCNViewSpy();
    sut->load(firstView, makeNotMatchingCNMatcher());

    CNViewPtr secondView = makeCNViewDummy();
    sut->load(secondView, makeCNFakeMatcher(firstView));

    std::string errorMessage = getReceiverAddedViewErrorMessage("FirstView", "SecondView");
    expectReceiverAddedView(firstView, secondView, errorMessage);
}

TEST_F(CNDynamicViewHierarchyTest, LoadedFirstView__LoadSecondViewNotMatching__SecondViewShouldNotBeAddedToFirstView) {
    CNDynamicViewHierarchyPtr sut = makeCNDynamicViewHierarchy();
    CNViewSpyPtr firstView = makeCNViewSpy();
    sut->load(firstView, makeNotMatchingCNMatcher());

    CNViewPtr secondView = makeCNViewDummy();
    sut->load(secondView, makeNotMatchingCNMatcher());

    std::string errorMessage = getReceiverDidNotAddViewErrorMessage("FirstView", "SecondView");
    expectReceiverDidNotAddView(firstView, secondView, errorMessage);
}

TEST_F(CNDynamicViewHierarchyTest, LoadedFirstView_LoadedSecondViewMatchingFirstView__LoadThirdViewMatching__ThirdViewShouldBeAddedToSecondView) {
    CNDynamicViewHierarchyPtr sut = makeCNDynamicViewHierarchy();
    CNViewPtr firstView = makeCNFakeView();
    sut->load(firstView, makeNotMatchingCNMatcher());
    CNViewSpyPtr secondView = makeCNViewSpy();
    sut->load(secondView, makeCNFakeMatcher(firstView));

    CNViewPtr thirdView = makeCNViewDummy();
    sut->load(thirdView, makeCNFakeMatcher(secondView));

    std::string errorMessage = getReceiverAddedViewErrorMessage("SecondView", "ThirdView");
    expectReceiverAddedView(secondView, thirdView, errorMessage);
}

TEST_F(CNDynamicViewHierarchyTest, LoadedFirstView_LoadedSecondViewMatchingFirstView__LoadThirdViewNotMatching__ThirdViewShouldNotBeAddedToSecondView) {
    CNDynamicViewHierarchyPtr sut = makeCNDynamicViewHierarchy();
    CNViewPtr firstView = makeCNFakeView();
    sut->load(firstView, makeNotMatchingCNMatcher());
    CNViewSpyPtr secondView = makeCNViewSpy();
    sut->load(secondView, makeCNFakeMatcher(firstView));

    CNViewPtr thirdView = makeCNViewDummy();
    sut->load(thirdView, makeNotMatchingCNMatcher());

    std::string errorMessage = getReceiverDidNotAddViewErrorMessage("SecondView", "ThirdView");
    expectReceiverDidNotAddView(secondView, thirdView, errorMessage);
}

TEST_F(CNDynamicViewHierarchyTest, LoadedFirstView_LoadedSecondViewMatchingFirstView__LoadThirdViewMatching__ThirdViewShouldBeAddedToFirstView) {
    CNDynamicViewHierarchyPtr sut = makeCNDynamicViewHierarchy();
    CNViewSpyPtr firstView = makeCNViewSpy();
    sut->load(firstView, makeNotMatchingCNMatcher());
    CNViewPtr secondView = makeCNViewDummy();
    sut->load(secondView, makeCNFakeMatcher(firstView));

    CNViewPtr thirdView = makeCNViewDummy();
    sut->load(thirdView, makeCNFakeMatcher(firstView));

    std::string errorMessage = getReceiverAddedViewErrorMessage("FirstView", "ThirdView");
    expectReceiverAddedView(firstView, thirdView, errorMessage);
}

TEST_F(CNDynamicViewHierarchyTest, LoadedFirstView_LoadedSecondViewMatchingFirstView__LoadThirdViewNotMatching__ThirdViewShouldNotBeAddedToFirstView) {
    CNDynamicViewHierarchyPtr sut = makeCNDynamicViewHierarchy();
    CNViewSpyPtr firstView = makeCNViewSpy();
    sut->load(firstView, makeNotMatchingCNMatcher());
    CNViewPtr secondView = makeCNViewDummy();
    sut->load(secondView, makeCNFakeMatcher(firstView));

    CNViewPtr thirdView = makeCNViewDummy();
    sut->load(thirdView, makeNotMatchingCNMatcher());

    std::string errorMessage = getReceiverDidNotAddViewErrorMessage("FirstView", "ThirdView");
    expectReceiverDidNotAddView(firstView, thirdView, errorMessage);
}

TEST_F(CNDynamicViewHierarchyTest, LoadedFirstView_LoadedSecondViewMatchingFirstView__LoadThirdViewMatchingFirstView__ThirdViewShouldNotBeAddedToSecondView) {
    CNDynamicViewHierarchyPtr sut = makeCNDynamicViewHierarchy();
    CNViewPtr firstView = makeCNFakeView()  ;
    sut->load(firstView, makeNotMatchingCNMatcher());
    CNViewSpyPtr secondView = makeCNViewSpy();
    sut->load(secondView, makeCNFakeMatcher(firstView));

    CNViewPtr thirdView = makeCNViewDummy();
    sut->load(thirdView, makeCNFakeMatcher(firstView));

    std::string errorMessage = getReceiverDidNotAddViewErrorMessage("SecondView", "ThirdView");
    expectReceiverDidNotAddView(secondView, thirdView, errorMessage);
}

TEST_F(CNDynamicViewHierarchyTest, LoadedFirstViewNotMatching_LoadedFirstViewNotMatching_ShouldThrowCNViewAlreadyLoadedException) {
    CNDynamicViewHierarchyPtr sut = makeCNDynamicViewHierarchy();
    CNViewPtr firstView = makeCNViewDummy();
    sut->load(firstView, makeNotMatchingCNMatcher());

    EXPECT_THROW(sut->load(firstView, makeNotMatchingCNMatcher()), CNViewAlreadyLoadedException);
}