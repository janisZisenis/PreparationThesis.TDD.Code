#include <gmock/gmock.h>
#include "PropertiesExplorerPresenter.h"
#include "PropertiesExplorerViewTestDoubles.h"
#include "CrossViews/SelecionModel/SelectionModelTestDoubles.h"
#include "HierarchicModelAccessTestDoubles.h"
#include <CrossNative/CNVisitor/CNVisitorTestDoubles.h>
#include <CrossNative/CNVisitable/CNVisitableTestDoubles.h>

class PropertiesExplorerPresenterTest : public testing::Test {
protected:
    virtual PropertiesExplorerPresenterPtr makePropertiesExplorerPresenter(PropertiesExplorerViewPtr view,
                                                                           HierarchicModelAccessPtr modelAccess,
                                                                           SelectionModelPtr selectionModel) {
        return PropertiesExplorerPresenter::getNewInstance(view, modelAccess, selectionModel);
    }

    virtual PropertiesExplorerViewSpyPtr makePropertiesExplorerViewSpy() {
        return PropertiesExplorerViewSpy::getNewInstance();
    }
    virtual PropertiesExplorerViewPtr makePropertiesExplorerViewDummy() {
        return PropertiesExplorerViewDummy::getNewInstance();
    }
    virtual HierarchicModelAccessSpyPtr makeHierarchicModelAccessSpy() {
        return HierarchicModelAccessSpy::getNewInstance();
    }
    virtual HierarchicModelAccessPtr makeHierarchicModelAccessDummy() {
        return HierarchicModelAccessDummy::getNewInstance();
    }
    virtual SelectionModelPtr makeSelectionModelDummy() {
        return SelectionModelDummy::getNewInstance();
    }
    virtual SelectionModelStubPtr makeSelectionModelStub() {
        return SelectionModelStub::getNewInstance();
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
    virtual void expectRetrievedIndexWas(const HierarchyIndex& index, HierarchicModelAccessSpyPtr modelAccess) {
        HierarchyIndex expected = index;
        HierarchyIndex actual = modelAccess->getRetrievedIndex();

        std::string errorMessage = "The retrieved index should be " + expected.toString() + ". Instead it is " + actual.toString() + "!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(PropertiesExplorerPresenterTest, FreshInstance__Accept__ShouldPassTheVisitorToPropertiesExplorerView) {
    PropertiesExplorerViewSpyPtr view = makePropertiesExplorerViewSpy();
    HierarchicModelAccessPtr hierarchicModelAccess = makeHierarchicModelAccessDummy();
    SelectionModelPtr selectionModel = makeSelectionModelDummy();
    PropertiesExplorerPresenterPtr sut = makePropertiesExplorerPresenter(view, hierarchicModelAccess, selectionModel);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectPropertiesExplorerViewHasAcceptedVisitor(view, visitor);
}

TEST_F(PropertiesExplorerPresenterTest, FreshInstance__Update__ShouldRetrieveTheSelectedIndexFromHierarchicModelAccess) {
    PropertiesExplorerViewPtr view = makePropertiesExplorerViewDummy();
    HierarchicModelAccessSpyPtr hierarchicModelAccess = makeHierarchicModelAccessSpy();
    SelectionModelPtr selectionModel = makeSelectionModelStub();
    selectionModel->setSelectedIndex(HierarchyIndex({1, 2, 3}));
    PropertiesExplorerPresenterPtr sut = makePropertiesExplorerPresenter(view, hierarchicModelAccess, selectionModel);

    sut->update();

    expectRetrievedIndexWas(HierarchyIndex({1, 2, 3}), hierarchicModelAccess);
}