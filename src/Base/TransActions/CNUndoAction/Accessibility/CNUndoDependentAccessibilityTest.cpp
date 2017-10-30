#include <gmock/gmock.h>

#include "CNUndoDependentAccessibility.h"
#include "Base/CNCommandHistory/CNCommandHistoryTestDoubles.h"

class CNUndoDependentAccessibilityTest : public testing::Test {
protected:
    virtual CNUndoDependentAccessibilityPtr makeCNUndoDependentAccessibility(CNCommandHistoryPtr commandHistory) {
        return CNUndoDependentAccessibility::getNewInstance(commandHistory);
    }
    virtual CNCommandHistoryStubPtr makeCNCommandHistoryStub(bool undoIsPossible) {
        CNCommandHistoryStubPtr stub = CNCommandHistoryStub::getNewInstance();
        stub->setUndoIsPossible(undoIsPossible);
        return stub;
    }

    virtual void expectIsAccessible(CNUndoDependentAccessibilityPtr sut) {
        bool result = sut->isAccessible();

        std::string errorMessage = "Should be accessible because \"undo\" of CNCommandHistory is possible, but it's not accessible!";

        EXPECT_TRUE(result) << errorMessage;
    }

    virtual void expectIsNotAccessible(CNUndoDependentAccessibilityPtr  sut) {
        bool result = sut->isAccessible();

        std::string errorMessage = "Should not be accessible because \"undo\" of CNCommandHistory is not possible, but it's accessible!";

        EXPECT_FALSE(result) << errorMessage;
    }
};

TEST_F(CNUndoDependentAccessibilityTest, CNCommandHistory_Undo_Possible__IsAccessible__ReturnsTrue) {
    bool undoIsPossible = true;
    CNCommandHistoryStubPtr commandHistory = makeCNCommandHistoryStub(undoIsPossible);
    CNUndoDependentAccessibilityPtr sut = makeCNUndoDependentAccessibility(commandHistory);

    expectIsAccessible(sut);
}

TEST_F(CNUndoDependentAccessibilityTest, CNCommandHistory_Undo_NOT_Possible__IsAccessible__ReturnsFalse) {
    bool undoIsPossible = false;
    CNCommandHistoryStubPtr commandHistory = makeCNCommandHistoryStub(undoIsPossible);
    CNUndoDependentAccessibilityPtr sut = makeCNUndoDependentAccessibility(commandHistory);

    expectIsNotAccessible(sut);
}