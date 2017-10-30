#include <gmock/gmock.h>

#include "AddCommand.h"
#include "AddingHierarchicModelTestDoubles.h"
#include <Hierarchies/CNComponent/CNComponentTestDoubles.h>

class AddCommandTest : public testing::Test {
protected:
    virtual AddCommandPtr makeAddCommand(AddingHierarchicModelPtr model,
                                         CNHierarchyIndex index,
                                         CNComponentPtr component) {
        return AddCommand::getNewInstance(model, index, component);
    }

    virtual CNComponentPtr makeCNComponentDummy() {
        return CNComponentDummy::getNewInstance();
    }

    virtual AddingHierarchicModelSpyPtr makeAddingHierarchicModelSpy() {
        return AddingHierarchicModelSpy::getNewInstance();
    }

    virtual void expectComponentWasAddedAtIndex(AddingHierarchicModelSpyPtr model, CNComponentPtr component, CNHierarchyIndex index) {
        expectComponentWasAdded(model, component);
        expectWasAddedAtIndex(model, index);
    }
    virtual void expectComponentWasAdded(AddingHierarchicModelSpyPtr model, CNComponentPtr component) {
        CNComponentPtr expected = component;
        CNComponentPtr actual = model->getAdded();

        std::string errorMessage = "AddingHierarchicModel should have added the CNComponent, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectWasAddedAtIndex(AddingHierarchicModelSpyPtr model, CNHierarchyIndex index) {
        CNHierarchyIndex expected = index;
        CNHierarchyIndex actual = model->getAddedIndex();

        std::string errorMessage = "AddingHierarchicModel should have added the CNComponent at index " + expected.toString() + " , but it has not!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }

    virtual void expectComponentWasRemovedAtIndex(AddingHierarchicModelSpyPtr model, CNComponentPtr component, CNHierarchyIndex index) {
        expectComponentWasRemoved(model, component);
        expectWasRemovedAtIndex(model, index);
    }
    virtual void expectComponentWasRemoved(AddingHierarchicModelSpyPtr model, CNComponentPtr component) {
        CNComponentPtr expected = component;
        CNComponentPtr actual = model->getRemoved();

        std::string errorMessage = "AddingHierarchicModel should have removed the CNComponent, but it has not!";
        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
    virtual void expectWasRemovedAtIndex(AddingHierarchicModelSpyPtr model, CNHierarchyIndex index) {
        CNHierarchyIndex expected = index;
        CNHierarchyIndex actual = model->getRemovedIndex();

        std::string errorMessage = "AddingHierarchicModel should have removed the CNComponent at index " + expected.toString() + " , but it has not!";

        EXPECT_THAT(actual, testing::Eq(expected)) << errorMessage;
    }
};

TEST_F(AddCommandTest, FreshInstance__Execute__ShouldAddTheComponentAtIndexToAddingHierarchicModel) {
    CNComponentPtr component = makeCNComponentDummy();
    AddingHierarchicModelSpyPtr model = AddingHierarchicModelSpy::getNewInstance();
    AddCommandPtr sut = makeAddCommand(model, CNHierarchyIndex({0, 2}), component);

    sut->execute();

    expectComponentWasAddedAtIndex(model, component, CNHierarchyIndex({0, 2}));
}

TEST_F(AddCommandTest, FreshInstance__Undo__ShouldRemoveTheComponentAtIndexFromAddingHierarchicModel) {
    CNComponentPtr component = makeCNComponentDummy();
    AddingHierarchicModelSpyPtr model = AddingHierarchicModelSpy::getNewInstance();
    AddCommandPtr sut = makeAddCommand(model, CNHierarchyIndex({0, 2}), component);

    sut->undo();

    expectComponentWasRemovedAtIndex(model, component, CNHierarchyIndex({0, 2}));
}