#include "AddSTLFileAction.h"

#include <CodeBase/CBCommandInvoker/CBCommandInvoker.h>
#include <CrossNative/CNMatcher/CNMatcher.h>
#include <CrossNative/CNComposer/CNNullComposer.h>
#include <CrossNative/CNComponent/CNComposable/CNComposable.h>
#include <CrossViews/Commands/AddCommand/AddingHierarchicModel.h>
#include <CrossViews/Commands/AddCommand/AddCommand.h>
#include <CrossViews/SelectionModel/SelectionModel.h>

#include "IRMB/STLFile/Implementation/STLFileImp.h"
#include "FileFinder.h"


AddSTLFileActionPtr AddSTLFileAction::getNewInstance(CBCommandInvokerPtr invoker,
                                                     AddingHierarchicModelPtr model,
                                                     SelectionModelPtr selectionModel,
                                                     CNMatcherPtr matcher,
                                                     FileFinderPtr fileFinder) {
    return AddSTLFileActionPtr(new AddSTLFileAction(invoker, model, selectionModel, matcher, fileFinder));
}

AddSTLFileAction::~AddSTLFileAction() {}

AddSTLFileAction::AddSTLFileAction(CBCommandInvokerPtr invoker,
                                   AddingHierarchicModelPtr model,
                                   SelectionModelPtr selectionModel,
                                   CNMatcherPtr matcher,
                                   FileFinderPtr fileFinder)
        : invoker(invoker),
          model(model),
          selectionModel(selectionModel),
          matcher(matcher),
          fileFinder(fileFinder) {}

void AddSTLFileAction::execute() {
    CNHierarchyIndex insertingIndex;
    if(selectionModel->hasSelection() && matcher->matches(model->retrieve(selectionModel->getSelectedIndex())))
        insertingIndex = selectionModel->getSelectedIndex();

    if(fileFinder->findFile())
        invoker->invoke(makeCommand(model, insertingIndex, makeSTLFileComponent(fileFinder->getFileName())));
//        invoker->invoke(makeCommand(model, insertingIndex, makeSTLFilePair("/Users/Janis/GridGeneratorLight/DATA/STL_OUTPUT/cube/cube_binary_edge_1_5.stl")));
}

CNComponentPtr AddSTLFileAction::makeSTLFileComponent(std::string fileName) {
    STLFilePtr stlFile = STLFileImp::getNewInstance(fileName);
    CNComposerPtr composer = CNNullComposer::getNewInstance();

    return makeComposable(stlFile, composer);
}

CBCommandPtr AddSTLFileAction::makeCommand(AddingHierarchicModelPtr model, CNHierarchyIndex index, CNComponentPtr component) {
    return AddCommand::getNewInstance(model, index, component);
}

CNComponentPtr AddSTLFileAction::makeComposable(CNVisitablePtr visitable, CNComposerPtr composer) {
    return CNComposable::getNewInstance(visitable, composer);
}

