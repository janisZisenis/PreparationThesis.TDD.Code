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
};

TEST_F(QtActionPresenterTest, FreshInstance__UpdateWithAccessibleAppearance__ShouldSetQtActionsAccessibilityToTrue) {
    QtActionViewSpyPtr view = makeQtActionViewSpy();
    CBTransActionAppearanceStubPtr appearance = makeCBTransActionAppearanceStub();
    appearance->setIsAccessible(true);
    QtActionPresenterPtr sut = makeQtActionPresenter(view, appearance);

    sut->update();

    expectAccessibilityWasSetToTrue(view);
}