#include "CNRedoAction.h"
#include "Base/CNCommandHistory/CNCommandHistory.h"

CNRedoActionPtr CNRedoAction::getNewInstance(CNCommandHistoryPtr commandHistory) {
    return CNRedoActionPtr(new CNRedoAction(commandHistory));
}

CNRedoAction::~CNRedoAction() {}

CNRedoAction::CNRedoAction(CNCommandHistoryPtr commandHistory) : commandHistory(commandHistory) {}

void CNRedoAction::execute() {
    commandHistory->redo();
}

