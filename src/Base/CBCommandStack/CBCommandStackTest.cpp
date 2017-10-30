#include <gmock/gmock.h>
#include "CBCommandStack.h"

#include "Base/CBCommand/CBCommandMocks.h"
#include "Base/CBObserver/CBObserverMocks.h"

class CBCommandStackTest : public testing::Test {
protected:
    class CBObserverMock;
    typedef std::shared_ptr<CBObserverMock> CBObserverMockPtr;
    class CBObserverMock : public CBObserver {
    public:
        static CBObserverMockPtr getNewInstance(CBCommandStackPtr sut) {
            return CBObserverMockPtr(new CBObserverMock(sut));
        }
        virtual ~CBObserverMock() {}
    protected:
        CBObserverMock(CBCommandStackPtr sut) : sut(sut) {}

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

            std::string errorMessage = "CBObserverMock should be updated with undo " + boolToString(expectedUndoState)
                                       + ". Instead undo is " + boolToString(actual) + "!";

            EXPECT_THAT(actual, expectedUndoState) << errorMessage;
        }
        virtual void verifyRedoState() {
            bool actual = sut->redoIsPossible();

            std::string errorMessage = "CBObserverMock should be updated with redo " + boolToString(expectedRedoState)
                                       + ". Instead redo is " + boolToString(actual) + "!";

            EXPECT_THAT(actual, expectedRedoState) << errorMessage;
        }

        virtual std::string boolToString(bool boolean) {
            return boolean ? "possible" : "not possible";
        }

        virtual void verifyWasUpdated() {
            std::string errorMessage = "CBObserverMock should be updated, but it was not updated!";

            EXPECT_TRUE(wasUpdated) << errorMessage;
        }

    private:
        CBCommandStackPtr sut;
        bool wasUpdated = false;
        bool expectedUndoState = false;
        bool expectedRedoState = false;
    };

    virtual CBCommandStackPtr makeCBCommandStack() {
        return CBCommandStack::getNewInstance();
    }
    virtual CBCommandSpyPtr makeCBCommandSpy() {
        return CBCommandSpy::getNewInstance();
    }
    virtual CBCommandDummyPtr makeCBCommandDummy() {
        return CBCommandDummy::getNewInstance();
    }
    virtual CBObserverSpyPtr makeCBObserverSpy() {
        return CBObserverSpy::getNewInstance();
    }
    virtual CBObserverMockPtr makeCBObserverMock(CBCommandStackPtr sut) {
        return CBObserverMock::getNewInstance(sut);
    }


    virtual void expect_Undo_Is_Possible(CBCommandStackPtr sut) {
        std::string errorMessage = "Undo should be possible, but it's not!";

        EXPECT_TRUE(sut->undoIsPossible()) << errorMessage;
    }
    virtual void expect_Undo_Is_NOT_Possible(CBCommandStackPtr sut) {
        std::string errorMessage = "Undo should not be possible, but it is!";

        EXPECT_FALSE(sut->undoIsPossible()) << errorMessage;
    }

    virtual void expect_Redo_Is_Possible(CBCommandStackPtr sut) {
        std::string errorMessage = "Redo should be possible, but it's not!";

        EXPECT_TRUE(sut->redoIsPossible()) << errorMessage;
    }
    virtual void expect_Redo_Is_NOT_Possible(CBCommandStackPtr sut) {
        std::string errorMessage = "Redo should not be possible, but it is!";

        EXPECT_FALSE(sut->redoIsPossible()) << errorMessage;
    }

    virtual void expect_Is_Executed(CBCommandSpyPtr command) {
        std::string expected = "e";
        std::string actual = command->getLogString();

        std::string expectedCommandState = "executed";

        expectCommandsLogString(actual, expected, expectedCommandState);
    }
    virtual void expect_Is_Undone(CBCommandSpyPtr command) {
        std::string expected = "eu";
        std::string actual = command->getLogString();

        std::string expectedCommandState = "undone";

        expectCommandsLogString(actual, expected, expectedCommandState);
    }
    virtual void expect_Is_Redone(CBCommandSpyPtr command) {
        std::string expected = "eue";
        std::string actual = command->getLogString();

        std::string expectedCommandState = "redone";

        expectCommandsLogString(actual, expected, expectedCommandState);
    }
    virtual void expectCommandsLogString(std::string actualLog, std::string expectedLog, std::string expectedCommandState) {
        std::string errorMessage = "The command should be "+ expectedCommandState + ". This means: The command's log should be \"" + expectedLog + "\". Instead it is: \"" + actualLog + "\"";

        EXPECT_THAT(actualLog, testing::StrEq(expectedLog)) << errorMessage;
    }

    virtual void expect_Observer_Is_Updated(CBObserverSpyPtr observer) {
        bool result = observer->wasUpdated();

        std::string errorMessage = "CBObserverSpy should be updated, but it was not updated!";

        EXPECT_TRUE(result) << errorMessage;
    }
    virtual void expect_Observer_Is_NOT_Updated(CBObserverSpyPtr observer) {
        bool result = observer->wasUpdated();

        std::string errorMessage = "CBObserver should not be updated, but it was updated!";

        EXPECT_FALSE(result) << errorMessage;
    }
};


TEST_F(CBCommandStackTest, FreshInstance__UndoShould_Not_BePossible) {
    CBCommandStackPtr sut = makeCBCommandStack();

    expect_Undo_Is_NOT_Possible(sut);
}

TEST_F(CBCommandStackTest, FreshInstance__RedoShould_Not_BePossible) {
    CBCommandStackPtr sut = makeCBCommandStack();

    expect_Redo_Is_NOT_Possible(sut);
}

TEST_F(CBCommandStackTest, FreshInstance__Undo__ThrowsCBNoExecutedCommandsException) {
    CBCommandStackPtr sut = makeCBCommandStack();

    std::string errorMessage = "Should throw CBNoExecutedCommandsException, but it doesn't!";
    EXPECT_THROW(sut->undo(), CBNoExecutedCommandsException) << errorMessage;
}

TEST_F(CBCommandStackTest, FreshInstance__Redo__ThrowsCBNoUndoneCommandsException) {
    CBCommandStackPtr sut = makeCBCommandStack();

    std::string errorMessage = "Should throw CBNoUndoneCommandsException, but it doesn't!";
    EXPECT_THROW(sut->redo(), CBNoUndoneCommandsException) << errorMessage;
}

TEST_F(CBCommandStackTest, FreshInstance__Invoke__ExecutesInvokedCommand) {
    CBCommandStackPtr sut = makeCBCommandStack();
    CBCommandSpyPtr command = makeCBCommandSpy();

    sut->invoke(command);

    expect_Is_Executed(command);
}

TEST_F(CBCommandStackTest, InvokedCommand__UndoShould_BePossible) {
    CBCommandStackPtr sut = makeCBCommandStack();
    CBCommandSpyPtr command = makeCBCommandSpy();

    sut->invoke(command);

    expect_Undo_Is_Possible(sut);
}

TEST_F(CBCommandStackTest, InvokedCommand__Undo__InvokedCommandIs_Undone) {
    CBCommandStackPtr sut = makeCBCommandStack();
    CBCommandSpyPtr command = makeCBCommandSpy();
    sut->invoke(command);

    sut->undo();

    expect_Is_Undone(command);
}

TEST_F(CBCommandStackTest, InvokedCommand_Undo__UndoShould_Not_BePossible) {
    CBCommandStackPtr sut = makeCBCommandStack();
    CBCommandSpyPtr command = makeCBCommandSpy();
    sut->invoke(command);
    sut->undo();

    expect_Undo_Is_NOT_Possible(sut);
}

TEST_F(CBCommandStackTest, InvokedCommand_Undo__RedoShould_BePossible) {
    CBCommandStackPtr sut = makeCBCommandStack();
    CBCommandSpyPtr command = makeCBCommandSpy();
    sut->invoke(command);
    sut->undo();

    expect_Redo_Is_Possible(sut);
}

TEST_F(CBCommandStackTest, InvokedCommand_Undo__Redo__UndoneCommandIs_Redone) {
    CBCommandStackPtr sut = makeCBCommandStack();
    CBCommandSpyPtr command = makeCBCommandSpy();
    sut->invoke(command);
    sut->undo();

    sut->redo();

    expect_Is_Redone(command);
}

TEST_F(CBCommandStackTest, InvokedCommand_Undo_Redo__RedoShould_Not_BePossible) {
    CBCommandStackPtr sut = makeCBCommandStack();
    CBCommandSpyPtr command = makeCBCommandSpy();
    sut->invoke(command);
    sut->undo();
    sut->redo();

    expect_Redo_Is_NOT_Possible(sut);
}

TEST_F(CBCommandStackTest, InvokedCommand_Undo_Redo__UndoShould_BePossible) {
    CBCommandStackPtr sut = makeCBCommandStack();
    CBCommandSpyPtr command = makeCBCommandSpy();
    sut->invoke(command);
    sut->undo();
    sut->redo();

    expect_Undo_Is_Possible(sut);
}

TEST_F(CBCommandStackTest, InvokedCommand_Undo_InvokedCommand__RedoShould_Not_BePossible) {
    CBCommandStackPtr sut = makeCBCommandStack();
    sut->invoke(makeCBCommandSpy());
    sut->undo();

    sut->invoke(makeCBCommandSpy());

    expect_Redo_Is_NOT_Possible(sut);
}



TEST_F(CBCommandStackTest, _2AttachedObservers_1DetachedObservers__Invoke__UpdatesAttachedObservers)  {
    CBCommandStackPtr sut = makeCBCommandStack();
    CBObserverSpyPtr first = makeCBObserverSpy();
    CBObserverSpyPtr second = makeCBObserverSpy();
    sut->attach(first);
    sut->attach(second);
    sut->detach(first);

    sut->invoke(makeCBCommandDummy());

    expect_Observer_Is_NOT_Updated(first);
    expect_Observer_Is_Updated(second);
}

TEST_F(CBCommandStackTest, InvokedCommand_2AttachedObservers_1DetachedObservers__Undo__UpdatesAttachedObservers) {
    CBCommandStackPtr sut = makeCBCommandStack();
    CBObserverSpyPtr first = makeCBObserverSpy();
    CBObserverSpyPtr second = makeCBObserverSpy();
    sut->invoke(makeCBCommandDummy());
    sut->attach(first);
    sut->attach(second);
    sut->detach(first);

    sut->undo();

    expect_Observer_Is_NOT_Updated(first);
    expect_Observer_Is_Updated(second);
}

TEST_F(CBCommandStackTest, InvokedCommand_Undo_2AttachedObservers_1DetachedObservers__Redo__UpdatesAttachedObservers) {
    CBCommandStackPtr sut = makeCBCommandStack();
    CBObserverSpyPtr first = makeCBObserverSpy();
    CBObserverSpyPtr second = makeCBObserverSpy();
    sut->invoke(makeCBCommandDummy());
    sut->undo();
    sut->attach(first);
    sut->attach(second);
    sut->detach(first);

    sut->redo();

    expect_Observer_Is_NOT_Updated(first);
    expect_Observer_Is_Updated(second);
}



TEST_F(CBCommandStackTest, AttachedObserver__Invoke__UpdatesObserverWith_UndoPossible_RedoNotPossible) {
    CBCommandStackPtr sut = makeCBCommandStack();
    CBObserverMockPtr observer = makeCBObserverMock(sut);
    observer->setExpected_UndoState_ForUpdating(true);
    observer->setExpected_RedoState_ForUpdating(false);
    sut->attach(observer);

    sut->invoke(makeCBCommandDummy());

    observer->verifyWasUpdated();
}

TEST_F(CBCommandStackTest, InvokedCommand_AttachedObserver__Undo__UpdatesObserverWith_UndoNotPossible_RedoPossible) {
    CBCommandStackPtr sut = makeCBCommandStack();
    CBObserverMockPtr observer = makeCBObserverMock(sut);
    observer->setExpected_UndoState_ForUpdating(false);
    observer->setExpected_RedoState_ForUpdating(true);
    sut->invoke(makeCBCommandDummy());
    sut->attach(observer);

    sut->undo();

    observer->verifyWasUpdated();
}

TEST_F(CBCommandStackTest, InvokedCommand_Undo_AttachedObserver__Redo__UpdatesObserverWith_UndoPossible_RedoNotPossible) {
    CBCommandStackPtr sut = makeCBCommandStack();
    CBObserverMockPtr observer = makeCBObserverMock(sut);
    observer->setExpected_UndoState_ForUpdating(true);
    observer->setExpected_RedoState_ForUpdating(false);
    sut->invoke(makeCBCommandDummy());
    sut->undo();
    sut->attach(observer);

    sut->redo();

    observer->verifyWasUpdated();
}