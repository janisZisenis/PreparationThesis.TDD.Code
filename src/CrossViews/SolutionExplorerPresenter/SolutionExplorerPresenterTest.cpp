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
    virtual void expectedSolutionExplorerHasRemovedIndex(SolutionExplorerViewSpyPtr view, const HierarchyIndex& index) {
        HierarchyIndex expected = index;
        HierarchyIndex actual = view->getRemoved();

        std::string errorMessage = "SolutionExplorerView should have removed the index " + toString(expected)
                                   + ". Instead it has removed the index " + toString(actual) + "!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }

    virtual std::string toString(const HierarchyIndex& index) {
        std::string s = "{";

        if(!index.isValid()) {
            s += "invalid";
        } else {
            for (int i = 0; i < index.depth(); i++) {
                s += std::to_string(index[i]);
                if(i != index.depth() - 1)
                    s+= "; ";
            }
        }

        s += "}";

        return s;
    }

};

TEST_F(SolutionExplorerPresenterTest, FreshInstance__Accept__SolutionExplorerViewShouldHaveAcceptedTheVisitor) {
    SolutionExplorerViewSpyPtr view = makeSolutionExplorerViewSpy();
    SolutionExplorerPresenterPtr sut = makeSolutionExplorerPresenter(view);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectSolutionExplorerViewHasAcceptedVisitor(view, visitor);
}

TEST_F(SolutionExplorerPresenterTest, FreshInstance__onRemove__ShouldRemoveIndexFromSolutionExplorerView) {
    SolutionExplorerViewSpyPtr view = makeSolutionExplorerViewSpy();
    SolutionExplorerPresenterPtr sut = makeSolutionExplorerPresenter(view);

    sut->onRemove(HierarchyIndex({1,2,3}));

    expectedSolutionExplorerHasRemovedIndex(view, HierarchyIndex({1,2,3}));
}