#include <gmock/gmock.h>
#include "CNGuiLayer.h"
#include "CNView.h"
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
        virtual void add(CNViewPtr view) {
            children.push_back(view);
        }

        virtual int getChildCount() {
            return (int)children.size();
        }
        virtual CNViewPtr getChild(int position) {
            return children[position];
        }

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
    virtual CNMatcherStubPtr make_NotMatching_Matcher() {
        CNMatcherStubPtr matcher = CNMatcherStub::getNewInstance();
        matcher->setIsMatching(false);
        return matcher;
    }
};


TEST_F(GuiLayerTest, LoadedTopLevelView__Load_SubView_MatchingTopLevelView__ShouldAdd_SubView_to_TopLevelView) {
    CNGuiLayerPtr sut = makeGuiLayer();
    FakeViewPtr topLevelView = makeFakeView();
    sut->loadTopLevel(topLevelView);

    FakeViewPtr subView = makeFakeView();
    FakeMatcherPtr subMatcher = makeFakeMatcher(topLevelView);
    sut->load(subView, subMatcher);

    int expectedChildCount = 1;
    ASSERT_THAT(topLevelView->getChildCount(), testing::Eq(expectedChildCount)) << "The ToplevelView's ChildCount should be " + std::to_string(expectedChildCount) + ". Instead it is " + std::to_string(topLevelView->getChildCount());
    EXPECT_THAT(topLevelView->getChild(0), testing::Eq(subView)) << "The view was not registered as child or at least at a wrong position!";
}

TEST_F(GuiLayerTest, LoadedTopLevelView__Load_SubViewNotMatchingTopLevelView__ShouldNotAdd_SubView_to_TopLevelView) {
    CNGuiLayerPtr sut = makeGuiLayer();
    FakeViewPtr topLevelView = makeFakeView();
    sut->loadTopLevel(topLevelView);

    FakeViewPtr subView = makeFakeView();
    CNMatcherStubPtr subMatcher = make_NotMatching_Matcher();
    sut->load(subView, subMatcher);

    int expectedChildCount = 0;
    ASSERT_THAT(topLevelView->getChildCount(), testing::Eq(expectedChildCount)) << "The ToplevelView's ChildCount should be " + std::to_string(expectedChildCount) + ". Instead it is " + std::to_string(topLevelView->getChildCount());
}


//TEST_F(GuiLayerTest, LoadedTopLevelView_and_SubView__Load_SubSubView_Matching_SubView__ShouldAdd_SubSubView_to_SubView) {
//    CNGuiLayerPtr sut = makeGuiLayer();
//    FakeViewPtr topLevelView = makeFakeView();
//    sut->loadTopLevel(topLevelView);
//    FakeViewPtr subView = makeFakeView();
//    FakeMatcherPtr subMatcher = makeFakeMatcher(topLevelView);
//    sut->load(subView, subMatcher);
//
//    FakeViewPtr subSubView = makeFakeView();
//    FakeMatcherPtr subsubMatcher = makeFakeMatcher(subView);
//
//    int expectedChildCount = 1;
//    ASSERT_THAT(subView->getChildCount(), testing::Eq(1)) << "The SubView's ChildCount should be " + std::to_string(expectedChildCount) + ". Instead it is " + std::to_string(subView->getChildCount());
//    EXPECT_THAT(subView->getChild(0), testing::Eq(subSubView)) << "The view was not registered as child or at least at a wrong position!";
//}