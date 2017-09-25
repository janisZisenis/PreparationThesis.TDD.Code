#include <gmock/gmock.h>
#include "CNGuiLayer.h"
#include "CNView.h"
#include "CNViewTestDoubles.h"
#include "CNMatcher.h"
#include "CNMatcherTestDoubles.h"

class GuiLayerTest : public testing::Test {
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

    virtual CNGuiLayerPtr makeGuiLayer() {
        return CNGuiLayer::getNewInstance();
    }
    virtual FakeViewPtr makeFakeView() {
        return FakeView::getNewInstance();
    }
    virtual FakeMatcherPtr makeFakeMatcher(CNViewPtr matchingView) {
        return FakeMatcher::getNewInstance(matchingView);
    }
    virtual CNMatcherDummyPtr makeMatcherDummy() {
        return CNMatcherDummy::getNewInstance();
    }
    virtual CNMatcherStubPtr make_NotMatching_Matcher() {
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
};


TEST_F(GuiLayerTest, LoadedTopLevelView__Load_View_MatchingTopLevelView__ShouldAdd_View_to_TopLevelView) {
    CNGuiLayerPtr sut = makeGuiLayer();
    CNViewSpyPtr topLevelView = makeCNViewSpy();
    sut->loadTopLevel(topLevelView);

    CNViewDummyPtr view = makeCNViewDummy();
    FakeMatcherPtr subMatcher = makeFakeMatcher(topLevelView);
    sut->load(view, subMatcher);

    EXPECT_THAT(topLevelView->getAddedView(), testing::Eq(view)) << "The view should be added to TopLevelView, but it was not!";
}

TEST_F(GuiLayerTest, LoadedTopLevelView__Load_View_NotMatching__ShouldNotAdd_View_to_TopLevelView) {
    CNGuiLayerPtr sut = makeGuiLayer();
    CNViewSpyPtr topLevelView = makeCNViewSpy();
    sut->loadTopLevel(topLevelView);

    FakeViewPtr subView = makeFakeView();
    CNMatcherStubPtr subMatcher = make_NotMatching_Matcher();
    sut->load(subView, make_NotMatching_Matcher());

    EXPECT_THAT(topLevelView->getAddedView(), testing::IsNull()) << "The view should not be added to TopLevelView, but it was!";
}


TEST_F(GuiLayerTest, LoadedTopLevelView_and_View_MatchingTopLevelView__Load_SubView_MatchingView__ShouldAdd_SubView_to_View) {
    CNGuiLayerPtr sut = makeGuiLayer();
    FakeViewPtr topLevelView = makeFakeView();
    sut->loadTopLevel(topLevelView);
    CNViewSpyPtr view = makeCNViewSpy();
    sut->load(view, makeFakeMatcher(topLevelView));

    CNViewDummyPtr subView = makeCNViewDummy();
    FakeMatcherPtr subMatcher = makeFakeMatcher(view);
    sut->load(subView, subMatcher);

    EXPECT_THAT(view->getAddedView(), testing::Eq(subView)) << "The subView should be added to view, but it was not!";
}

TEST_F(GuiLayerTest, LoadedTopLevelView_and_View_MatchingTopLevelView__Load_SubView_NotMatching__ShouldNotAdd_SubView_to_View) {
    CNGuiLayerPtr sut = makeGuiLayer();
    FakeViewPtr topLevelView = makeFakeView();
    sut->loadTopLevel(topLevelView);
    CNViewSpyPtr view = makeCNViewSpy();
    sut->load(view, makeFakeMatcher(topLevelView));

    CNViewDummyPtr subView = makeCNViewDummy();
    CNMatcherDummyPtr subMatcher = make_NotMatching_Matcher();
    sut->load(subView, subMatcher);

    EXPECT_THAT(view->getAddedView(), testing::IsNull()) << "The subView should not be added to view, but it was!";
}

TEST_F(GuiLayerTest, LoadedTopLevelView_and_2Views_MatchingTopLevelView__Load_SubView_MatchingSecondView__ShouldAdd_SubView_to_SecondView) {
    CNGuiLayerPtr sut = makeGuiLayer();
    FakeViewPtr topLevelView = makeFakeView();
    sut->loadTopLevel(topLevelView);
    CNViewDummyPtr firstView = makeCNViewDummy();
    sut->load(firstView, makeFakeMatcher(topLevelView));
    CNViewSpyPtr secondView = makeCNViewSpy();
    sut->load(secondView, makeFakeMatcher(topLevelView));

    CNViewDummyPtr subView = makeCNViewDummy();
    FakeMatcherPtr subMatcher = makeFakeMatcher(secondView);
    sut->load(subView, subMatcher);

    EXPECT_THAT(secondView->getAddedView(), testing::Eq(subView)) << "The subView should be added to secondView, but it was not!";
}