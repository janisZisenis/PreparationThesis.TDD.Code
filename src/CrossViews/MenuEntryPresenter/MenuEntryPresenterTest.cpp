#include <gmock/gmock.h>
#include "MenuEntryPresenter.h"
#include "MenuEntryViewTestDoubles.h"
#include <CodeBase/CBTransActionAppearance/CBTransActionAppearanceTestDoubles.h>
#include <CrossNative/CNVisitable/CNVisitableTestDoubles.h>
#include <CrossNative/CNVisitor/CNVisitorTestDoubles.h>
#include <CodeBase/CBTransAction/CBTransActionMocks.h>

class MenuEntryPresenterTest : public testing::Test {
protected:
    virtual MenuEntryPresenterPtr makeMenuEntryPresenter(MenuEntryViewPtr view,
                                                       CBTransActionAppearancePtr appearance,
                                                       CBTransActionPtr action) {
        return MenuEntryPresenter::getNewInstance(view, appearance, action);
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
    virtual void expectWasUnchecked(MenuEntryViewSpyPtr view) {
        bool actual = view->wasUnchecked();

        std::string errorMessage = "MenuEntryView should be unchecked, but it was not!";
        EXPECT_TRUE(actual) << errorMessage;
    }

    virtual void expectWasEnabled(MenuEntryViewSpyPtr view) {
        bool actual = view->wasEnabled();

        std::string errorMessage = "MenuEntryView should be enabled, but it was not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectWasDisabled(MenuEntryViewSpyPtr view) {
        bool actual = view->wasDisabled();

        std::string errorMessage = "MenuEntryView should be disabled, but it was not!";
        EXPECT_TRUE(actual) << errorMessage;
    }

};

TEST_F(MenuEntryPresenterTest, FreshInstance__Accept__ShouldPassTheVisitorToMenuEntryView) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearancePtr appearance = makeCBTransActionAppearanceDummy();
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectMenuEntryViewHasAcceptedVisitor(view, visitor);
}


TEST_F(MenuEntryPresenterTest, FreshInstance__onAction__ShouldExecuteTransAction) {
    CBTransActionSpyPtr action = makeCBTransActionSpy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    sut->onAction();

    expectCBTransActionWasExecuted(action);
}


TEST_F(MenuEntryPresenterTest, OnConstruction_WithAppearanceStateON__ShouldCheckTheMenuEntry) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setState(ON);
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    expectWasChecked(view);
}

TEST_F(MenuEntryPresenterTest, OnConstruction_WithNotAppearanceStateOFF__ShouldUncheckTheMenuEntry) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setState(OFF);
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    expectWasUnchecked(view);
}

TEST_F(MenuEntryPresenterTest, FreshInstance_WithNotAppearanceStateOFF__UpdateWithAppearanceStateON__ShouldCheckTheMenuEntry) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setState(OFF);
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    appearance->setState(ON);
    sut->update();

    expectWasChecked(view);
}

TEST_F(MenuEntryPresenterTest, OnConstruction_WithAccessibleAppearance__ShouldEnableTheMenuEntry) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setIsAccessible(true);
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    expectWasEnabled(view);
}

TEST_F(MenuEntryPresenterTest, OnConstruction_WithNotAccessibleAppearance__ShouldDisableTheMenuEntry) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setIsAccessible(false);
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    expectWasDisabled(view);
}

TEST_F(MenuEntryPresenterTest, FreshInstance_WithNotAccessibleAppearance__UpdateWithAccessibleAppearance__ShouldEnableTheMenuEntry) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setIsAccessible(false);
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    appearance->setIsAccessible(true);
    sut->update();

    expectWasEnabled(view);
}

TEST_F(MenuEntryPresenterTest, OnConstruction_WithAppearanceWithTitle__ShouldSetTitleToMenuEntryView) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setTitle("Title");
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    expectTitleWasSetTo("Title", view);
}

TEST_F(MenuEntryPresenterTest, FreshInstance_WithAppearanceWithTitle__UpdateWithAppearanceWithNewTitle__ShouldSetNewTitleToMenuEntryView) {
    CBTransActionPtr action = makeCBTransActionDummy();
    MenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setTitle("Title");
    MenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    appearance->setTitle("NewTitle");
    sut->update();

    expectTitleWasSetTo("NewTitle", view);
}
