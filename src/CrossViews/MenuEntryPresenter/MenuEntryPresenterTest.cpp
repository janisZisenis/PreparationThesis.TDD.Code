#include <gmock/gmock.h>
#include "MenuEntryPresenter.h"
#include "MenuEntryViewTestDoubles.h"
#include <CodeBase/CBTransActionAppearance/CBTransActionAppearanceTestDoubles.h>
#include <CrossNative/CNVisitable/CNVisitableTestDoubles.h>
#include <CrossNative/CNVisitor/CNVisitorTestDoubles.h>
#include <CodeBase/CBTransAction/CBTransActionMocks.h>

class MenuEntryPresenterTest : public testing::Test {
protected:
    virtual MenuEntryPresenterPtr makeMenuEntryPresenter(MenuEntryViewPtr actionView,
                                                       CBTransActionAppearancePtr appearance,
                                                       CBTransActionPtr action) {
        return MenuEntryPresenter::getNewInstance(actionView, appearance, action);
    }

    virtual MenuEntryViewSpyPtr makeMenuEntryViewSpy() {
        return MenuEntryViewSpy::getNewInstance();
    }

    virtual CNVisitorPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }

    virtual CBTransActionAppearancePtr makeCBTransActionAppearanceDummy() {
        return CBTransActionAppearanceDummy::getNewInstance();
    }
    virtual CBTransActionAppearanceStubPtr makeCBTransActionAppearanceStub() {
        return CBTransActionAppearanceStub::getNewInstance();
    }

    virtual CBTransActionPtr makeCBTransActionDummy() {
        return CBTransActionDummy::getNewInstance();
    }
    virtual CBTransActionSpyPtr makeCBTransActionSpy() {
        return CBTransActionSpy::getNewInstance();
    }

    virtual void expectAccessibilityWasSetToTrue(MenuEntryViewSpyPtr view) {
        bool actual = view->getNewAccessibility();

        std::string errorMessage = "The MenuEntryViews accessibility should be set to true, but it was not";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectStateWasSetToON(MenuEntryViewSpyPtr view) {
        CBActionStates actual = view->getNewState();

        std::string errorMessage = "The MenuEntryViews state should be set to ON, but it was not!";
        EXPECT_THAT(actual, testing::Eq(ON)) << errorMessage;
    }
    virtual void expectTitleWasSetTo(std::string title, MenuEntryViewSpyPtr view) {
        std::string expected = title;
        std::string actual = view->getNewTitle();

        std::string errorMessage = "The MenuEntryViews title should be set to \"" + expected + "\" , but it was not!";
        EXPECT_THAT(actual, testing::StrEq(expected)) << errorMessage;
    }
    virtual void expectMenuEntryViewHasAcceptedVisitor(MenuEntryViewSpyPtr view, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitor;
        CNVisitorPtr actual = view->getAccepted();

        std::string errorMessage = "The MenuEntryView should have accepted the CNVisitor but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectCBTransActionWasExecuted(CBTransActionSpyPtr transAction) {
        bool actual = transAction->wasExecuted();

        std::string errorMessage = "CBTransAction should be executed, but it was not!";
        EXPECT_TRUE(actual);
    }

    virtual void expectWasChecked(MenuEntryViewSpyPtr view) {
        bool actual = view->wasChecked();

        std::string errorMessage = "MenuEntryView should be checked, but it was not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
};

TEST_F(MenuEntryPresenterTest, FreshInstance__Accept__MenuEntryViewShouldHaveAcceptedTheVisitor) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearancePtr appearance = makeCBTransActionAppearanceDummy();
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectMenuEntryViewHasAcceptedVisitor(view, visitor);
}


TEST_F(MenuEntryPresenterTest, OnConstruction_WithAccessibleAppreance__ShouldSetMenuEntryAccessibilityToTrue) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setIsAccessible(true);
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    expectAccessibilityWasSetToTrue(view);
}

TEST_F(MenuEntryPresenterTest, FreshInstance__UpdateWithAccessibleAppearance__ShouldSetMenuEntrysAccessibilityToTrue) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    appearance->setIsAccessible(true);
    sut->update();

    expectAccessibilityWasSetToTrue(view);
}

TEST_F(MenuEntryPresenterTest, OnConstruction_WithAppearanceStateON__ShouldSetMenuEntryViewStateON) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setState(ON);
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    expectStateWasSetToON(view);
}

TEST_F(MenuEntryPresenterTest, FreshInstance__UpdateWithAppearanceStateON__ShouldSetMenuEntryViewStateON) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    appearance->setState(ON);
    sut->update();

    expectStateWasSetToON(view);
}

TEST_F(MenuEntryPresenterTest, OnConstruction_WithAppearanceTitle__ShouldSetMenuEntryViewTitle) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setTitle("ThisIsMyTitle");
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    expectTitleWasSetTo("ThisIsMyTitle", view);
}

TEST_F(MenuEntryPresenterTest, FreshInstance__UpdateWithAppearanceTitle__ShouldSetMenuEntryViewTitle) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    appearance->setTitle("ThisIsMyTitle");
    sut->update();

    expectTitleWasSetTo("ThisIsMyTitle", view);
}


TEST_F(MenuEntryPresenterTest, FreshInstance__onAction__ShouldExecuteTransAction) {
    CBTransActionSpyPtr action = makeCBTransActionSpy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    sut->onAction();

    expectCBTransActionWasExecuted(action);
}



TEST_F(MenuEntryPresenterTest, OnConstruction_WithAccessibleAppearance__ShouldCheckTheMenuEntry) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setIsAccessible(true);
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    sut->update();

    expectWasChecked(view);
}
