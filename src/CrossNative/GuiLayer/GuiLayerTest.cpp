#include <gmock/gmock.h>
#include "CNGuiLayer.h"
#include "CNView.h"
#include "CNMatcher.h"

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
};


TEST_F(GuiLayerTest, Loaded_TopLevelView__LoadView_MatchingTopLevelView__ShouldAdd_View_to_TopLevelView) {
    CNGuiLayerPtr sut = makeGuiLayer();
    FakeViewPtr topLevelView = makeFakeView();
    sut->loadTopLevel(topLevelView);

    FakeViewPtr view = makeFakeView();
    FakeMatcherPtr matcher = makeFakeMatcher(topLevelView);
    sut->load(view, matcher);

    int expectedChildCount = 1;
    ASSERT_THAT(topLevelView->getChildCount(), testing::Eq(1)) << "The ToplevelView's ChildCount should be " + std::to_string(expectedChildCount) + ". Instead it is " + std::to_string(topLevelView->getChildCount());
    EXPECT_THAT(topLevelView->getChild(0), testing::Eq(view)) << "The view was not registered as child or at least at a wrong position!";
}