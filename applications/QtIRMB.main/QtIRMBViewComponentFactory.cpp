#include "QtIRMBViewComponentFactory.h"
#include <IRMB/TransActions/AddSTLFileAction/AddSTLFileAction.h>
#include <IRMB/TransActions/AddGridGeneratorAction/AddGridGeneratorAction.h>
#include <CrossViews/MenuEntryPresenter/MenuEntryPresenter.h>

QtIRMBViewComponentFactoryPtr QtIRMBViewComponentFactory::getNewInstance() {
    return QtIRMBViewComponentFactoryPtr(new QtIRMBViewComponentFactory());
}
QtIRMBViewComponentFactory::~QtIRMBViewComponentFactory() {}
QtIRMBViewComponentFactory::QtIRMBViewComponentFactory() {}

std::shared_ptr<CNComponent> QtIRMBViewComponentFactory::makeAddSTLFileActionComponent(std::shared_ptr<CBCommandInvoker> invoker,
                                                          std::shared_ptr<AddingHierarchicModel> model,
                                                          std::shared_ptr<SelectionModel> selectionModel,
                                                          std::shared_ptr<CNMatcher> matcher,
                                                          std::shared_ptr<FileFinder> fileFinder) {
    std::shared_ptr<MenuEntryView> view = makeMenuEntryView();
    std::shared_ptr<CBTransActionAppearance> appearance = makeFixedTransActionAppearance(true, OFF, "STL File");
    CBTransActionPtr action = AddSTLFileAction::getNewInstance(invoker, model, selectionModel, matcher, fileFinder);
    std::shared_ptr<MenuEntryPresenter> presenter = makeMenuEntryPresenter(view, appearance, action);
    std::shared_ptr<CNComposer> composer = makeNullComposer();

    return makeComposable(presenter, composer);
}

std::shared_ptr<CNComponent> QtIRMBViewComponentFactory::makeGridGeneratorActionComponent(std::shared_ptr<CBCommandInvoker> invoker,
                                                                                          std::shared_ptr<AddingHierarchicModel> model,
                                                                                          std::shared_ptr<SelectionModel> selectionModel,
                                                                                          std::shared_ptr<CNMatcher> matcher) {
    std::shared_ptr<MenuEntryView> view = makeMenuEntryView();
    std::shared_ptr<CBTransActionAppearance> appearance = makeFixedTransActionAppearance(true, OFF, "Grid Generator");
    CBTransActionPtr action = AddGridGeneratorAction::getNewInstance(invoker, model, selectionModel, matcher);
    std::shared_ptr<MenuEntryPresenter> presenter = makeMenuEntryPresenter(view, appearance, action);
    std::shared_ptr<CNComposer> composer = makeNullComposer();

    return makeComposable(presenter, composer);
}