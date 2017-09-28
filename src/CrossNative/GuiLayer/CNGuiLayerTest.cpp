#include <gmock/gmock.h>
#include <string>

#include "CNGuiLayer.h"

#include "CNView.h"
#include "CNFakeView.h"
#include "CNViewTestDoubles.h"

#include "CNIteratorTestDoubles.h"

#include "CNMatcher.h"
#include "CNMatcherTestDoubles.h"

class CNGuiLayerTest : public testing::Test {
protected:
    class FakeMatcher;
    typedef std::shared_ptr<FakeMatcher> FakeMatcherPtr;
    class FakeMatcher : public CNMatcher {
    public:
        static FakeMatcherPtr getNewInstance(CNViewPtr matchingView) {
            return FakeMatcherPtr(new FakeMatcher(matchingView));
        }
        virtual ~FakeMatcher() {}
    protected:
        FakeMatcher(CNViewPtr matchingView) : matchingView(matchingView) {}

    public:
        virtual bool matches(CNViewPtr view) override {
            return view == matchingView;
        }

    private:
        CNViewPtr matchingView;
    };

    virtual CNGuiLayerPtr makeCNGuiLayer() {
        return CNGuiLayer::getNewInstance();
    }

    virtual FakeMatcherPtr makeFakeMatcher(CNViewPtr matchingView) {
        return FakeMatcher::getNewInstance(matchingView);
    }
    virtual CNMatcherPtr make_NotMatching_Matcher() {
        CNMatcherStubPtr matcher = CNMatcherStub::getNewInstance();
        matcher->setIsMatching(false);
        return matcher;
    }

    virtual CNViewDummyPtr makeCNViewDummy() {
        return CNViewDummy::getNewInstance();
    }
    virtual CNViewSpyPtr makeCNViewSpy_WithDoneIterator() {
        CNViewSpyPtr viewSpy = CNViewSpy::getNewInstance();
        viewSpy->setIterator(makeDoneIterator());
        return viewSpy;
    }
    virtual CNFakeViewPtr makeCNFakeView() {
        return CNFakeView::getNewInstance();
    }
    virtual CNIteratorPtr makeDoneIterator() {
        CNIteratorStubPtr iteratorStub = CNIteratorStub::getNewInstance();
        iteratorStub->setIsDone(true);
        return iteratorStub;
    }

    virtual std::string getAddedView_ErrorMessage(std::string addedView, std::string addingView) {
        return addedView + " should be added to " + addingView + ", but it was not!";
    }
    virtual std::string getAddedNothing_ErrorMessage(std::string view) {
        return view + " should not have been adding another view, but it has!";
    }

    virtual void expect_View_WasAddedTo_View(CNViewPtr added, CNViewSpyPtr adding, std::string errorMessage) {
        CNViewPtr expected = added;
        CNViewPtr actual = adding->getAddedView();

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expect_View_AddedNothing(CNViewSpyPtr adding, std::string errorMessage) {
        CNViewPtr actual = adding->getAddedView();

        EXPECT_THAT(actual, testing::IsNull()) << errorMessage;
    }
};

class GuiLayer_With_FakeView_Loaded_to_TopLevel : public CNGuiLayerTest {
protected:
    virtual void SetUp() override {
        sut = makeCNGuiLayer();
        topLevelView = makeCNFakeView();

        sut->loadTopLevel(topLevelView);
    }

protected:
    CNGuiLayerPtr sut;
    CNFakeViewPtr topLevelView;
};


TEST_F(CNGuiLayerTest, LoadedTopLevelView__Load_View_MatchingTopLevelView__ShouldAdd_View_to_TopLevelView) {
    CNGuiLayerPtr sut = makeCNGuiLayer();
    CNViewSpyPtr topLevelView = makeCNViewSpy_WithDoneIterator();
    sut->loadTopLevel(topLevelView);

    CNViewPtr view = makeCNViewDummy();
    sut->load(view, makeFakeMatcher(topLevelView));

    std::string errorMessage = getAddedView_ErrorMessage("View", "TopLevelVew");
    expect_View_WasAddedTo_View(view, topLevelView, errorMessage);
}

TEST_F(CNGuiLayerTest, LoadedTopLevelView__Load_View_NotMatching__ShouldNotAdd_View_to_TopLevelView) {
    CNGuiLayerPtr sut = makeCNGuiLayer();
    CNViewSpyPtr topLevelView = makeCNViewSpy_WithDoneIterator();
    sut->loadTopLevel(topLevelView);

    CNViewPtr view = makeCNViewDummy();
    sut->load(view, make_NotMatching_Matcher());

    std::string errorMessage = getAddedNothing_ErrorMessage("TopLevelView");
    expect_View_AddedNothing(topLevelView, errorMessage);
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, View_Loaded_MatchingTopLevelView__Load_SubView_MatchingView__ShouldAdd_SubView_to_View) {
    CNViewSpyPtr view = makeCNViewSpy_WithDoneIterator();
    sut->load(view, makeFakeMatcher(topLevelView));

    CNViewDummyPtr subView = makeCNViewDummy();
    sut->load(subView, makeFakeMatcher(view));

    std::string errorMessage = getAddedView_ErrorMessage("SubView", "View");
    expect_View_WasAddedTo_View(subView, view, errorMessage);
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, View_Loaded_MatchingTopLevelView__Load_SubView_NotMatching__ShouldNotAdd_SubView_to_View) {
    CNViewSpyPtr view = makeCNViewSpy_WithDoneIterator();
    sut->load(view, makeFakeMatcher(topLevelView));

    CNViewDummyPtr subView = makeCNViewDummy();
    sut->load(subView, make_NotMatching_Matcher());

    std::string errorMessage = getAddedNothing_ErrorMessage("View");
    expect_View_AddedNothing(view, errorMessage);
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, View_and_SubView_Loaded_inALine__Load_SubSubView_MatchingSubView__ShouldAdd_SubSubView_to_SubView) {
    CNFakeViewPtr view = makeCNFakeView();
    sut->load(view, makeFakeMatcher(topLevelView));
    CNViewSpyPtr subView = makeCNViewSpy_WithDoneIterator();
    sut->load(subView, makeFakeMatcher(view));

    CNViewDummyPtr subSubView = makeCNViewDummy();
    sut->load(subSubView, makeFakeMatcher(subView));

    std::string errorMessage = getAddedView_ErrorMessage("SubSubView", "SubView");
    expect_View_WasAddedTo_View(subSubView, subView, errorMessage);
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, View_and_SubView_Loaded_inALine__Load_SubSubView_NotMatching__ShouldNotAdd_SubSubView_to_SubView) {
    CNFakeViewPtr view = makeCNFakeView();
    sut->load(view, makeFakeMatcher(topLevelView));
    CNViewSpyPtr subView = makeCNViewSpy_WithDoneIterator();
    sut->load(subView, makeFakeMatcher(view));

    CNViewDummyPtr subSubView = makeCNViewDummy();
    sut->load(subSubView, make_NotMatching_Matcher());

    std::string errorMessage = getAddedNothing_ErrorMessage("SubView");
    expect_View_AddedNothing(subView, errorMessage);
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, _2Views_Loaded_MatchingTopLevelView__Load_SubView_MatchingSecondView__ShouldAdd_SubView_to_SecondView) {
    CNFakeViewPtr firstView = makeCNFakeView();
    sut->load(firstView, makeFakeMatcher(topLevelView));
    CNViewSpyPtr secondView = makeCNViewSpy_WithDoneIterator();
    sut->load(secondView, makeFakeMatcher(topLevelView));

    CNViewDummyPtr subView = makeCNViewDummy();
    sut->load(subView, makeFakeMatcher(secondView));

    std::string errorMessage = getAddedView_ErrorMessage("SubView", "SecondView");
    expect_View_WasAddedTo_View(subView, secondView, errorMessage);
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, _2Views_Loaded_MatchingTopLevelView__Load_SubView_MatchingFirstView__ShouldAdd_SubView_to_FirstView) {
    CNViewSpyPtr firstView = makeCNViewSpy_WithDoneIterator();
    sut->load(firstView, makeFakeMatcher(topLevelView));
    CNFakeViewPtr secondView = makeCNFakeView();
    sut->load(secondView, makeFakeMatcher(topLevelView));

    CNViewDummyPtr subView = makeCNViewDummy();
    sut->load(subView, makeFakeMatcher(firstView));

    std::string errorMessage = getAddedView_ErrorMessage("SubView", "FirstView");
    expect_View_WasAddedTo_View(subView, firstView, errorMessage);
}

TEST_F(CNGuiLayerTest, _2TopLevelViews_Loaded__Load_View_MatchingFirstTopLevelView__ShouldAdd_View_to_FirstTopLevelView) {
    CNGuiLayerPtr sut = makeCNGuiLayer();
    CNViewSpyPtr firstTopLevelView = makeCNViewSpy_WithDoneIterator();
    CNViewDummyPtr secondTopLevelView = makeCNViewDummy();
    sut->loadTopLevel(firstTopLevelView);
    sut->loadTopLevel(secondTopLevelView);

    CNViewDummyPtr view = makeCNViewDummy();
    sut->load(view, makeFakeMatcher(firstTopLevelView));

    std::string errorMessage = getAddedView_ErrorMessage("View", "FirstTopLevelView");
    expect_View_WasAddedTo_View(view, firstTopLevelView, errorMessage);
}

TEST_F(CNGuiLayerTest, _2TopLevelViews_Loaded__Load_View_MatchingSecondTopLevelView__ShouldAdd_View_to_SecondTopLevelView) {
    CNGuiLayerPtr sut = makeCNGuiLayer();
    CNFakeViewPtr firstTopLevelView = makeCNFakeView();
    CNViewSpyPtr secondTopLevelView = makeCNViewSpy_WithDoneIterator();
    sut->loadTopLevel(firstTopLevelView);
    sut->loadTopLevel(secondTopLevelView);

    CNViewDummyPtr view = makeCNViewDummy();
    sut->load(view, makeFakeMatcher(secondTopLevelView));

    std::string errorMessage = getAddedView_ErrorMessage("View", "SecondTopLevelView");
    expect_View_WasAddedTo_View(view, secondTopLevelView, errorMessage);
}


TEST_F(CNGuiLayerTest, View_Loaded_MatchingTopLevelView__Load_TopLevelView__ShouldAdd_View_to_TopLevelView) {
    CNGuiLayerPtr sut = makeCNGuiLayer();
    CNViewSpyPtr topLevelView = makeCNViewSpy_WithDoneIterator();
    CNViewDummyPtr view = makeCNViewDummy();
    sut->load(view, makeFakeMatcher(topLevelView));

    sut->loadTopLevel(topLevelView);

    std::string errorMessage = getAddedView_ErrorMessage("View", "TopLevelView");
    expect_View_WasAddedTo_View(view, topLevelView, errorMessage);
}

