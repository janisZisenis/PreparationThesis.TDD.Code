#include <gmock/gmock.h>

#include "AddCommand.h"
#include "CrossViews/HierarchicModel/API/AddingHierarchicModelTestDoubles.h"
#include <CrossNative/CNComponent/CNComponentTestDoubles.h>

class AddCommandTest : public testing::Test {
protected:
    virtual AddCommandPtr makeAddCommand(CNComponentPtr component, const CNHierarchyIndex index, AddingHierarchicModelPtr model) {
        return AddCommand::getNewInstance(component, index, model);
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
        CNHierarchyIndex expectedIndex = index;
        CNHierarchyIndex actualIndex = model->getAddedIndex();

        std::string errorMessage = "AddingHierarchicModel should have added the CNComponent at index " + expectedIndex.toString() + " , but it has not!";

        EXPECT_THAT(expectedIndex, testing::Eq(actualIndex)) << errorMessage;
    }
};

TEST_F(AddCommandTest, FreshInstance__Execute__ShouldAddTheComponentAtIndexToAddingHierarchicModel) {
    CNComponentPtr component = makeCNComponentDummy();
    AddingHierarchicModelSpyPtr model = AddingHierarchicModelSpy::getNewInstance();
    AddCommandPtr sut = makeAddCommand(component, CNHierarchyIndex({0, 2}), model);

    sut->execute();

    expectComponentWasAddedAtIndex(model, component, CNHierarchyIndex({0, 2}));
}

//TEST_F(AddCommandTest, testUndoShouldTriggerTheModelToRemoveTheVisitableComposerPairAtAddedIndex) {
//    AddingHierarchicModelSpyPtr model = AddingHierarchicModelSpy::getNewInstance();
//    VisitableComposerPairDummyPtr pair = VisitableComposerPairDummy::getNewInstance();
//
//    CCore::HierarchyIndex addingIndex({1, 5});
//    AddCommandPtr sut = AddCommand::getNewInstance(pair, addingIndex, model);
//
//    sut->undo();
//
//    EXPECT_THAT(model->getRemovedPair(), pair);
//    EXPECT_TRUE(model->getRemovingIndex() == addingIndex);
//}