#include <gmock/gmock.h>
#include "CNUndoAction.h"
#include "Base/CNCommandHistory/CNCommandHistoryTestDoubles.h"

class CNUndoActionTest : public testing::Test {
protected:
    virtual CNUndoActionPtr makeCNUndoAction(CNCommandHistoryPtr commandHistory) {
        return CNUndoAction::getNewInstance(commandHistory);
    }
    virtual CNCommandHistorySpyPtr makeCNCommandHistorySpy() {
        return CNCommandHistorySpy::getNewInstance();
    }

    virtual void expectWasTriggeredToUndo(CNCommandHistorySpyPtr commandHistory) {
        bool result = commandHistory->wasUndone();

        std::string errorMessage = "The CNCommandHistory should be triggered to undo, but \"undo\" was not called!";

        EXPECT_TRUE(result) << errorMessage;
    }
};

TEST_F(CNUndoActionTest, FreshInstance__Execute__CNCommandHistoryWasTriggeredToUndo) {
    CNCommandHistorySpyPtr commandHistory = makeCNCommandHistorySpy();
    CNUndoActionPtr sut = makeCNUndoAction(commandHistory);

    sut->execute();

    expectWasTriggeredToUndo(commandHistory);
}