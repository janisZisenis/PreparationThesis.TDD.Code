#include <gmock/gmock.h>
#include "SolutionExplorerPresenter.h"
#include "SolutionExplorerViewTestDoubles.h"
#include "SolutionExplorerViewMock.h"
#include "CrossViews/SelectionModel/SelectionModelTestDoubles.h"
#include "CrossViews/SelectionModel/FakeSelectionModel.h"
#include <CrossHierarchies/CNVisitor/CNVisitorTestDoubles.h>
#include <CrossHierarchies/CNVisitable/CNVisitableTestDoubles.h>

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
    virtual SelectionModelPtr makeFakeSelectionModel() {
        return FakeSelectionModel::getNewInstance();
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
    virtual void expectedSolutionExplorerHasRemovedIndex(SolutionExplorerViewSpyPtr view, const CNHierarchyIndex& index) {
        CNHierarchyIndex expected = index;
        CNHierarchyIndex actual = view->getRemoved();

        std::string errorMessage = "SolutionExplorerView should have removed the index " + expected.toString()
                                   + ". Instead it has removed the index " + actual.toString() + "!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectSelectionHasSelectedIndex(SelectionModelPtr selectionModel, const CNHierarchyIndex &index) {
        CNHierarchyIndex expected = index;
        CNHierarchyIndex actual = selectionModel->getSelectedIndex();

        std::string errorMessage = "The SelectionModel should have received the index " + expected.toString() + ", but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(SolutionExplorerPresenterTest, FreshInstance__Accept__ShouldPassTheVisitorToSolutionExplorerView) {
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

    sut->onRemove(CNHierarchyIndex({1,2,3}));

    expectedSolutionExplorerHasRemovedIndex(view, CNHierarchyIndex({1,2,3}));
}

TEST_F(SolutionExplorerPresenterTest, FreshInstance__onInserted__ShouldAddVisitableToSolutionExplorerAtParentIndexAtChildPosition) {
    SolutionExplorerViewMockPtr view = makeSolutionExplorerViewMock();
    SelectionModelPtr selectionModel = makeSelectionModelDummy();
    SolutionExplorerPresenterPtr sut = makeSolutionExplorerPresenter(view, selectionModel);


    CNVisitablePtr visitable = makeCNVisitableDummy();
    view->expectCalledInsertItem(visitable, CNHierarchyIndex({1,2,3}), 4);
    sut->onInsert(visitable, CNHierarchyIndex({1,2,3}), 4);

    view->verify();
}

TEST_F(SolutionExplorerPresenterTest, FreshInstance__onSelectionChanged__ShouldSetTheSelectedIndexToThSelectionModel) {
    SolutionExplorerViewStubPtr view = makeSolutionExplorerViewStub();
    view->setSelectedIndex(CNHierarchyIndex({1,2,3}));
    SelectionModelPtr selectionModel = makeFakeSelectionModel();
    SolutionExplorerPresenterPtr sut = makeSolutionExplorerPresenter(view, selectionModel);

    sut->onSelectionChanged();

    expectSelectionHasSelectedIndex(selectionModel, CNHierarchyIndex({1, 2, 3}));
}