#include <gmock/gmock.h>
#include "CNRemoveCommand.h"
#include "CNComponentInserterTestDoubles.h"
#include <Hierarchies/CNComponent/CNComponentTestDoubles.h>

class CNRemoveCommandTest : public testing::Test {
protected:
    virtual CNRemoveCommandPtr makeCNRemoveCommand(CNComponentInserterPtr model, CNHierarchyIndex index, CNComponentPtr component) {
        return CNRemoveCommand::getNewInstance(model, index, component);
    }

    virtual CNComponentPtr makeCNComponentDummy() {
        return CNComponentDummy::getNewInstance();
    }

    virtual CNComponentInserterSpyPtr makeCNComponentInserterSpy() {
        return CNComponentInserterSpy::getNewInstance();
    }

    virtual void expectChildPositionWasRemovedAtIndex(CNComponentInserterSpyPtr model, int childPos, CNHierarchyIndex index) {
        expectChildPositionWasRemoved(model, childPos);
        expectWasRemovedAtParentIndex(model, index);
    }
    virtual void expectWasRemovedAtParentIndex(CNComponentInserterSpyPtr model, CNHierarchyIndex index) {
        CNHierarchyIndex expected = index;
        CNHierarchyIndex actual = model->getRemovedIndex();

        std::string errorMessage = "CNComponentInserter should have removed at parent index " + expected.toString() + " , but it has not!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectChildPositionWasRemoved(CNComponentInserterSpyPtr model, int childPos) {
        int expected = childPos;
        int actual = model->getRemovedChildPos();

        std::string errorMessage = "CNComponentInserter should have removed the child position " + std::to_string(childPos) + " , but it has not!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }

    virtual void expectComponentWasInserted(CNComponentInserterSpyPtr model, CNComponentPtr component) {
        CNComponentPtr expected = component;
        CNComponentPtr actual = model->getInserted();

        std::string errorMessage = "InsertingHIerarchicModel should have inserted the CNComponent, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectWasInsertedAtParentIndex(CNComponentInserterSpyPtr model, CNHierarchyIndex index) {
        CNHierarchyIndex expected = index;
        CNHierarchyIndex actual = model->getInsertedIndex();

        std::string errorMessage = "CNComponentInserter should have inserted at parent index " + expected.toString() + " , but it has not!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectChildPositionWasInserted(CNComponentInserterSpyPtr model, int childPos) {
        int expected = childPos;
        int actual = model->getInsertedChildPos();

        std::string errorMessage = "CNComponentInserter should have inserted the child position " + std::to_string(childPos) + " , but it has not!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(CNRemoveCommandTest, FreshInstance__Execute__ShouldRemoveTheCNComponentAtIndexFromCNComponentInserter) {
    CNComponentPtr component = makeCNComponentDummy();
    CNComponentInserterSpyPtr model = CNComponentInserterSpy::getNewInstance();
    CNRemoveCommandPtr sut = makeCNRemoveCommand(model, CNHierarchyIndex({0, 2}), component);

    sut->execute();

    expectChildPositionWasRemovedAtIndex(model, 2, CNHierarchyIndex({0}));
}

TEST_F(CNRemoveCommandTest, FreshInstance__Undo__ShouldInsertTheCNComponentAtParentIndexAndChildPostitionToCNComponentInserter) {
    CNComponentPtr component = makeCNComponentDummy();
    CNComponentInserterSpyPtr model = CNComponentInserterSpy::getNewInstance();
    CNRemoveCommandPtr sut = makeCNRemoveCommand(model, CNHierarchyIndex({0, 2}), component);

    sut->undo();

    expectComponentWasInserted(model, component);
    expectWasInsertedAtParentIndex(model, CNHierarchyIndex({0}));
    expectChildPositionWasInserted(model, 2);
}