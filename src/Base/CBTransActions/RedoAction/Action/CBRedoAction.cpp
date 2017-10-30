#include "CBRedoAction.h"
#include "Base/CBCommandHistory/CBCommandHistory.h"

CBRedoActionPtr CBRedoAction::getNewInstance(CBCommandHistoryPtr commandHistory) {
    return CBRedoActionPtr(new CBRedoAction(commandHistory));
}

CBRedoAction::~CBRedoAction() {}

CBRedoAction::CBRedoAction(CBCommandHistoryPtr commandHistory) : commandHistory(commandHistory) {}

void CBRedoAction::execute() {
    commandHistory->redo();
}

