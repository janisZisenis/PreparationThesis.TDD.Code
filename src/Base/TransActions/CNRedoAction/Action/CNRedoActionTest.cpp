#include <gmock/gmock.h>
#include "CNRedoAction.h"
#include "Base/CNCommandHistory/CNCommandHistoryTestDoubles.h"

class CNRedoActionTest : public testing::Test {
protected:
    virtual CNRedoActionPtr makeCNRedoAction(CNCommandHistoryPtr commandHistory) {
        return CNRedoAction::getNewInstance(commandHistory);
    }
    virtual CNCommandHistorySpyPtr makeCNCommandHistorySpy() {
        return CNCommandHistorySpy::getNewInstance();
    }

    virtual void expectWasTriggeredToRedo(CNCommandHistorySpyPtr commandHistory) {
        bool result = commandHistory->wasRedone();

        std::string errorMessage = "The CNCommandHistory should be triggered to redo, but \"redo\" was not called!";

        EXPECT_TRUE(result) << errorMessage;
    }
};

TEST_F(CNRedoActionTest, FreshInstance__Execute__CNCommandHistoryWasTriggeredToRedo) {
    CNCommandHistorySpyPtr commandHistory = makeCNCommandHistorySpy();
    CNRedoActionPtr sut = makeCNRedoAction(commandHistory);

    sut->execute();

    expectWasTriggeredToRedo(commandHistory);
}