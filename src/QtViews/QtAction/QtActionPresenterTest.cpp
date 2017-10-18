#include <gmock/gmock.h>
#include "QtActionPresenter.h"
#include "QtActionViewTestDoubles.h"
#include <CodeBase/CBTransActionAppearance/CBTransActionAppearanceTestDoubles.h>

class QtActionPresenterTest : public testing::Test {
protected:
    virtual QtActionPresenterPtr makeQtActionPresenter(QtActionViewPtr actionView, CBTransActionAppearancePtr appearance) {
        return QtActionPresenter::getNewInstance(actionView, appearance);
    }

    virtual QtActionViewPtr makeQtActionViewDummy() {
        return QtActionViewDummy::getNewInstance();
    }

    virtual QtActionViewSpyPtr makeQtActionViewSpy() {
        return QtActionViewSpy::getNewInstance();
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
    virtual void expectTitleWasSetTo(std::string expected, QtActionViewSpyPtr view) {
        std::string actual = view->getNewTitle();

        std::string errorMessage = "The QtActionViews title should be set to \"" + expected + "\" , but it was not!";
        EXPECT_THAT(actual, testing::StrEq(expected)) << errorMessage;
    }

};

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