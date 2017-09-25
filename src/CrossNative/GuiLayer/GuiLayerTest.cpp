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

    virtual void expect_View_WasAddedTo_View(CNViewPtr added, std::string addedName, CNViewSpyPtr adding, std::string addingName) {
        CNViewPtr expected = added;
        CNViewPtr actual = adding->getAddedView();

        std::string errorMessage = addedName + " should be added to " + addingName + ", but it was not!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expect_View_AddedNothing(CNViewSpyPtr adding, std::string addingName) {
        CNViewPtr actual = adding->getAddedView();

        std::string errorMessage = addingName + " should not have been adding another view, but it has!";

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

    expect_View_WasAddedTo_View(view, "View", topLevelView, "TopLevelView");
}

TEST_F(GuiLayerTest, LoadedTopLevelView__Load_View_NotMatching__ShouldNotAdd_View_to_TopLevelView) {
    CNGuiLayerPtr sut = makeCNGuiLayer();
    CNViewSpyPtr topLevelView = makeCNViewSpy();
    sut->loadTopLevel(topLevelView);

    CNViewPtr view = makeCNViewDummy();
    sut->load(view, make_NotMatching_Matcher());

    expect_View_AddedNothing(topLevelView, "TopLevelView");
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, View_Loaded_MatchingTopLevelView__Load_SubView_MatchingView__ShouldAdd_SubView_to_View) {
    CNViewSpyPtr view = makeCNViewSpy();
    sut->load(view, makeFakeMatcher(topLevelView));

    CNViewDummyPtr subView = makeCNViewDummy();
    sut->load(subView, makeFakeMatcher(view));

    expect_View_WasAddedTo_View(subView, "SubView", view, "View");
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, View_Loaded_MatchingTopLevelView__Load_SubView_NotMatching__ShouldNotAdd_SubView_to_View) {
    CNViewSpyPtr view = makeCNViewSpy();
    sut->load(view, makeFakeMatcher(topLevelView));

    CNViewDummyPtr subView = makeCNViewDummy();
    sut->load(subView, make_NotMatching_Matcher());

    expect_View_AddedNothing(view, "View");
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, View_and_SubView_Loaded_inALine__Load_SubSubView_MatchingSubView__ShouldAdd_SubSubView_to_SubView) {
    FakeViewPtr view = makeFakeView();
    sut->load(view, makeFakeMatcher(topLevelView));
    CNViewSpyPtr subView = makeCNViewSpy();
    sut->load(subView, makeFakeMatcher(view));

    CNViewDummyPtr subSubView = makeCNViewDummy();
    sut->load(subSubView, makeFakeMatcher(subView));

    expect_View_WasAddedTo_View(subSubView, "SubSubView", subView, "SubView");
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, View_and_SubView_Loaded_inALine__Load_SubSubView_NotMatching__ShouldNotAdd_SubSubView_to_SubView) {
    FakeViewPtr view = makeFakeView();
    sut->load(view, makeFakeMatcher(topLevelView));
    CNViewSpyPtr subView = makeCNViewSpy();
    sut->load(subView, makeFakeMatcher(view));

    CNViewDummyPtr subSubView = makeCNViewDummy();
    sut->load(subSubView, make_NotMatching_Matcher());

    expect_View_AddedNothing(subView, "SubView");
}

TEST_F(GuiLayer_With_FakeView_Loaded_to_TopLevel, _2Views_Loaded_MatchingTopLevelView__Load_SubView_MatchingSecondView__ShouldAdd_SubView_to_SecondView) {
    CNViewDummyPtr firstView = makeCNViewDummy();
    sut->load(firstView, makeFakeMatcher(topLevelView));
    CNViewSpyPtr secondView = makeCNViewSpy();
    sut->load(secondView, makeFakeMatcher(topLevelView));

    CNViewDummyPtr subView = makeCNViewDummy();
    sut->load(subView, makeFakeMatcher(secondView));

    expect_View_WasAddedTo_View(subView, "SubView", secondView, "SecondView");
}

TEST_F(GuiLayerTest, _2TopLevelViews_Loaded__Load_View_MatchingFirstTopLevelView__ShouldAdd_View_to_FirstTopLevelView) {
    CNGuiLayerPtr sut = makeCNGuiLayer();
    CNViewSpyPtr firstTopLevelView = makeCNViewSpy();
    CNViewDummyPtr secondTopLevelView = makeCNViewDummy();
    sut->loadTopLevel(firstTopLevelView);
    sut->loadTopLevel(secondTopLevelView);

    CNViewDummyPtr view = makeCNViewDummy();
    sut->load(view, makeFakeMatcher(firstTopLevelView));

    expect_View_WasAddedTo_View(view, "View", firstTopLevelView, "FirstTopLevelView");
}
