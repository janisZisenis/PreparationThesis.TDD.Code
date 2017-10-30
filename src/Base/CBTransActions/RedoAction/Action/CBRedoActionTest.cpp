#include <gmock/gmock.h>
#include "CBRedoAction.h"
#include "Base/CBCommandHistory/CBCommandHistoryMocks.h"

class CBRedoActionTest : public testing::Test {
protected:
    virtual CBRedoActionPtr makeCBRedoAction(CBCommandHistoryPtr commandHistory) {
        return CBRedoAction::getNewInstance(commandHistory);
    }
    virtual CBCommandHistorySpyPtr makeCBCommandHistorySpy() {
        return CBCommandHistorySpy::getNewInstance();
    }

    virtual void expectWasTriggeredToRedo(CBCommandHistorySpyPtr commandHistory) {
        bool result = commandHistory->wasRedone();

        std::string errorMessage = "The CBCommandHistory should be triggered to redo, but \"redo\" was not called!";

        EXPECT_TRUE(result) << errorMessage;
    }
};

TEST_F(CBRedoActionTest, FreshInstance__Execute__CBCommandHistoryWasTriggeredToRedo) {
    CBCommandHistorySpyPtr commandHistory = makeCBCommandHistorySpy();
    CBRedoActionPtr sut = makeCBRedoAction(commandHistory);

    sut->execute();

    expectWasTriggeredToRedo(commandHistory);
}