#include <gmock/gmock.h>

#include "CNRedoDependentAccessibility.h"
#include "Base/CNCommandHistory/CNCommandHistoryTestDoubles.h"

class CNRedoDependentAccessibilityTest : public testing::Test {
protected:
    virtual CNRedoDependentAccessibilityPtr makeCNRedoDependentAccessibility(CNCommandHistoryPtr commandHistory) {
        return CNRedoDependentAccessibility::getNewInstance(commandHistory);
    }
    virtual CNCommandHistoryStubPtr makeCNCommandHistoryStub(bool redoIsPossible) {
        CNCommandHistoryStubPtr stub = CNCommandHistoryStub::getNewInstance();
        stub->setRedoIsPossible(redoIsPossible);
        return stub;
    }

    virtual void expectIsAccessible(CNRedoDependentAccessibilityPtr sut) {
        bool result = sut->isAccessible();

        std::string errorMessage = "Should be accessible because \"redo\" of CNCommandHistory is possible, but it's not accessible!";

        EXPECT_TRUE(result) << errorMessage;
    }

    virtual void expectIsNotAccessible(CNRedoDependentAccessibilityPtr sut) {
        bool result = sut->isAccessible();

        std::string errorMessage = "Should not be accessible because \"redo\" of CNCommandHistory is not possible, but it's accessible!";

        EXPECT_FALSE(result) << errorMessage;
    }
};

TEST_F(CNRedoDependentAccessibilityTest, CNCommandHistory_Redo_Possible__IsAccessible__ReturnsTrue) {
    bool redoIsPossible = true;
    CNCommandHistoryStubPtr commandHistory = makeCNCommandHistoryStub(redoIsPossible);
    CNRedoDependentAccessibilityPtr sut = makeCNRedoDependentAccessibility(commandHistory);

    expectIsAccessible(sut);
}

TEST_F(CNRedoDependentAccessibilityTest, CNCommandHistory_Redo_NOT_Possible__IsAccessible__ReturnsFalse) {
    bool redoIsPossible = false;
    CNCommandHistoryStubPtr commandHistory = makeCNCommandHistoryStub(redoIsPossible);
    CNRedoDependentAccessibilityPtr sut = makeCNRedoDependentAccessibility(commandHistory);

    expectIsNotAccessible(sut);
}