#include <gmock/gmock.h>
#include "CNPropertiesExplorerPresenter.h"
#include "CNPropertiesExplorerViewTestDoubles.h"
#include "CrossViews/CNSelectionModel/CNSelectionModelTestDoubles.h"
#include "CrossViews/CNSelectionModel/CNFakeSelectionModel.h"
#include "CrossViews/CNHierarchicModel/API/CNHierarchicComponentAccessTestDoubles.h"
#include <Hierarchies/CNVisitor/CNVisitorTestDoubles.h>
#include <Hierarchies/CNComponent/CNComponentTestDoubles.h>

class CNPropertiesExplorerPresenterTest : public testing::Test {
protected:
    virtual CNPropertiesExplorerPresenterPtr makeCNPropertiesExplorerPresenter(CNPropertiesExplorerViewPtr view,
                                                                               CNHierarchicComponentAccessPtr modelAccess,
                                                                               CNSelectionModelPtr selectionModel) {
        return CNPropertiesExplorerPresenter::getNewInstance(view, modelAccess, selectionModel);
    }

    virtual CNPropertiesExplorerViewSpyPtr makePropertiesExplorerViewSpy() {
        return CNPropertiesExplorerViewSpy::getNewInstance();
    }
    virtual CNHierarchicComponentAccessSpyPtr makeCNHierarchicComponentAccessSpy() {
        return CNHierarchicComponentAccessSpy::getNewInstance();
    }
    virtual CNHierarchicComponentAccessPtr makeCNHierarchicComponentAccessDummy() {
        return CNHierarchicComponentAccessDummy::getNewInstance();
    }
    virtual CNSelectionModelPtr makeSelectionModelDummy() {
        return CNSelectionModelDummy::getNewInstance();
    }
    virtual CNSelectionModelPtr makeFakeSelectionModel() {
        return CNFakeSelectionModel::getNewInstance();
    }
    virtual CNVisitorPtr makeCNVisitorDummy() {
        return CNVisitorDummy::getNewInstance();
    }
    virtual CNComponentPtr makeCNComponentDummy() {
        return CNComponentDummy::getNewInstance();
    }

    virtual void expectPropertiesExplorerViewHasAcceptedVisitor(CNPropertiesExplorerViewSpyPtr view, CNVisitorPtr visitor) {
        CNVisitorPtr expected = visitor;
        CNVisitorPtr actual = view->getAccepted();

        std::string errorMessage = "The CNPropertiesExplorerView should have accepted the CNVisitor but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectRetrievedIndexWas(const CNHierarchyIndex& index, CNHierarchicComponentAccessSpyPtr modelAccess) {
        CNHierarchyIndex expected = index;
        CNHierarchyIndex actual = modelAccess->getRetrievedIndex();

        std::string errorMessage = "The retrieved index should be " + expected.toString() + ". Instead it is " + actual.toString() + "!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectPropertiesExplorerDisplaysPropertiesFor(CNVisitablePtr visitable, CNPropertiesExplorerViewSpyPtr view) {
        CNVisitablePtr expected = visitable;
        CNVisitablePtr actual = view->getDisplayed();

        std::string errorMessage = "The CNPropertiesExplorerView should display the properties for the visitable, but it does not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectDisplaysEmptyProperties(CNPropertiesExplorerViewSpyPtr view) {
        bool actual = view->getDisplaysEmptyProperties();

        std::string errorMessage = "The CNPropertiesExplorerView should display empty properties, but it does not!";
        EXPECT_TRUE(actual) << errorMessage;
    }
};

TEST_F(CNPropertiesExplorerPresenterTest, FreshInstance__Accept__ShouldPassTheVisitorToCNPropertiesExplorerView) {
    CNPropertiesExplorerViewSpyPtr view = makePropertiesExplorerViewSpy();
    CNHierarchicComponentAccessPtr hierarchicModelAccess = makeCNHierarchicComponentAccessDummy();
    CNSelectionModelPtr selectionModel = makeSelectionModelDummy();
    CNPropertiesExplorerPresenterPtr sut = makeCNPropertiesExplorerPresenter(view, hierarchicModelAccess,
                                                                             selectionModel);

    CNVisitorPtr visitor = makeCNVisitorDummy();
    sut->accept(visitor);

    expectPropertiesExplorerViewHasAcceptedVisitor(view, visitor);
}

TEST_F(CNPropertiesExplorerPresenterTest, FreshInstance__UpdateCNSelectionModelHasSelection__ShouldRetrieveTheSelectedIndexFromCNHierarchicComponentAccess) {
    CNPropertiesExplorerViewSpyPtr view = makePropertiesExplorerViewSpy();
    CNHierarchicComponentAccessSpyPtr hierarchicModelAccess = makeCNHierarchicComponentAccessSpy();
    CNComponentPtr component = makeCNComponentDummy();
    hierarchicModelAccess->setRetrieved(component);
    CNSelectionModelPtr selectionModel = makeFakeSelectionModel();
    selectionModel->setSelectedIndex(CNHierarchyIndex({1, 2, 3}));
    CNPropertiesExplorerPresenterPtr sut = makeCNPropertiesExplorerPresenter(view, hierarchicModelAccess,
                                                                             selectionModel);

    sut->update();

    expectRetrievedIndexWas(CNHierarchyIndex({1, 2, 3}), hierarchicModelAccess);
}

TEST_F(CNPropertiesExplorerPresenterTest, FreshInstance__UpdateCNSelectionModelHasSelection__ShouldTriggerCNPropertiesExplorerViewToDisplayPropertiesForTheRetrieved) {
    CNPropertiesExplorerViewSpyPtr view = makePropertiesExplorerViewSpy();
    CNHierarchicComponentAccessSpyPtr hierarchicModelAccess = makeCNHierarchicComponentAccessSpy();
    CNComponentPtr component = makeCNComponentDummy();
    hierarchicModelAccess->setRetrieved(component);
    CNSelectionModelPtr selectionModel = makeFakeSelectionModel();
    selectionModel->setSelectedIndex(CNHierarchyIndex({1, 2, 3}));
    CNPropertiesExplorerPresenterPtr sut = makeCNPropertiesExplorerPresenter(view, hierarchicModelAccess,
                                                                             selectionModel);

    sut->update();

    expectPropertiesExplorerDisplaysPropertiesFor(component, view);
}

TEST_F(CNPropertiesExplorerPresenterTest, FreshInstance__UpdateCNSelectionModelHasNoSelection__ShouldTriggerCNPropertiesExplorerViewToDisplayEmptyProperties) {
    CNPropertiesExplorerViewSpyPtr view = makePropertiesExplorerViewSpy();
    CNHierarchicComponentAccessSpyPtr hierarchicModelAccess = makeCNHierarchicComponentAccessSpy();
    CNComponentPtr component = makeCNComponentDummy();
    hierarchicModelAccess->setRetrieved(component);
    CNSelectionModelPtr selectionModel = makeFakeSelectionModel();
    selectionModel->setSelectedIndex(CNHierarchyIndex());
    CNPropertiesExplorerPresenterPtr sut = makeCNPropertiesExplorerPresenter(view, hierarchicModelAccess,
                                                                             selectionModel);

    sut->update();

    expectDisplaysEmptyProperties(view);
}