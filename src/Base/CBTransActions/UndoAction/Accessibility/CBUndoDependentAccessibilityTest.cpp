#include <gmock/gmock.h>

#include "CBUndoDependentAccessibility.h"
#include "Base/CBCommandHistory/CBCommandHistoryMocks.h"

class CBUndoDependentAccessibilityTest : public testing::Test {
protected:
    virtual CBUndoDependentAccessibilityPtr makeCBUndoDependentAccessibility(CBCommandHistoryPtr commandHistory) {
        return CBUndoDependentAccessibility::getNewInstance(commandHistory);
    }
    virtual CBCommandHistoryStubPtr makeCBCommandHistoryStub(bool undoIsPossible) {
        CBCommandHistoryStubPtr stub = CBCommandHistoryStub::getNewInstance();
        stub->setUndoIsPossible(undoIsPossible);
        return stub;
    }

    virtual void expectIsAccessible(CBUndoDependentAccessibilityPtr sut) {
        bool result = sut->isAccessible();

        std::string errorMessage = "Should be accessible because \"undo\" of CBCommandHistory is possible, but it's not accessible!";

        EXPECT_TRUE(result) << errorMessage;
    }

    virtual void expectIsNotAccessible(CBUndoDependentAccessibilityPtr  sut) {
        bool result = sut->isAccessible();

        std::string errorMessage = "Should not be accessible because \"undo\" of CBCommandHistory is not possible, but it's accessible!";

        EXPECT_FALSE(result) << errorMessage;
    }
};

TEST_F(CBUndoDependentAccessibilityTest, CBCommandHistory_Undo_Possible__IsAccessible__ReturnsTrue) {
    bool undoIsPossible = true;
    CBCommandHistoryStubPtr commandHistory = makeCBCommandHistoryStub(undoIsPossible);
    CBUndoDependentAccessibilityPtr sut = makeCBUndoDependentAccessibility(commandHistory);

    expectIsAccessible(sut);
}

TEST_F(CBUndoDependentAccessibilityTest, CBCommandHistory_Undo_NOT_Possible__IsAccessible__ReturnsFalse) {
    bool undoIsPossible = false;
    CBCommandHistoryStubPtr commandHistory = makeCBCommandHistoryStub(undoIsPossible);
    CBUndoDependentAccessibilityPtr sut = makeCBUndoDependentAccessibility(commandHistory);

    expectIsNotAccessible(sut);
}