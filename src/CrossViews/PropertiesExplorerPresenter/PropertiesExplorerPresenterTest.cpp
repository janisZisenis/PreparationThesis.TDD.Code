#include <gmock/gmock.h>
#include "SolutionExplorerPresenter.h"
#include "SolutionExplorerViewTestDoubles.h"
#include "SolutionExplorerViewMock.h"
#include "SelectionModelTestDoubles.h"
#include <CrossNative/CNVisitor/CNVisitorTestDoubles.h>
#include <CrossNative/CNVisitable/CNVisitableTestDoubles.h>

class SolutionExplorerPresenterTest : public testing::Test {
protected:
    virtual SolutionExplorerPresenterPtr makeSolutionExplorerPresenter(SolutionExplorerViewPtr view, SelectionModelPtr selectionModel) {
        return SolutionExplorerPresenter::getNewInstance(view, selectionModel);
    }

    virtual SolutionExplorerViewSpyPtr makeSolutionExplorerViewSpy() {
        return SolutionExplorerViewSpy::getNewInstance();
    }
    virtual SolutionExplorerViewStubPtr makeSolutionExplorerViewStub() {
        return SolutionExplorerViewStub::getNewInstance();
    }
    virtual SolutionExplorerViewMockPtr makeSolutionExplorerViewMock() {
        return SolutionExplorerViewMock::getNewInstance();
    }

    virtual SelectionModelPtr makeSelectionModelDummy() {
        return SelectionModelDummy::getNewInstance();
    }
    virtual SelectionModelSpyPtr makeSelectionModelSpy() {
        return SelectionModelSpy::getNewInstance();
    }

    virtual CNVisitorPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }
    virtual CNVisitablePtr makeCNVisitableDummy() {
        return CNVisitableDummy::getNewInstance();
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

        std::string errorMessage = "SolutionExplorerView should have removed the index " + expected.toString()
                                   + ". Instead it has removed the index " + actual.toString() + "!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectSelectionModelReceivedIndex(SelectionModelSpyPtr selectionModel, const HierarchyIndex& index) {
        HierarchyIndex expected = index;
        HierarchyIndex actual = selectionModel->getSelectedIndex();

        std::string errorMessage = "The SelectionModel should have received the index " + expected.toString() + ", but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }

};

TEST_F(SolutionExplorerPresenterTest, FreshInstance__Accept__SolutionExplorerViewShouldHaveAcceptedTheVisitor) {
    SolutionExplorerViewSpyPtr view = makeSolutionExplorerViewSpy();
    SelectionModelPtr selectionModel = makeSelectionModelDummy();
    SolutionExplorerPresenterPtr sut = makeSolutionExplorerPresenter(view, selectionModel);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectSolutionExplorerViewHasAcceptedVisitor(view, visitor);
}

TEST_F(SolutionExplorerPresenterTest, FreshInstance__onRemove__ShouldRemoveIndexFromSolutionExplorerView) {
    SolutionExplorerViewSpyPtr view = makeSolutionExplorerViewSpy();
    SelectionModelPtr selectionModel = makeSelectionModelDummy();
    SolutionExplorerPresenterPtr sut = makeSolutionExplorerPresenter(view, selectionModel);

    sut->onRemove(HierarchyIndex({1,2,3}));

    expectedSolutionExplorerHasRemovedIndex(view, HierarchyIndex({1,2,3}));
}

TEST_F(SolutionExplorerPresenterTest, FreshInstance__onInserted__ShouldAddVisitableToSolutionExplorerAtParentIndexAtChildPosition) {
    SolutionExplorerViewMockPtr view = makeSolutionExplorerViewMock();
    SelectionModelPtr selectionModel = makeSelectionModelDummy();
    SolutionExplorerPresenterPtr sut = makeSolutionExplorerPresenter(view, selectionModel);


    CNVisitablePtr visitable = makeCNVisitableDummy();
    view->expectCalledInsertItem(visitable, HierarchyIndex({1,2,3}), 4);
    sut->onInsert(visitable, HierarchyIndex({1,2,3}), 4);

    view->verify();
}

TEST_F(SolutionExplorerPresenterTest, FreshInstance__onSelectionChanged__ShouldSetTheSelectedIndexToThSelectionModel) {
    SolutionExplorerViewStubPtr view = makeSolutionExplorerViewStub();
    view->setSelectedIndex(HierarchyIndex({1,2,3}));
    SelectionModelSpyPtr selectionModel = makeSelectionModelSpy();
    SolutionExplorerPresenterPtr sut = makeSolutionExplorerPresenter(view, selectionModel);

    sut->onSelectionChanged();

    expectSelectionModelReceivedIndex(selectionModel, HierarchyIndex({1,2,3}));
}