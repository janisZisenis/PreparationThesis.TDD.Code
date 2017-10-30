#include <gmock/gmock.h>
#include "RemoveCommand.h"
#include "InsertingHierarchicModelTestDoubles.h"
#include <Hierarchies/CNComponent/CNComponentTestDoubles.h>

class RemoveCommandTest : public testing::Test {
protected:
    virtual RemoveCommandPtr
    makeRemoveCommand(InsertingHierarchicModelPtr model, CNHierarchyIndex index, CNComponentPtr component) {
        return RemoveCommand::getNewInstance(model, index, component);
    }

    virtual CNComponentPtr makeCNComponentDummy() {
        return CNComponentDummy::getNewInstance();
    }

    virtual InsertingHierarchicModelSpyPtr makeInsertingHierarchicModelSpy() {
        return InsertingHierarchicModelSpy::getNewInstance();
    }

    virtual void expectChildPositionWasRemovedAtIndex(InsertingHierarchicModelSpyPtr model, int childPos, CNHierarchyIndex index) {
        expectChildPositionWasRemoved(model, childPos);
        expectWasRemovedAtParentIndex(model, index);
    }
    virtual void expectWasRemovedAtParentIndex(InsertingHierarchicModelSpyPtr model, CNHierarchyIndex index) {
        CNHierarchyIndex expected = index;
        CNHierarchyIndex actual = model->getRemovedIndex();

        std::string errorMessage = "InsertingHierarchicModel should have removed at parent index " + expected.toString() + " , but it has not!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectChildPositionWasRemoved(InsertingHierarchicModelSpyPtr model, int childPos) {
        int expected = childPos;
        int actual = model->getRemovedChildPos();

        std::string errorMessage = "InsertingHierarchicModel should have removed the child position " + std::to_string(childPos) + " , but it has not!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }

    virtual void expectComponentWasInserted(InsertingHierarchicModelSpyPtr model, CNComponentPtr component) {
        CNComponentPtr expected = component;
        CNComponentPtr actual = model->getInserted();

        std::string errorMessage = "InsertingHIerarchicModel should have inserted the CNComponent, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectWasInsertedAtParentIndex(InsertingHierarchicModelSpyPtr model, CNHierarchyIndex index) {
        CNHierarchyIndex expected = index;
        CNHierarchyIndex actual = model->getInsertedIndex();

        std::string errorMessage = "InsertingHierarchicModel should have inserted at parent index " + expected.toString() + " , but it has not!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectChildPositionWasInserted(InsertingHierarchicModelSpyPtr model, int childPos) {
        int expected = childPos;
        int actual = model->getInsertedChildPos();

        std::string errorMessage = "InsertingHierarchicModel should have inserted the child position " + std::to_string(childPos) + " , but it has not!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(RemoveCommandTest, FreshInstance__Execute__ShouldRemoveTheComponentAtIndexToInsertingHierarchicModel) {
    CNComponentPtr component = makeCNComponentDummy();
    InsertingHierarchicModelSpyPtr model = InsertingHierarchicModelSpy::getNewInstance();
    RemoveCommandPtr sut = makeRemoveCommand(model, CNHierarchyIndex({0, 2}), component);

    sut->execute();

    expectChildPositionWasRemovedAtIndex(model, 2, CNHierarchyIndex({0}));
}

TEST_F(RemoveCommandTest, FreshInstance__Undo__ShouldInsertTheComponentAtParentIndexAndChildPostitionToInsertingHierarchicModel) {
    CNComponentPtr component = makeCNComponentDummy();
    InsertingHierarchicModelSpyPtr model = InsertingHierarchicModelSpy::getNewInstance();
    RemoveCommandPtr sut = makeRemoveCommand(model, CNHierarchyIndex({0, 2}), component);

    sut->undo();

    expectComponentWasInserted(model, component);
    expectWasInsertedAtParentIndex(model, CNHierarchyIndex({0}));
    expectChildPositionWasInserted(model, 2);
}