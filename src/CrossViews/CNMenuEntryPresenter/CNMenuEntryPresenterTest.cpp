#include <gmock/gmock.h>
#include "CNMenuEntryPresenter.h"
#include "CNMenuEntryViewTestDoubles.h"
#include <Base/CNTransActionAppearance/CNTransActionAppearanceTestDoubles.h>
#include <Hierarchies/CNVisitable/CNVisitableTestDoubles.h>
#include <Hierarchies/CNVisitor/CNVisitorTestDoubles.h>
#include <Base/CNTransAction/CNTransActionTestDoubles.h>

class CNMenuEntryPresenterTest : public testing::Test {
protected:
    virtual CNMenuEntryPresenterPtr makeMenuEntryPresenter(CNMenuEntryViewPtr view,
                                                           CNTransActionAppearancePtr appearance,
                                                           CNTransActionPtr action) {
        return MenuEntryPresenter::getNewInstance(view, appearance, action);
    }

    virtual CNMenuEntryViewSpyPtr makeMenuEntryViewSpy() {
        return CNMenuEntryViewSpy::getNewInstance();
    }

    virtual CNVisitorPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }

    virtual CNTransActionAppearancePtr makeCNTransActionAppearanceDummy() {
        return CNTransActionAppearanceDummy::getNewInstance();
    }
    virtual CNTransActionAppearanceStubPtr makeCNTransActionAppearanceStub() {
        return CNTransActionAppearanceStub::getNewInstance();
    }

    virtual CNTransActionPtr makeCNTransActionDummy() {
        return CNTransActionDummy::getNewInstance();
    }
    virtual CNTransActionSpyPtr makeCNTransActionSpy() {
        return CNTransActionSpy::getNewInstance();
    }

    virtual void expectTitleWasSetTo(std::string title, CNMenuEntryViewSpyPtr view) {
        std::string expected = title;
        std::string actual = view->getNewTitle();

        std::string errorMessage = "The MenuEntryViews title should be set to \"" + expected + "\" , but it was not!";
        EXPECT_THAT(actual, testing::StrEq(expected)) << errorMessage;
    }
    virtual void expectMenuEntryViewHasAcceptedVisitor(CNMenuEntryViewSpyPtr view, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitor;
        CNVisitorPtr actual = view->getAccepted();

        std::string errorMessage = "The CNMenuEntryView should have accepted the CNVisitor but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectCNTransActionWasExecuted(CNTransActionSpyPtr transAction) {
        bool actual = transAction->wasExecuted();

        std::string errorMessage = "CNTransAction should be executed, but it was not!";
        EXPECT_TRUE(actual);
    }

    virtual void expectWasChecked(CNMenuEntryViewSpyPtr view) {
        bool actual = view->wasChecked();

        std::string errorMessage = "CNMenuEntryView should be checked, but it was not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectWasUnchecked(CNMenuEntryViewSpyPtr view) {
        bool actual = view->wasUnchecked();

        std::string errorMessage = "CNMenuEntryView should be unchecked, but it was not!";
        EXPECT_TRUE(actual) << errorMessage;
    }

    virtual void expectWasEnabled(CNMenuEntryViewSpyPtr view) {
        bool actual = view->wasEnabled();

        std::string errorMessage = "CNMenuEntryView should be enabled, but it was not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectWasDisabled(CNMenuEntryViewSpyPtr view) {
        bool actual = view->wasDisabled();

        std::string errorMessage = "CNMenuEntryView should be disabled, but it was not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
};

TEST_F(CNMenuEntryPresenterTest, FreshInstance__Accept__ShouldPassTheVisitorToMenuEntryView) {
    CNTransActionPtr action = makeCNTransActionDummy();
    CNMenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CNTransActionAppearancePtr appearance = makeCNTransActionAppearanceDummy();
    CNMenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectMenuEntryViewHasAcceptedVisitor(view, visitor);
}


TEST_F(CNMenuEntryPresenterTest, FreshInstance__onTriggered__ShouldExecuteTransAction) {
    CNTransActionSpyPtr action = makeCNTransActionSpy();
    CNMenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CNTransActionAppearanceStubPtr appearance = makeCNTransActionAppearanceStub();
    CNMenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    sut->onTriggered();

    expectCNTransActionWasExecuted(action);
}


TEST_F(CNMenuEntryPresenterTest, OnConstruction_WithAppearanceStateON__ShouldCheckTheMenuEntry) {
    CNTransActionPtr action = makeCNTransActionDummy();
    CNMenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CNTransActionAppearanceStubPtr appearance = makeCNTransActionAppearanceStub();
    appearance->setState(ON);
    CNMenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    expectWasChecked(view);
}

TEST_F(CNMenuEntryPresenterTest, OnConstruction_WithNotAppearanceStateOFF__ShouldUncheckTheMenuEntry) {
    CNTransActionPtr action = makeCNTransActionDummy();
    CNMenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CNTransActionAppearanceStubPtr appearance = makeCNTransActionAppearanceStub();
    appearance->setState(OFF);
    CNMenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    expectWasUnchecked(view);
}

TEST_F(CNMenuEntryPresenterTest, FreshInstance_WithNotAppearanceStateOFF__UpdateWithAppearanceStateON__ShouldCheckTheMenuEntry) {
    CNTransActionPtr action = makeCNTransActionDummy();
    CNMenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CNTransActionAppearanceStubPtr appearance = makeCNTransActionAppearanceStub();
    appearance->setState(OFF);
    CNMenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    appearance->setState(ON);
    sut->update();

    expectWasChecked(view);
}

TEST_F(CNMenuEntryPresenterTest, OnConstruction_WithAccessibleAppearance__ShouldEnableTheMenuEntry) {
    CNTransActionPtr action = makeCNTransActionDummy();
    CNMenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CNTransActionAppearanceStubPtr appearance = makeCNTransActionAppearanceStub();
    appearance->setIsAccessible(true);
    CNMenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    expectWasEnabled(view);
}

TEST_F(CNMenuEntryPresenterTest, OnConstruction_WithNotAccessibleAppearance__ShouldDisableTheMenuEntry) {
    CNTransActionPtr action = makeCNTransActionDummy();
    CNMenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CNTransActionAppearanceStubPtr appearance = makeCNTransActionAppearanceStub();
    appearance->setIsAccessible(false);
    CNMenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    expectWasDisabled(view);
}

TEST_F(CNMenuEntryPresenterTest, FreshInstance_WithNotAccessibleAppearance__UpdateWithAccessibleAppearance__ShouldEnableTheMenuEntry) {
    CNTransActionPtr action = makeCNTransActionDummy();
    CNMenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CNTransActionAppearanceStubPtr appearance = makeCNTransActionAppearanceStub();
    appearance->setIsAccessible(false);
    CNMenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    appearance->setIsAccessible(true);
    sut->update();

    expectWasEnabled(view);
}

TEST_F(CNMenuEntryPresenterTest, OnConstruction_WithAppearanceWithTitle__ShouldSetTitleToMenuEntryView) {
    CNTransActionPtr action = makeCNTransActionDummy();
    CNMenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CNTransActionAppearanceStubPtr appearance = makeCNTransActionAppearanceStub();
    appearance->setTitle("Title");
    CNMenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    expectTitleWasSetTo("Title", view);
}

TEST_F(CNMenuEntryPresenterTest, FreshInstance_WithAppearanceWithTitle__UpdateWithAppearanceWithNewTitle__ShouldSetNewTitleToMenuEntryView) {
    CNTransActionPtr action = makeCNTransActionDummy();
    CNMenuEntryViewSpyPtr view = makeMenuEntryViewSpy();
    CNTransActionAppearanceStubPtr appearance = makeCNTransActionAppearanceStub();
    appearance->setTitle("Title");
    CNMenuEntryPresenterPtr sut = makeMenuEntryPresenter(view, appearance, action);

    appearance->setTitle("NewTitle");
    sut->update();

    expectTitleWasSetTo("NewTitle", view);
}
