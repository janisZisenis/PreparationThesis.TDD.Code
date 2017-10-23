#include "AddGridGeneratorAction.h"
#include <CodeBase/CBCommandInvoker/CBCommandInvoker.h>
#include <CrossNative/CNComponent/CNComposable/CNComposable.h>
#include <CrossNative/CNMatcher/CNMatcher.h>
#include <CrossNative/CNComposer/CNVisitingComposer/CNVisitingComposer.h>
#include <CrossViews/SelectionModel/SelectionModel.h>
#include <CrossViews/Commands/AddCommand/AddingHierarchicModel.h>
#include <CrossViews/Commands/AddCommand/AddCommand.h>
#include "IRMB/GridGenerator/Implementation/GridGeneratorImp.h"
#include "IRMB/GridGenerator/Visitors/GridGeneratorComposingVisitor.h"
#include "IRMB/GridGenerator/Visitors/GridGeneratorDecomposingVisitor.h"

AddGridGeneratorActionPtr AddGridGeneratorAction::getNewInstance(CBCommandInvokerPtr invoker,
                                                                 AddingHierarchicModelPtr model,
                                                                 SelectionModelPtr selectionModel,
                                                                 CNMatcherPtr matcher) {
    return AddGridGeneratorActionPtr(new AddGridGeneratorAction(invoker, model, selectionModel, matcher));
}

AddGridGeneratorAction::~AddGridGeneratorAction() {}

AddGridGeneratorAction::AddGridGeneratorAction(CBCommandInvokerPtr invoker,
                                               AddingHierarchicModelPtr model,
                                               SelectionModelPtr selectionModel,
                                               CNMatcherPtr matcher)
        : invoker(invoker), model(model), selectionModel(selectionModel), matcher(matcher) {}

void AddGridGeneratorAction::execute() {
    CNHierarchyIndex insertingIndex;

    if(selectionModel->hasSelection() && matcher->matches(model->retrieve(selectionModel->getSelectedIndex())))
        insertingIndex = selectionModel->getSelectedIndex();

    CBCommandPtr command = makeCommand(model, insertingIndex, makeGridGeneratorComponent());
    invoker->invoke(command);
}

CNComponentPtr AddGridGeneratorAction::makeGridGeneratorComponent() {
    static int i;

    GridGeneratorPtr gridGenerator = GridGeneratorImp::getNewInstance("MyFancyGridGenerator (" + std::to_string(i++) + ")", 10, 10, 10, 1, "D3Q7");
    GridGeneratorComposingVisitorPtr composingVisitor = GridGeneratorComposingVisitor::getNewInstance(gridGenerator);
    GridGeneratorDecomposingVisitorPtr decomposingVisitor = GridGeneratorDecomposingVisitor::getNewInstance(gridGenerator);
    CNComposerPtr composer = CNVisitingComposer::getNewInstance(composingVisitor, decomposingVisitor);

    return makeComposable(gridGenerator, composer);
}

CBCommandPtr AddGridGeneratorAction::makeCommand(AddingHierarchicModelPtr model, CNHierarchyIndex index, CNComponentPtr component) {
    return AddCommand::getNewInstance(model, index, component);
}

CNComponentPtr AddGridGeneratorAction::makeComposable(CNVisitablePtr visitable, CNComposerPtr composer) {
    return CNComposable::getNewInstance(visitable, composer);
}

