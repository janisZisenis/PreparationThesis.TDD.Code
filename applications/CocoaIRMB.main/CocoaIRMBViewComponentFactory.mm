#include "CocoaIRMBViewComponentFactory.h"
#include <IRMB/TransActions/AddSTLFileAction/AddSTLFileAction.h>
#include <IRMB/TransActions/AddGridGeneratorAction/AddGridGeneratorAction.h>
#include <CrossViews/MenuEntryPresenter/MenuEntryPresenter.h>

CocoaIRMBViewComponentFactoryPtr CocoaIRMBViewComponentFactory::getNewInstance() {
    return CocoaIRMBViewComponentFactoryPtr(new CocoaIRMBViewComponentFactory());
}
CocoaIRMBViewComponentFactory::~CocoaIRMBViewComponentFactory() {}
CocoaIRMBViewComponentFactory::CocoaIRMBViewComponentFactory() {}

std::shared_ptr<CNComponent> CocoaIRMBViewComponentFactory::makeAddSTLFileActionComponent(std::shared_ptr<CBCommandInvoker> invoker,
                                                          std::shared_ptr<AddingHierarchicModel> model,
                                                          std::shared_ptr<SelectionModel> selectionModel,
                                                          std::shared_ptr<CNMatcher> matcher,
                                                          std::shared_ptr<FileFinder> fileFinder) {
    std::shared_ptr<MenuEntryView> view = makeMenuEntryView();
    std::shared_ptr<CBTransActionAppearance> appearance = makeCBFixedTransActionAppearance(true, OFF, "STL File");
    CBTransActionPtr action = AddSTLFileAction::getNewInstance(invoker, model, selectionModel, matcher, fileFinder);
    std::shared_ptr<MenuEntryPresenter> presenter = makeMenuEntryPresenter(view, appearance, action);
    std::shared_ptr<CNComposer> composer = makeNullComposer();

    return makeCNComposable(presenter, composer);
}

std::shared_ptr<CNComponent> CocoaIRMBViewComponentFactory::makeGridGeneratorActionComponent(std::shared_ptr<CBCommandInvoker> invoker,
                                                                                             std::shared_ptr<AddingHierarchicModel> model,
                                                                                             std::shared_ptr<SelectionModel> selectionModel,
                                                                                             std::shared_ptr<CNMatcher> matcher) {
    std::shared_ptr<MenuEntryView> view = makeMenuEntryView();
    std::shared_ptr<CBTransActionAppearance> appearance = makeCBFixedTransActionAppearance(true, OFF, "Grid Generator");
    CBTransActionPtr action = AddGridGeneratorAction::getNewInstance(invoker, model, selectionModel, matcher);
    std::shared_ptr<MenuEntryPresenter> presenter = makeMenuEntryPresenter(view, appearance, action);
    std::shared_ptr<CNComposer> composer = makeNullComposer();

    return makeCNComposable(presenter, composer);
}
