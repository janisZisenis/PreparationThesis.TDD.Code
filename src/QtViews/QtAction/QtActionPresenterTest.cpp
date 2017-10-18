#include <gmock/gmock.h>
#include "QtActionPresenter.h"
#include "QtActionViewTestDoubles.h"
#include <CodeBase/CBTransActionAppearance/CBTransActionAppearanceTestDoubles.h>
#include <CrossNative/CNVisitable/CNVisitableTestDoubles.h>
#include <CrossNative/CNVisitor/CNVisitorTestDoubles.h>

class QtActionPresenterTest : public testing::Test {
protected:
    virtual QtActionPresenterPtr makeQtActionPresenter(QtActionViewPtr actionView, CBTransActionAppearancePtr appearance) {
        return QtActionPresenter::getNewInstance(actionView, appearance);
    }

    virtual QtActionViewSpyPtr makeQtActionViewSpy() {
        return QtActionViewSpy::getNewInstance();
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

    virtual void expectAccessibilityWasSetToTrue(QtActionViewSpyPtr view) {
        bool actual = view->getNewAccessibility();

        std::string errorMessage = "The QtActionViews accessibility should be set to true, but it was not";
        EXPECT_TRUE(actual) << errorMessage;
    }
    virtual void expectStateWasSetToON(QtActionViewSpyPtr view) {
        CBActionStates actual = view->getNewState();

        std::string errorMessage = "The QtActionViews state should be set to ON, but it was not!";
        EXPECT_THAT(actual, testing::Eq(ON)) << errorMessage;
    }
    virtual void expectTitleWasSetTo(std::string title, QtActionViewSpyPtr view) {
        std::string expected = title;
        std::string actual = view->getNewTitle();

        std::string errorMessage = "The QtActionViews title should be set to \"" + expected + "\" , but it was not!";
        EXPECT_THAT(actual, testing::StrEq(expected)) << errorMessage;
    }
    virtual void expectQtActionViewHasAcceptedVisitor(QtActionViewSpyPtr view, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitor;
        CNVisitorPtr actual = view->getAccepted();

        std::string errorMessage = "The QtActionView should have accepted the CNVisitor but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }

};

TEST_F(QtActionPresenterTest, FreshInstance__Accept__QtActionViewShouldHaveAcceptedTheVisitor) {
    QtActionViewSpyPtr view = makeQtActionViewSpy();
    CBTransActionAppearancePtr appearance = makeCBTransActionAppearanceDummy();
    QtActionPresenterPtr sut = makeQtActionPresenter(view, appearance);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectQtActionViewHasAcceptedVisitor(view, visitor);
}

TEST_F(QtActionPresenterTest, FreshInstance__UpdateWithAccessibleAppearance__ShouldSetQtActionsAccessibilityToTrue) {
    QtActionViewSpyPtr view = makeQtActionViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setIsAccessible(true);
    QtActionPresenterPtr sut = makeQtActionPresenter(view, appearance);

    sut->update();

    expectAccessibilityWasSetToTrue(view);
}

TEST_F(QtActionPresenterTest, FreshInstance__UpdateWithAppearanceStateON__ShouldSetQtActionViewStateON) {
    QtActionViewSpyPtr view = makeQtActionViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setState(ON);
    QtActionPresenterPtr sut = makeQtActionPresenter(view, appearance);

    sut->update();

    expectStateWasSetToON(view);
}

TEST_F(QtActionPresenterTest, FreshInstance__UpdateWithAppearanceTitle__ShouldSetQtActionViewTitle) {
    QtActionViewSpyPtr view = makeQtActionViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setTitle("ThisIsMyTitle");
    QtActionPresenterPtr sut = makeQtActionPresenter(view, appearance);

    sut->update();

    expectTitleWasSetTo("ThisIsMyTitle", view);
}