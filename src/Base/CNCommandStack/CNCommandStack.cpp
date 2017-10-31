#include "CNCommandStack.h"
#include "Base/CNCommandInvoker/CNCommand.h"
#include "Base/CNObserver/CNObserver.h"
#include "Base/CNSubject/CNSubject.h"

CNCommandStackPtr CNCommandStack::getNewInstance() {
    return CNCommandStackPtr(new CNCommandStack());
}

CNCommandStack::~CNCommandStack() {}

CNCommandStack::CNCommandStack() : subject(CNSubject::getNewInstance()) {}

void CNCommandStack::invoke(CNCommandPtr command) {
    removeUndoneCommands();

    executeCommand(command);

    notifyObservers();
}

void CNCommandStack::undo() {
    if(!undoIsPossible()) throw CNNoExecutedCommandsException();

    undoCommand();

    notifyObservers();
}

void CNCommandStack::redo() {
    if(!redoIsPossible()) throw CNNoUndoneCommandsException();

    redoCommand();

    notifyObservers();
}

bool CNCommandStack::undoIsPossible() {
    return !executedCommands.empty();
}

bool CNCommandStack::redoIsPossible() {
    return !undoneCommands.empty();
}

void CNCommandStack::attach(CNObserverPtr observer) {
    subject->attach(observer);
}

void CNCommandStack::detach(CNObserverPtr observer) {
    subject->detach(observer);
}

void CNCommandStack::removeUndoneCommands() {
    undoneCommands = std::stack<CNCommandPtr>();
}

void CNCommandStack::executeCommand(std::shared_ptr<CNCommand> command) {
    executedCommands.push(command);
    command->execute();
}

void CNCommandStack::undoCommand() {
    executedCommands.top()->undo();
    move(executedCommands, undoneCommands);
}

void CNCommandStack::redoCommand() {
    undoneCommands.top()->execute();
    move(undoneCommands, executedCommands);
}

void CNCommandStack::move(std::stack<CNCommandPtr> &from, std::stack<CNCommandPtr> &to) {
    to.push(from.top());
    from.pop();
}

void CNCommandStack::notifyObservers() {
    subject->notifyObservers();
}

