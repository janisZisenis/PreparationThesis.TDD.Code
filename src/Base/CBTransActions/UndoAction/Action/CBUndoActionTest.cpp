#include <gmock/gmock.h>
#include "CBUndoAction.h"
#include "Base/CBCommandHistory/CBCommandHistoryMocks.h"

class CBUndoActionTest : public testing::Test {
protected:
    virtual CBUndoActionPtr makeCBUndoAction(CBCommandHistoryPtr commandHistory) {
        return CBUndoAction::getNewInstance(commandHistory);
    }
    virtual CBCommandHistorySpyPtr makeCBCommandHistorySpy() {
        return CBCommandHistorySpy::getNewInstance();
    }

    virtual void expectWasTriggeredToUndo(CBCommandHistorySpyPtr commandHistory) {
        bool result = commandHistory->wasUndone();

        std::string errorMessage = "The CBCommandHistory should be triggered to undo, but \"undo\" was not called!";

        EXPECT_TRUE(result) << errorMessage;
    }
};

TEST_F(CBUndoActionTest, FreshInstance__Execute__CBCommandHistoryWasTriggeredToUndo) {
    CBCommandHistorySpyPtr commandHistory = makeCBCommandHistorySpy();
    CBUndoActionPtr sut = makeCBUndoAction(commandHistory);

    sut->execute();

    expectWasTriggeredToUndo(commandHistory);
}