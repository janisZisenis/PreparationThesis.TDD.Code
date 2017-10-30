#include "CBCommandStack.h"
#include "Base/CBCommand/CBCommand.h"
#include "Base/CBObserver/CBObserver.h"
#include "Base/CBSubject/CBSubject.h"

CBCommandStackPtr CBCommandStack::getNewInstance() {
    return CBCommandStackPtr(new CBCommandStack());
}

CBCommandStack::~CBCommandStack() {}

CBCommandStack::CBCommandStack() : subject(CBSubject::getNewInstance()) {}

void CBCommandStack::invoke(CBCommandPtr command) {
    removeUndoneCommands();

    executeCommand(command);

    notifyObservers();
}

void CBCommandStack::undo() {
    if(!undoIsPossible()) throw CBNoExecutedCommandsException();

    undoCommand();

    notifyObservers();
}

void CBCommandStack::redo() {
    if(!redoIsPossible()) throw CBNoUndoneCommandsException();

    redoCommand();

    notifyObservers();
}

bool CBCommandStack::undoIsPossible() {
    return !executedCommands.empty();
}

bool CBCommandStack::redoIsPossible() {
    return !undoneCommands.empty();
}

void CBCommandStack::attach(CBObserverPtr observer) {
    subject->attach(observer);
}

void CBCommandStack::detach(CBObserverPtr observer) {
    subject->detach(observer);
}

void CBCommandStack::removeUndoneCommands() {
    undoneCommands = std::stack<CBCommandPtr>();
}

void CBCommandStack::executeCommand(std::shared_ptr<CBCommand> command) {
    executedCommands.push(command);
    command->execute();
}

void CBCommandStack::undoCommand() {
    executedCommands.top()->undo();
    move(executedCommands, undoneCommands);
}

void CBCommandStack::redoCommand() {
    undoneCommands.top()->execute();
    move(undoneCommands, executedCommands);
}

void CBCommandStack::move(std::stack<CBCommandPtr> &from, std::stack<CBCommandPtr> &to) {
    to.push(from.top());
    from.pop();
}

void CBCommandStack::notifyObservers() {
    subject->notifyObservers();
}

