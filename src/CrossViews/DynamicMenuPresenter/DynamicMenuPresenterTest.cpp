#include <gmock/gmock.h>
#include "DynamicMenuPresenter.h"
#include "MenuViewTestDoubles.h"
#include <CrossNative/CNComposer/CNComposerTestDoubles.h>
#include <CrossNative/CNVisitor/CNVisitorTestDoubles.h>

class DynamicMenuPresenterTest : public testing::Test {
protected:
    virtual DynamicMenuPresenterPtr makeDynamicMenuPresenter(MenuViewPtr view, CNComposerPtr composer) {
        return DynamicMenuPresenter::getNewInstance(view, composer);
    }
    virtual MenuViewSpyPtr makeMenuViewSpy() {
        return MenuViewSpy::getNewInstance();
    }
    virtual CNVisitorPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }
    virtual CNComposerSpyPtr makeCNComposerSpy() {
        return CNComposerSpy::getNewInstance();
    }

    virtual void expectMenuViewWasCleared(MenuViewSpyPtr view) {
        bool actual = view->wasCleared();

        std::string errorMessage = "DynamicMenuPresenter should have cleared the MenuView, but it has not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
};

TEST_F(DynamicMenuPresenterTest, FreshInstance__Update__ShouldClearTheMenuView) {
    MenuViewSpyPtr view = makeMenuViewSpy();
    CNComposerPtr composer = makeCNComposerSpy();
    DynamicMenuPresenterPtr sut = makeDynamicMenuPresenter(view, composer);

    sut->update();

    expectMenuViewWasCleared(view);
}

