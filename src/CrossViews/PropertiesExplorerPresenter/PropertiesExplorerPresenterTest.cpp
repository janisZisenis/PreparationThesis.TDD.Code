#include <gmock/gmock.h>
#include "PropertiesExplorerPresenter.h"
#include "PropertiesExplorerViewTestDoubles.h"
#include <CrossNative/CNVisitor/CNVisitorTestDoubles.h>
#include <CrossNative/CNVisitable/CNVisitableTestDoubles.h>

class PropertiesExplorerPresenterTest : public testing::Test {
protected:
    virtual PropertiesExplorerPresenterPtr makePropertiesExplorerPresenter(PropertiesExplorerViewPtr view) {
        return PropertiesExplorerPresenter::getNewInstance(view);
    }

    virtual PropertiesExplorerViewSpyPtr makePropertiesExplorerViewSpy() {
        return PropertiesExplorerViewSpy::getNewInstance();
    }

    virtual CNVisitorPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }

    virtual CNVisitablePtr makeCNVisitableDummy() {
        return CNVisitableDummy::getNewInstance();
    }

    virtual void expectPropertiesExplorerViewHasAcceptedVisitor(PropertiesExplorerViewSpyPtr view, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitor;
        CNVisitorPtr actual = view->getAccepted();

        std::string errorMessage = "The PropertiesExplorerView should have accepted the CNVisitor but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(PropertiesExplorerPresenterTest, FreshInstance__Accept__PropertiesExplorerViewShouldHaveAcceptedTheVisitor) {
    PropertiesExplorerViewSpyPtr view = makePropertiesExplorerViewSpy();
    PropertiesExplorerPresenterPtr sut = makePropertiesExplorerPresenter(view);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectPropertiesExplorerViewHasAcceptedVisitor(view, visitor);
}