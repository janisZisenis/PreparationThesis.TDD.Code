#include <gmock/gmock.h>
#include "SolutionExplorerPresenter.h"
#include "SolutionExplorerViewTestDoubles.h"
#include <CrossNative/CNVisitor/CNVisitorTestDoubles.h>

class SolutionExplorerPresenterTest : public testing::Test {
protected:
    virtual SolutionExplorerPresenterPtr makeSolutionExplorerPresenter(SolutionExplorerViewPtr view) {
        return SolutionExplorerPresenter::getNewInstance(view);
    }

    virtual SolutionExplorerViewSpyPtr makeSolutionExplorerViewSpy() {
        return SolutionExplorerViewSpy::getNewInstance();
    }

    virtual CNVisitorPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }

    virtual void expectSolutionExplorerViewHasAcceptedVisitor(SolutionExplorerViewSpyPtr view, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitor;
        CNVisitorPtr actual = view->getAccepted();

        std::string errorMessage = "The SolutionExplorerView should have accepted the CNVisitor but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(SolutionExplorerPresenterTest, FreshInstance__Accept__SolutionExplorerViewShouldHaveAcceptedTheVisitor) {
    SolutionExplorerViewSpyPtr view = makeSolutionExplorerViewSpy();
    SolutionExplorerPresenterPtr sut = makeSolutionExplorerPresenter(view);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectSolutionExplorerViewHasAcceptedVisitor(view, visitor);
}