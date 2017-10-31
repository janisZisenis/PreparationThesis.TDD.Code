#ifndef COCOAVIEWS_COCOAVIEWCOMPONENTFACTORY_H
#define COCOAVIEWS_COCOAVIEWCOMPONENTFACTORY_H

#include <memory>
#include <string>
#include <Base/TransActionAppearances/CNTransActionAppearanceImp/CNTransActionState.h>

class CNActionAppearanceFactory;

class CNTransAction;
class CNTransActionAppearance;
class CNTransActionAccessibility;
class CNTransActionTitle;
class CNTransActionState;
class CNCommandHistory;
class CNCommandInvoker;

class CNComponentFactory;
class CNComposerFactory;
class CNComponent;
class CNVisitable;
class CNComposer;
class CNVisitor;

class CNSelectionModel;
class CNHierarchicComponentAccess;
class CNComponentInserter;
class CocoaSolutionItemFactory;
class CocoaPropertiesModelFactory;

class CNDynamicMenuPresenter;
class CNVisitableListProvider;
class CNMenuView;
class CocoaMenu;
class CNMenuEntryPresenter;
class CNMenuEntryView;
class CocoaAction;

class CocoaViewComponentFactory;
typedef std::shared_ptr<CocoaViewComponentFactory> CocoaViewComponentFactoryPtr;

class CocoaViewComponentFactory {
public:
    static CocoaViewComponentFactoryPtr getNewInstance();
    virtual ~CocoaViewComponentFactory();
protected:
    CocoaViewComponentFactory();

public:
    virtual std::shared_ptr<CNComponent> makeShellComponent();
    virtual std::shared_ptr<CNComponent> makeSolutionExplorerComponent(std::shared_ptr<CNSelectionModel> selectionModel,
                                                                       std::shared_ptr<CNHierarchicComponentAccess> modelAccess,
                                                                       std::shared_ptr<CocoaSolutionItemFactory> itemFactory);
    virtual std::shared_ptr<CNComponent> makePropertiesExplorerComponent(std::shared_ptr<CNSelectionModel> selectionModel,
                                                                         std::shared_ptr<CNHierarchicComponentAccess> modelAccess,
                                                                         std::shared_ptr<CocoaPropertiesModelFactory> modelFactory);

    virtual std::shared_ptr<CNComponent> makeMenuBarComponent();
    virtual std::shared_ptr<CNComponent> makeMenuComponent(std::string title, std::string tag);
    virtual std::shared_ptr<CNComponent> makeUndoActionComponent(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual std::shared_ptr<CNComponent> makeRedoActionComponent(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual std::shared_ptr<CNComponent> makeRemoveActionComponent(std::shared_ptr<CNSelectionModel> selectionModel,
                                                                   std::shared_ptr<CNComponentInserter> model,
                                                                   std::shared_ptr<CNCommandInvoker> invoker);

protected:
    virtual std::shared_ptr<CocoaMenu> makeCocoaMenu(std::string title, std::string tag);
    virtual std::shared_ptr<CNMenuEntryView> makeMenuEntryView();
    virtual std::shared_ptr<CNMenuEntryPresenter> makeMenuEntryPresenter(std::shared_ptr<CNMenuEntryView> view,
                                                                       std::shared_ptr<CNTransActionAppearance> appearance,
                                                                       std::shared_ptr<CNTransAction> action);
    virtual std::shared_ptr<CNDynamicMenuPresenter> makeDynamicMenuPresenter(std::shared_ptr<CNMenuView> view,
                                                                           std::shared_ptr<CNComposer> composer,
                                                                           std::shared_ptr<CNVisitableListProvider> listProvider);

    virtual std::shared_ptr<CNTransActionAppearance> makeCBTransActionAppearance(
            std::shared_ptr<CNTransActionAccessibility> accessibility,
            std::shared_ptr<CNTransActionState> state,
            std::shared_ptr<CNTransActionTitle> title);
    virtual std::shared_ptr<CNTransActionAppearance> makeCBFixedTransActionAppearance(bool accessibility,
                                                                                      CNTransActionStateValues state,
                                                                                      std::string title);
    virtual std::shared_ptr<CNTransActionAccessibility> makeUndoDependenAccessibility(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual std::shared_ptr<CNTransActionAccessibility> makeRedoDependenAccessibility(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual std::shared_ptr<CNTransActionAccessibility> makeSelectionDependenAccessibility(std::shared_ptr<CNSelectionModel> selectionModel);
    virtual std::shared_ptr<CNTransActionState> makeCBFixedActionState(CNTransActionStateValues state);
    virtual std::shared_ptr<CNTransActionTitle> makeCBFixedActionTitle(std::string title);

    virtual std::shared_ptr<CNComponent> makeCNComposable(std::shared_ptr<CNVisitable> visitable,
                                                          std::shared_ptr<CNComposer> composer);
    virtual std::shared_ptr<CNComposer> makeCNVisitingComposer(std::shared_ptr<CNVisitor> composing,
                                                               std::shared_ptr<CNVisitor> decomposing);
    virtual std::shared_ptr<CNComposer> makeCNNullComposer();

private:
    std::shared_ptr<CNComponentFactory> componentFactory;
    std::shared_ptr<CNComposerFactory> composerFactory;
    std::shared_ptr<CNActionAppearanceFactory> appearanceFactory;
};

#endif //COCOAVIEWS_COCOAVIEWCOMPONENTFACTORY_H