#include <gmock/gmock.h>
#include "CNCommandStack.h"

#include "Base/CNCommandInvoker/CNCommandTestDoubles.h"
#include "Base/CNObserver/CNObserverTestDoubles.h"

class CNCommandStackTest : public testing::Test {
protected:
    class CNObserverMock;
    typedef std::shared_ptr<CNObserverMock> CNObserverMockPtr;
    class CNObserverMock : public CNObserver {
    public:
        static CNObserverMockPtr getNewInstance(CNCommandStackPtr sut) {
            return CNObserverMockPtr(new CNObserverMock(sut));
        }
        virtual ~CNObserverMock() {}
    protected:
        CNObserverMock(CNCommandStackPtr sut) : sut(sut) {}

    public:
        virtual void update() {
            verifyUndoState();
            verifyRedoState();

            wasUpdated = true;
        }

        virtual void setExpected_UndoState_ForUpdating(bool expected) {
            expectedUndoState = expected;
        }
        virtual void setExpected_RedoState_ForUpdating(bool expected) {
            expectedRedoState = expected;
        }

        virtual void verifyUndoState() {
            bool actual = sut->undoIsPossible();

            std::string errorMessage = "CNObserverMock should be updated with undo " + boolToString(expectedUndoState)
                                       + ". Instead undo is " + boolToString(actual) + "!";

            EXPECT_THAT(actual, expectedUndoState) << errorMessage;
        }
        virtual void verifyRedoState() {
            bool actual = sut->redoIsPossible();

            std::string errorMessage = "CNObserverMock should be updated with redo " + boolToString(expectedRedoState)
                                       + ". Instead redo is " + boolToString(actual) + "!";

            EXPECT_THAT(actual, expectedRedoState) << errorMessage;
        }

        virtual std::string boolToString(bool boolean) {
            return boolean ? "possible" : "not possible";
        }

        virtual void verifyWasUpdated() {
            std::string errorMessage = "CNObserverMock should be updated, but it was not updated!";

            EXPECT_TRUE(wasUpdated) << errorMessage;
        }

    private:
        CNCommandStackPtr sut;
        bool wasUpdated = false;
        bool expectedUndoState = false;
        bool expectedRedoState = false;
    };

    virtual CNCommandStackPtr makeCNCommandStack() {
        return CNCommandStack::getNewInstance();
    }
    virtual CNCommandSpyPtr makeCNCommandSpy() {
        return CNCommandSpy::getNewInstance();
    }
    virtual CNCommandDummyPtr makeCNCommandDummy() {
        return CNCommandDummy::getNewInstance();
    }
    virtual CNObserverSpyPtr makeCNObserverSpy() {
        return CNObserverSpy::getNewInstance();
    }
    virtual CNObserverMockPtr makeCNObserverMock(CNCommandStackPtr sut) {
        return CNObserverMock::getNewInstance(sut);
    }


    virtual void expect_Undo_Is_Possible(CNCommandStackPtr sut) {
        std::string errorMessage = "Undo should be possible, but it's not!";

        EXPECT_TRUE(sut->undoIsPossible()) << errorMessage;
    }
    virtual void expect_Undo_Is_NOT_Possible(CNCommandStackPtr sut) {
        std::string errorMessage = "Undo should not be possible, but it is!";

        EXPECT_FALSE(sut->undoIsPossible()) << errorMessage;
    }

    virtual void expect_Redo_Is_Possible(CNCommandStackPtr sut) {
        std::string errorMessage = "Redo should be possible, but it's not!";

        EXPECT_TRUE(sut->redoIsPossible()) << errorMessage;
    }
    virtual void expect_Redo_Is_NOT_Possible(CNCommandStackPtr sut) {
        std::string errorMessage = "Redo should not be possible, but it is!";

        EXPECT_FALSE(sut->redoIsPossible()) << errorMessage;
    }

    virtual void expect_Is_Executed(CNCommandSpyPtr command) {
        std::string expected = "e";
        std::string actual = command->getLogString();

        std::string expectedCommandState = "executed";

        expectCommandsLogString(actual, expected, expectedCommandState);
    }
    virtual void expect_Is_Undone(CNCommandSpyPtr command) {
        std::string expected = "eu";
        std::string actual = command->getLogString();

        std::string expectedCommandState = "undone";

        expectCommandsLogString(actual, expected, expectedCommandState);
    }
    virtual void expect_Is_Redone(CNCommandSpyPtr command) {
        std::string expected = "eue";
        std::string actual = command->getLogString();

        std::string expectedCommandState = "redone";

        expectCommandsLogString(actual, expected, expectedCommandState);
    }
    virtual void expectCommandsLogString(std::string actualLog, std::string expectedLog, std::string expectedCommandState) {
        std::string errorMessage = "The command should be "+ expectedCommandState + ". This means: The command's log should be \"" + expectedLog + "\". Instead it is: \"" + actualLog + "\"";

        EXPECT_THAT(actualLog, testing::StrEq(expectedLog)) << errorMessage;
    }

    virtual void expect_Observer_Is_Updated(CNObserverSpyPtr observer) {
        bool result = observer->wasUpdated();

        std::string errorMessage = "CNObserverSpy should be updated, but it was not updated!";

        EXPECT_TRUE(result) << errorMessage;
    }
    virtual void expect_Observer_Is_NOT_Updated(CNObserverSpyPtr observer) {
        bool result = observer->wasUpdated();

        std::string errorMessage = "CNObserver should not be updated, but it was updated!";

        EXPECT_FALSE(result) << errorMessage;
    }
};


TEST_F(CNCommandStackTest, FreshInstance__UndoShould_Not_BePossible) {
    CNCommandStackPtr sut = makeCNCommandStack();

    expect_Undo_Is_NOT_Possible(sut);
}

TEST_F(CNCommandStackTest, FreshInstance__RedoShould_Not_BePossible) {
    CNCommandStackPtr sut = makeCNCommandStack();

    expect_Redo_Is_NOT_Possible(sut);
}

TEST_F(CNCommandStackTest, FreshInstance__Undo__ThrowsCNNoExecutedCommandsException) {
    CNCommandStackPtr sut = makeCNCommandStack();

    std::string errorMessage = "Should throw CNNoExecutedCommandsException, but it doesn't!";
    EXPECT_THROW(sut->undo(), CNNoExecutedCommandsException) << errorMessage;
}

TEST_F(CNCommandStackTest, FreshInstance__Redo__ThrowsCNNoUndoneCommandsException) {
    CNCommandStackPtr sut = makeCNCommandStack();

    std::string errorMessage = "Should throw CNNoUndoneCommandsException, but it doesn't!";
    EXPECT_THROW(sut->redo(), CNNoUndoneCommandsException) << errorMessage;
}

TEST_F(CNCommandStackTest, FreshInstance__Invoke__ExecutesInvokedCommand) {
    CNCommandStackPtr sut = makeCNCommandStack();
    CNCommandSpyPtr command = makeCNCommandSpy();

    sut->invoke(command);

    expect_Is_Executed(command);
}

TEST_F(CNCommandStackTest, InvokedCommand__UndoShould_BePossible) {
    CNCommandStackPtr sut = makeCNCommandStack();
    CNCommandSpyPtr command = makeCNCommandSpy();

    sut->invoke(command);

    expect_Undo_Is_Possible(sut);
}

TEST_F(CNCommandStackTest, InvokedCommand__Undo__InvokedCommandIs_Undone) {
    CNCommandStackPtr sut = makeCNCommandStack();
    CNCommandSpyPtr command = makeCNCommandSpy();
    sut->invoke(command);

    sut->undo();

    expect_Is_Undone(command);
}

TEST_F(CNCommandStackTest, InvokedCommand_Undo__UndoShould_Not_BePossible) {
    CNCommandStackPtr sut = makeCNCommandStack();
    CNCommandSpyPtr command = makeCNCommandSpy();
    sut->invoke(command);
    sut->undo();

    expect_Undo_Is_NOT_Possible(sut);
}

TEST_F(CNCommandStackTest, InvokedCommand_Undo__RedoShould_BePossible) {
    CNCommandStackPtr sut = makeCNCommandStack();
    CNCommandSpyPtr command = makeCNCommandSpy();
    sut->invoke(command);
    sut->undo();

    expect_Redo_Is_Possible(sut);
}

TEST_F(CNCommandStackTest, InvokedCommand_Undo__Redo__UndoneCommandIs_Redone) {
    CNCommandStackPtr sut = makeCNCommandStack();
    CNCommandSpyPtr command = makeCNCommandSpy();
    sut->invoke(command);
    sut->undo();

    sut->redo();

    expect_Is_Redone(command);
}

TEST_F(CNCommandStackTest, InvokedCommand_Undo_Redo__RedoShould_Not_BePossible) {
    CNCommandStackPtr sut = makeCNCommandStack();
    CNCommandSpyPtr command = makeCNCommandSpy();
    sut->invoke(command);
    sut->undo();
    sut->redo();

    expect_Redo_Is_NOT_Possible(sut);
}

TEST_F(CNCommandStackTest, InvokedCommand_Undo_Redo__UndoShould_BePossible) {
    CNCommandStackPtr sut = makeCNCommandStack();
    CNCommandSpyPtr command = makeCNCommandSpy();
    sut->invoke(command);
    sut->undo();
    sut->redo();

    expect_Undo_Is_Possible(sut);
}

TEST_F(CNCommandStackTest, InvokedCommand_Undo_InvokedCommand__RedoShould_Not_BePossible) {
    CNCommandStackPtr sut = makeCNCommandStack();
    sut->invoke(makeCNCommandSpy());
    sut->undo();

    sut->invoke(makeCNCommandSpy());

    expect_Redo_Is_NOT_Possible(sut);
}



TEST_F(CNCommandStackTest, _2AttachedObservers_1DetachedObservers__Invoke__UpdatesAttachedObservers)  {
    CNCommandStackPtr sut = makeCNCommandStack();
    CNObserverSpyPtr first = makeCNObserverSpy();
    CNObserverSpyPtr second = makeCNObserverSpy();
    sut->attach(first);
    sut->attach(second);
    sut->detach(first);

    sut->invoke(makeCNCommandDummy());

    expect_Observer_Is_NOT_Updated(first);
    expect_Observer_Is_Updated(second);
}

TEST_F(CNCommandStackTest, InvokedCommand_2AttachedObservers_1DetachedObservers__Undo__UpdatesAttachedObservers) {
    CNCommandStackPtr sut = makeCNCommandStack();
    CNObserverSpyPtr first = makeCNObserverSpy();
    CNObserverSpyPtr second = makeCNObserverSpy();
    sut->invoke(makeCNCommandDummy());
    sut->attach(first);
    sut->attach(second);
    sut->detach(first);

    sut->undo();

    expect_Observer_Is_NOT_Updated(first);
    expect_Observer_Is_Updated(second);
}

TEST_F(CNCommandStackTest, InvokedCommand_Undo_2AttachedObservers_1DetachedObservers__Redo__UpdatesAttachedObservers) {
    CNCommandStackPtr sut = makeCNCommandStack();
    CNObserverSpyPtr first = makeCNObserverSpy();
    CNObserverSpyPtr second = makeCNObserverSpy();
    sut->invoke(makeCNCommandDummy());
    sut->undo();
    sut->attach(first);
    sut->attach(second);
    sut->detach(first);

    sut->redo();

    expect_Observer_Is_NOT_Updated(first);
    expect_Observer_Is_Updated(second);
}



TEST_F(CNCommandStackTest, AttachedObserver__Invoke__UpdatesObserverWith_UndoPossible_RedoNotPossible) {
    CNCommandStackPtr sut = makeCNCommandStack();
    CNObserverMockPtr observer = makeCNObserverMock(sut);
    observer->setExpected_UndoState_ForUpdating(true);
    observer->setExpected_RedoState_ForUpdating(false);
    sut->attach(observer);

    sut->invoke(makeCNCommandDummy());

    observer->verifyWasUpdated();
}

TEST_F(CNCommandStackTest, InvokedCommand_AttachedObserver__Undo__UpdatesObserverWith_UndoNotPossible_RedoPossible) {
    CNCommandStackPtr sut = makeCNCommandStack();
    CNObserverMockPtr observer = makeCNObserverMock(sut);
    observer->setExpected_UndoState_ForUpdating(false);
    observer->setExpected_RedoState_ForUpdating(true);
    sut->invoke(makeCNCommandDummy());
    sut->attach(observer);

    sut->undo();

    observer->verifyWasUpdated();
}

TEST_F(CNCommandStackTest, InvokedCommand_Undo_AttachedObserver__Redo__UpdatesObserverWith_UndoPossible_RedoNotPossible) {
    CNCommandStackPtr sut = makeCNCommandStack();
    CNObserverMockPtr observer = makeCNObserverMock(sut);
    observer->setExpected_UndoState_ForUpdating(true);
    observer->setExpected_RedoState_ForUpdating(false);
    sut->invoke(makeCNCommandDummy());
    sut->undo();
    sut->attach(observer);

    sut->redo();

    observer->verifyWasUpdated();
}