#include "CNUndoAction.h"
#include "Base/CNCommandHistory/CNCommandHistory.h"

CNUndoActionPtr CNUndoAction::getNewInstance(CNCommandHistoryPtr commandHistory) {
    return CNUndoActionPtr(new CNUndoAction(commandHistory));
}

CNUndoAction::~CNUndoAction() {

}

CNUndoAction::CNUndoAction(CNCommandHistoryPtr commandHistory) : commandHistory(commandHistory) {}

void CNUndoAction::execute() {
    commandHistory->undo();
}

