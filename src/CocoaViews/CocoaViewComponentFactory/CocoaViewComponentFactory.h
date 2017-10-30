#ifndef COCOAVIEWS_COCOAVIEWCOMPONENTFACTORY_H
#define COCOAVIEWS_COCOAVIEWCOMPONENTFACTORY_H

#include <memory>
#include <string>
#include <CodeBase/CBTransActionAppearance/CBActionState.h>

class CNActionAppearanceFactory;

class CNTransAction;
class CNTransActionAppearance;
class CNActionAccessibility;
class CNActionTitle;
class CNActionState;
class CNCommandHistory;
class CNCommandInvoker;

class CNComponentFactory;
class CNComposerFactory;
class CNComponent;
class CNVisitable;
class CNComposer;
class CNVisitor;

class SelectionModel;
class HierarchicModelAccess;
class InsertingHierarchicModel;
class CocoaSolutionItemFactory;
class CocoaPropertiesModelFactory;

class DynamicMenuPresenter;
class MenuEntryListProvider;
class MenuView;
class CocoaMenu;
class MenuEntryPresenter;
class MenuEntryView;
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
    virtual std::shared_ptr<CNComponent> makeSolutionExplorerComponent(std::shared_ptr<SelectionModel> selectionModel,
                                                                       std::shared_ptr<HierarchicModelAccess> modelAccess,
                                                                       std::shared_ptr<CocoaSolutionItemFactory> itemFactory);
    virtual std::shared_ptr<CNComponent> makePropertiesExplorerComponent(std::shared_ptr<SelectionModel> selectionModel,
                                                                         std::shared_ptr<HierarchicModelAccess> modelAccess,
                                                                         std::shared_ptr<CocoaPropertiesModelFactory> modelFactory);

    virtual std::shared_ptr<CNComponent> makeMenuBarComponent();
    virtual std::shared_ptr<CNComponent> makeMenuComponent(std::string title, std::string tag);
    virtual std::shared_ptr<CNComponent> makeUndoActionComponent(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual std::shared_ptr<CNComponent> makeRedoActionComponent(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual std::shared_ptr<CNComponent> makeRemoveActionComponent(std::shared_ptr<SelectionModel> selectionModel,
                                                                   std::shared_ptr<InsertingHierarchicModel> model,
                                                                   std::shared_ptr<CNCommandInvoker> invoker);

protected:
    virtual std::shared_ptr<CocoaMenu> makeCocoaMenu(std::string title, std::string tag);
    virtual std::shared_ptr<MenuEntryView> makeMenuEntryView();
    virtual std::shared_ptr<MenuEntryPresenter> makeMenuEntryPresenter(std::shared_ptr<MenuEntryView> view,
                                                                       std::shared_ptr<CNTransActionAppearance> appearance,
                                                                       std::shared_ptr<CNTransAction> action);
    virtual std::shared_ptr<DynamicMenuPresenter> makeDynamicMenuPresenter(std::shared_ptr<MenuView> view,
                                                                           std::shared_ptr<CNComposer> composer,
                                                                           std::shared_ptr<MenuEntryListProvider> listProvider);

    virtual std::shared_ptr<CNTransActionAppearance> makeCBTransActionAppearance(
            std::shared_ptr<CNActionAccessibility> accessibility,
            std::shared_ptr<CNActionState> state,
            std::shared_ptr<CNActionTitle> title);
    virtual std::shared_ptr<CNTransActionAppearance> makeCBFixedTransActionAppearance(bool accessibility,
                                                                                      CNActionStates state,
                                                                                      std::string title);
    virtual std::shared_ptr<CNActionAccessibility> makeUndoDependenAccessibility(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual std::shared_ptr<CNActionAccessibility> makeRedoDependenAccessibility(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual std::shared_ptr<CNActionAccessibility> makeSelectionDependenAccessibility(std::shared_ptr<SelectionModel> selectionModel);
    virtual std::shared_ptr<CNActionState> makeCBFixedActionState(CNActionStates state);
    virtual std::shared_ptr<CNActionTitle> makeCBFixedActionTitle(std::string title);

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