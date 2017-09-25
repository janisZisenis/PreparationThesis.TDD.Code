#include <gmock/gmock.h>
#include <string>

#include "CNGuiLayer.h"
#include "CNView.h"
#include "CNViewTestDoubles.h"
#include "CNMatcher.h"
#include "CNMatcherTestDoubles.h"

class GuiLayerTest : public testing::Test {
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
    virtual CNViewSpyPtr makeCNViewSpy() {
        return CNViewSpy::getNewInstance();
    }
    virtual CNViewDummyPtr makeCNViewDummy() {
        return CNViewDummy::getNewInstance();
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

class GuiLayer_With_FakeView_Loaded_to_TopLevel : public GuiLayerTest {
protected:
    class FakeView;
    typedef std::shared_ptr<FakeView> FakeViewPtr;
    class FakeView : public CNView {
    public:
        static FakeViewPtr getNewInstance() {
            return FakeViewPtr(new FakeView());
        }
        virtual ~FakeView() {}
    protected:
        FakeView() {}

    public:
        virtual void add(CNViewPtr view) override {
            children.push_back(view);
        }
        virtual CNViewPtr getChild(int position) override {
            return children[position];
        }
        virtual int getChildCount() override {
            return (int)children.size();
        };

    private:
        std::vector<CNViewPtr> children;
    };

protected:
    virtual void SetUp() override {
        sut = makeCNGuiLayer();
        topLevelView = makeFakeView();

        sut->loadTopLevel(topLevelView);
    }

    virtual void setupSUT() {

    }
protected:
    CNGuiLayerPtr sut;
    FakeViewPtr topLevelView;

protected:
    virtual FakeViewPtr makeFakeView() {
        return FakeView::getNewInstance();
    }
};


TEST_F(GuiLayerTest, LoadedTopLevelView__Load_View_MatchingTopLevelView__ShouldAdd_View_to_TopLevelView) {
    CNGuiLayerPtr sut = makeCNGuiLayer();
    CNViewSpyPtr topLevelView = makeCNViewSpy();
    sut->loadTopLevel(topLevelView);

    CNViewPtr view = makeCNViewDummy();
    sut->load(view, makeFakeMatcher(topLevelView));

    std::string errorMessage = getAddedView_ErrorMessage("View", "TopLevelVew");
    expect_View_WasAddedTo_View(view, topLevelView, errorMessage);
}

TEST_F(GuiLayerTest, LoadedTopLevelView__Load_View_NotMatching__ShouldNotAdd_View_to_TopLevelView) {
    CNGuiLayerPtr sut = makeCNGuiLayer();
    CNViewSpyPtr topLevelView = makeCNViewSpy();
    sut->loadTopLevel(topLevelView);

    CNViewPtr view = makeCNViewDummy();
    sut->load(view, make_NotMatching_Matcher());

    std::string errorMessage = getAddedNothing_ErrorMessage("TopLevelView");
    expect_View_AddedNothing(topLevelView, errorMessage);
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, View_Loaded_MatchingTopLevelView__Load_SubView_MatchingView__ShouldAdd_SubView_to_View) {
    CNViewSpyPtr view = makeCNViewSpy();
    sut->load(view, makeFakeMatcher(topLevelView));

    CNViewDummyPtr subView = makeCNViewDummy();
    sut->load(subView, makeFakeMatcher(view));

    std::string errorMessage = getAddedView_ErrorMessage("SubView", "View");
    expect_View_WasAddedTo_View(subView, view, errorMessage);
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, View_Loaded_MatchingTopLevelView__Load_SubView_NotMatching__ShouldNotAdd_SubView_to_View) {
    CNViewSpyPtr view = makeCNViewSpy();
    sut->load(view, makeFakeMatcher(topLevelView));

    CNViewDummyPtr subView = makeCNViewDummy();
    sut->load(subView, make_NotMatching_Matcher());

    std::string errorMessage = getAddedNothing_ErrorMessage("View");
    expect_View_AddedNothing(view, errorMessage);
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, View_and_SubView_Loaded_inALine__Load_SubSubView_MatchingSubView__ShouldAdd_SubSubView_to_SubView) {
    FakeViewPtr view = makeFakeView();
    sut->load(view, makeFakeMatcher(topLevelView));
    CNViewSpyPtr subView = makeCNViewSpy();
    sut->load(subView, makeFakeMatcher(view));

    CNViewDummyPtr subSubView = makeCNViewDummy();
    sut->load(subSubView, makeFakeMatcher(subView));

    std::string errorMessage = getAddedView_ErrorMessage("SubSubView", "SubView");
    expect_View_WasAddedTo_View(subSubView, subView, errorMessage);
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, View_and_SubView_Loaded_inALine__Load_SubSubView_NotMatching__ShouldNotAdd_SubSubView_to_SubView) {
    FakeViewPtr view = makeFakeView();
    sut->load(view, makeFakeMatcher(topLevelView));
    CNViewSpyPtr subView = makeCNViewSpy();
    sut->load(subView, makeFakeMatcher(view));

    CNViewDummyPtr subSubView = makeCNViewDummy();
    sut->load(subSubView, make_NotMatching_Matcher());

    std::string errorMessage = getAddedNothing_ErrorMessage("SubView");
    expect_View_AddedNothing(subView, errorMessage);
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, _2Views_Loaded_MatchingTopLevelView__Load_SubView_MatchingSecondView__ShouldAdd_SubView_to_SecondView) {
    CNViewDummyPtr firstView = makeCNViewDummy();
    sut->load(firstView, makeFakeMatcher(topLevelView));
    CNViewSpyPtr secondView = makeCNViewSpy();
    sut->load(secondView, makeFakeMatcher(topLevelView));

    CNViewDummyPtr subView = makeCNViewDummy();
    sut->load(subView, makeFakeMatcher(secondView));

    std::string errorMessage = getAddedView_ErrorMessage("SubView", "SecondView");
    expect_View_WasAddedTo_View(subView, secondView, errorMessage);
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, _2Views_Loaded_MatchingTopLevelView__Load_SubView_MatchingFirstView__ShouldAdd_SubView_to_FirstView) {
    CNViewSpyPtr firstView = makeCNViewSpy();
    sut->load(firstView, makeFakeMatcher(topLevelView));
    CNViewDummyPtr secondView = makeCNViewDummy();
    sut->load(secondView, makeFakeMatcher(topLevelView));

    CNViewDummyPtr subView = makeCNViewDummy();
    sut->load(subView, makeFakeMatcher(firstView));

    std::string errorMessage = getAddedView_ErrorMessage("SubView", "FirstView");
    expect_View_WasAddedTo_View(subView, firstView, errorMessage);
}

TEST_F(GuiLayerTest, _2TopLevelViews_Loaded__Load_View_MatchingFirstTopLevelView__ShouldAdd_View_to_FirstTopLevelView) {
    CNGuiLayerPtr sut = makeCNGuiLayer();
    CNViewSpyPtr firstTopLevelView = makeCNViewSpy();
    CNViewDummyPtr secondTopLevelView = makeCNViewDummy();
    sut->loadTopLevel(firstTopLevelView);
    sut->loadTopLevel(secondTopLevelView);

    CNViewDummyPtr view = makeCNViewDummy();
    sut->load(view, makeFakeMatcher(firstTopLevelView));

    std::string errorMessage = getAddedView_ErrorMessage("View", "FirstTopLevelView");
    expect_View_WasAddedTo_View(view, firstTopLevelView, errorMessage);
}

TEST_F(GuiLayerTest, _2TopLevelViews_Loaded__Load_View_MatchingSecondTopLevelView__ShouldAdd_View_to_SecondTopLevelView) {
    CNGuiLayerPtr sut = makeCNGuiLayer();
    CNViewDummyPtr firstTopLevelView = makeCNViewDummy();
    CNViewSpyPtr secondTopLevelView = makeCNViewSpy();
    sut->loadTopLevel(firstTopLevelView);
    sut->loadTopLevel(secondTopLevelView);

    CNViewDummyPtr view = makeCNViewDummy();
    sut->load(view, makeFakeMatcher(secondTopLevelView));

    std::string errorMessage = getAddedView_ErrorMessage("View", "SecondTopLevelView");
    expect_View_WasAddedTo_View(view, secondTopLevelView, errorMessage);
}
