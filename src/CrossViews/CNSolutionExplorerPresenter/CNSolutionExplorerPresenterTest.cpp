#include <gmock/gmock.h>
#include "CNSolutionExplorerPresenter.h"
#include "CNSolutionExplorerViewTestDoubles.h"
#include "CNSolutionExplorerViewMock.h"
#include "CrossViews/CNSelectionModel/CNSelectionModelTestDoubles.h"
#include "CrossViews/CNSelectionModel/CNFakeSelectionModel.h"
#include <Hierarchies/CNVisitor/CNVisitorTestDoubles.h>
#include <Hierarchies/CNVisitable/CNVisitableTestDoubles.h>

class CNSolutionExplorerPresenterTest : public testing::Test {
protected:
    virtual CNSolutionExplorerPresenterPtr makeCNSolutionExplorerPresenter(CNSolutionExplorerViewPtr view,
                                                                           CNSelectionModelPtr selectionModel) {
        return CNSolutionExplorerPresenter::getNewInstance(view, selectionModel);
    }

    virtual CNSolutionExplorerViewSpyPtr makeCNSolutionExplorerViewSpy() {
        return CNSolutionExplorerViewSpy::getNewInstance();
    }
    virtual CNSolutionExplorerViewStubPtr makeCNSolutionExplorerViewStub() {
        return CNSolutionExplorerViewStub::getNewInstance();
    }
    virtual CNSolutionExplorerViewMockPtr makeCNSolutionExplorerViewMock() {
        return CNSolutionExplorerViewMock::getNewInstance();
    }

    virtual CNSelectionModelPtr makeCNSelectionModelDummy() {
        return CNSelectionModelDummy::getNewInstance();
    }
    virtual CNSelectionModelPtr makeCNFakeSelectionModel() {
        return CNFakeSelectionModel::getNewInstance();
    }

    virtual CNVisitorPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }
    virtual CNVisitablePtr makeCNVisitableDummy() {
        return CNVisitableDummy::getNewInstance();
    }

    virtual void expectSolutionExplorerViewHasAcceptedVisitor(CNSolutionExplorerViewSpyPtr view, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitor;
        CNVisitorPtr actual = view->getAccepted();

        std::string errorMessage = "The CNSolutionExplorerView should have accepted the CNVisitor but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectedSolutionExplorerHasRemovedIndex(CNSolutionExplorerViewSpyPtr view, const CNHierarchyIndex& index) {
        CNHierarchyIndex expected = index;
        CNHierarchyIndex actual = view->getRemoved();

        std::string errorMessage = "CNSolutionExplorerView should have removed the index " + expected.toString()
                                   + ". Instead it has removed the index " + actual.toString() + "!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectSelectionHasSelectedIndex(CNSelectionModelPtr selectionModel, const CNHierarchyIndex &index) {
        CNHierarchyIndex expected = index;
        CNHierarchyIndex actual = selectionModel->getSelectedIndex();

        std::string errorMessage = "The CNSelectionModel should have received the index " + expected.toString() + ", but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(CNSolutionExplorerPresenterTest, FreshInstance__Accept__ShouldPassTheCNVisitorToCNSolutionExplorerView) {
    CNSolutionExplorerViewSpyPtr view = makeCNSolutionExplorerViewSpy();
    CNSelectionModelPtr selectionModel = makeCNSelectionModelDummy();
    CNSolutionExplorerPresenterPtr sut = makeCNSolutionExplorerPresenter(view, selectionModel);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectSolutionExplorerViewHasAcceptedVisitor(view, visitor);
}

TEST_F(CNSolutionExplorerPresenterTest, FreshInstance__onRemove__ShouldRemoveIndexFromCNSolutionExplorerView) {
    CNSolutionExplorerViewSpyPtr view = makeCNSolutionExplorerViewSpy();
    CNSelectionModelPtr selectionModel = makeCNSelectionModelDummy();
    CNSolutionExplorerPresenterPtr sut = makeCNSolutionExplorerPresenter(view, selectionModel);

    sut->onRemove(CNHierarchyIndex({1,2,3}));

    expectedSolutionExplorerHasRemovedIndex(view, CNHierarchyIndex({1,2,3}));
}

TEST_F(CNSolutionExplorerPresenterTest, FreshInstance__onInserted__ShouldAddCNVisitableToCNSolutionExplorerAtParentIndexAtChildPosition) {
    CNSolutionExplorerViewMockPtr view = makeCNSolutionExplorerViewMock();
    CNSelectionModelPtr selectionModel = makeCNSelectionModelDummy();
    CNSolutionExplorerPresenterPtr sut = makeCNSolutionExplorerPresenter(view, selectionModel);


    CNVisitablePtr visitable = makeCNVisitableDummy();
    view->expectCalledInsertItem(visitable, CNHierarchyIndex({1,2,3}), 4);
    sut->onInsert(visitable, CNHierarchyIndex({1,2,3}), 4);

    view->verify();
}

TEST_F(CNSolutionExplorerPresenterTest, FreshInstance__onSelectionChanged__ShouldSetTheSelectedIndexToThCNSelectionModel) {
    CNSolutionExplorerViewStubPtr view = makeCNSolutionExplorerViewStub();
    view->setSelectedIndex(CNHierarchyIndex({1,2,3}));
    CNSelectionModelPtr selectionModel = makeCNFakeSelectionModel();
    CNSolutionExplorerPresenterPtr sut = makeCNSolutionExplorerPresenter(view, selectionModel);

    sut->onSelectionChanged();

    expectSelectionHasSelectedIndex(selectionModel, CNHierarchyIndex({1, 2, 3}));
}