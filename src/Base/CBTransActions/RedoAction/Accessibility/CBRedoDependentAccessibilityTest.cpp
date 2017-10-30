#include <gmock/gmock.h>

#include "CBRedoDependentAccessibility.h"
#include "Base/CBCommandHistory/CBCommandHistoryMocks.h"

class CBRedoDependentAccessibilityTest : public testing::Test {
protected:
    virtual CBRedoDependentAccessibilityPtr makeCBRedoDependentAccessibility(CBCommandHistoryPtr commandHistory) {
        return CBRedoDependentAccessibility::getNewInstance(commandHistory);
    }
    virtual CBCommandHistoryStubPtr makeCBCommandHistoryStub(bool redoIsPossible) {
        CBCommandHistoryStubPtr stub = CBCommandHistoryStub::getNewInstance();
        stub->setRedoIsPossible(redoIsPossible);
        return stub;
    }

    virtual void expectIsAccessible(CBRedoDependentAccessibilityPtr sut) {
        bool result = sut->isAccessible();

        std::string errorMessage = "Should be accessible because \"redo\" of CBCommandHistory is possible, but it's not accessible!";

        EXPECT_TRUE(result) << errorMessage;
    }

    virtual void expectIsNotAccessible(CBRedoDependentAccessibilityPtr sut) {
        bool result = sut->isAccessible();

        std::string errorMessage = "Should not be accessible because \"redo\" of CBCommandHistory is not possible, but it's accessible!";

        EXPECT_FALSE(result) << errorMessage;
    }
};

TEST_F(CBRedoDependentAccessibilityTest, CBCommandHistory_Redo_Possible__IsAccessible__ReturnsTrue) {
    bool redoIsPossible = true;
    CBCommandHistoryStubPtr commandHistory = makeCBCommandHistoryStub(redoIsPossible);
    CBRedoDependentAccessibilityPtr sut = makeCBRedoDependentAccessibility(commandHistory);

    expectIsAccessible(sut);
}

TEST_F(CBRedoDependentAccessibilityTest, CBCommandHistory_Redo_NOT_Possible__IsAccessible__ReturnsFalse) {
    bool redoIsPossible = false;
    CBCommandHistoryStubPtr commandHistory = makeCBCommandHistoryStub(redoIsPossible);
    CBRedoDependentAccessibilityPtr sut = makeCBRedoDependentAccessibility(commandHistory);

    expectIsNotAccessible(sut);
}