#include "CBUndoAction.h"
#include "Base/CBCommandHistory/CBCommandHistory.h"

CBUndoActionPtr CBUndoAction::getNewInstance(CBCommandHistoryPtr commandHistory) {
    return CBUndoActionPtr(new CBUndoAction(commandHistory));
}

CBUndoAction::~CBUndoAction() {

}

CBUndoAction::CBUndoAction(CBCommandHistoryPtr commandHistory) : commandHistory(commandHistory) {}

void CBUndoAction::execute() {
    commandHistory->undo();
}

