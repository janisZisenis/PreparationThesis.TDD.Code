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
    virtual void expectPropertiesExplorerDisplaysPropertiesFor(CNVisitablePtr visitable, PropertiesExplorerViewSpyPtr view) {
        CNVisitablePtr expected = visitable;
        CNVisitablePtr actual = view->getDisplayed();

        std::string errorMessage = "The PropertiesExplorerView should display the properties for the visitable, but it does not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectDisplaysEmptyProperties(PropertiesExplorerViewSpyPtr view) {
        bool actual = view->getDisplaysEmptyProperties();

        std::string errorMessage = "The PropertiesExplorerView should display empty properties, but it does not!";
        EXPECT_TRUE(actual) << errorMessage;
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

TEST_F(PropertiesExplorerPresenterTest, FreshInstance__UpdateSelectionModelHasSelection__ShouldRetrieveTheSelectedIndexFromHierarchicModelAccess) {
    PropertiesExplorerViewSpyPtr view = makePropertiesExplorerViewSpy();
    HierarchicModelAccessSpyPtr hierarchicModelAccess = makeHierarchicModelAccessSpy();
    SelectionModelStubPtr selectionModel = makeSelectionModelStub();
    PropertiesExplorerPresenterPtr sut = makePropertiesExplorerPresenter(view, hierarchicModelAccess, selectionModel);
    CNVisitablePtr visitable = makeCNVisitableDummy();
    hierarchicModelAccess->setRetrieved(visitable);
    selectionModel->setSelectedIndex(HierarchyIndex({1, 2, 3}));
    selectionModel->setHasSelection(true);

    sut->update();

    expectRetrievedIndexWas(HierarchyIndex({1, 2, 3}), hierarchicModelAccess);
}

TEST_F(PropertiesExplorerPresenterTest, FreshInstance__UpdateSelectionModelHasSelection__ShouldTriggerPropertiesExplorerViewToDisplayPropertiesForTheRetrieved) {
    PropertiesExplorerViewSpyPtr view = makePropertiesExplorerViewSpy();
    HierarchicModelAccessSpyPtr hierarchicModelAccess = makeHierarchicModelAccessSpy();
    SelectionModelStubPtr selectionModel = makeSelectionModelStub();
    PropertiesExplorerPresenterPtr sut = makePropertiesExplorerPresenter(view, hierarchicModelAccess, selectionModel);
    CNVisitablePtr visitable = makeCNVisitableDummy();
    hierarchicModelAccess->setRetrieved(visitable);
    selectionModel->setSelectedIndex(HierarchyIndex({1, 2, 3}));
    selectionModel->setHasSelection(true);

    sut->update();

    expectPropertiesExplorerDisplaysPropertiesFor(visitable, view);
}

TEST_F(PropertiesExplorerPresenterTest, FreshInstance__UpdateSelectionModelHasNoSelection__ShouldTriggerPropertiesExplorerViewToDisplayEmptyProperties) {
    PropertiesExplorerViewSpyPtr view = makePropertiesExplorerViewSpy();
    HierarchicModelAccessSpyPtr hierarchicModelAccess = makeHierarchicModelAccessSpy();
    SelectionModelStubPtr selectionModel = makeSelectionModelStub();
    PropertiesExplorerPresenterPtr sut = makePropertiesExplorerPresenter(view, hierarchicModelAccess, selectionModel);
    CNVisitablePtr visitable = makeCNVisitableDummy();
    hierarchicModelAccess->setRetrieved(visitable);
    selectionModel->setHasSelection(false);

    sut->update();

    expectDisplaysEmptyProperties(view);
}