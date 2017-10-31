#include <gmock/gmock.h>

#include "CNAddCommand.h"
#include "CNComponentAdderTestDoubles.h"
#include <Hierarchies/CNComponent/CNComponentTestDoubles.h>

class CNAddCommandTest : public testing::Test {
protected:
    virtual CNAddCommandPtr makeCNAddCommand(CNComponentAdderPtr model,
                                             CNHierarchyIndex index,
                                             CNComponentPtr component) {
        return CNAddCommand::getNewInstance(model, index, component);
    }

    virtual CNComponentPtr makeCNComponentDummy() {
        return CNComponentDummy::getNewInstance();
    }

    virtual CNComponentAdderSpyPtr makeCNComponentAdderSpy() {
        return CNComponentAdderSpy::getNewInstance();
    }

    virtual void expectComponentWasAddedAtIndex(CNComponentAdderSpyPtr model, CNComponentPtr component, CNHierarchyIndex index) {
        expectComponentWasAdded(model, component);
        expectWasAddedAtIndex(model, index);
    }
    virtual void expectComponentWasAdded(CNComponentAdderSpyPtr model, CNComponentPtr component) {
        CNComponentPtr expected = component;
        CNComponentPtr actual = model->getAdded();

        std::string errorMessage = "CNComponentAdder should have added the CNComponent, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectWasAddedAtIndex(CNComponentAdderSpyPtr model, CNHierarchyIndex index) {
        CNHierarchyIndex expected = index;
        CNHierarchyIndex actual = model->getAddedIndex();

        std::string errorMessage = "CNComponentAdder should have added the CNComponent at index " + expected.toString() + " , but it has not!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }

    virtual void expectComponentWasRemovedAtIndex(CNComponentAdderSpyPtr model, CNComponentPtr component, CNHierarchyIndex index) {
        expectComponentWasRemoved(model, component);
        expectWasRemovedAtIndex(model, index);
    }
    virtual void expectComponentWasRemoved(CNComponentAdderSpyPtr model, CNComponentPtr component) {
        CNComponentPtr expected = component;
        CNComponentPtr actual = model->getRemoved();

        std::string errorMessage = "CNComponentAdder should have removed the CNComponent, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectWasRemovedAtIndex(CNComponentAdderSpyPtr model, CNHierarchyIndex index) {
        CNHierarchyIndex expected = index;
        CNHierarchyIndex actual = model->getRemovedIndex();

        std::string errorMessage = "CNComponentAdder should have removed the CNComponent at index " + expected.toString() + " , but it has not!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(CNAddCommandTest, FreshInstance__Execute__ShouldAddTheCNComponentAtIndexToCNComponentAdder) {
    CNComponentPtr component = makeCNComponentDummy();
    CNComponentAdderSpyPtr model = CNComponentAdderSpy::getNewInstance();
    CNAddCommandPtr sut = makeCNAddCommand(model, CNHierarchyIndex({0, 2}), component);

    sut->execute();

    expectComponentWasAddedAtIndex(model, component, CNHierarchyIndex({0, 2}));
}

TEST_F(CNAddCommandTest, FreshInstance__Undo__ShouldRemoveTheCNComponentAtIndexFromCNComponentAdder) {
    CNComponentPtr component = makeCNComponentDummy();
    CNComponentAdderSpyPtr model = CNComponentAdderSpy::getNewInstance();
    CNAddCommandPtr sut = makeCNAddCommand(model, CNHierarchyIndex({0, 2}), component);

    sut->undo();

    expectComponentWasRemovedAtIndex(model, component, CNHierarchyIndex({0, 2}));
}