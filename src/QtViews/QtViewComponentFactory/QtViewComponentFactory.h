#ifndef QTVIEWS_QTVIEWCOMPONENTFACTORY_H
#define QTVIEWS_QTVIEWCOMPONENTFACTORY_H

#include <memory>
#include <string>
#include <CodeBase/CBTransActionAppearance/CBActionState.h>

class CBActionAppearanceFactory;

class CBTransAction;
class CBTransActionAppearance;
class CBActionAccessibility;
class CBActionTitle;
class CBActionState;
class CBCommandHistory;
class CBCommandInvoker;

class CNComponentFactory;
class CNComposerFactory;
class CNComponent;
class CNVisitable;
class CNComposer;
class CNVisitor;

class SelectionModel;
class HierarchicModelAccess;
class InsertingHierarchicModel;
class QtSolutionItemFactory;
class QtPropertiesModelFactory;

class DynamicMenuPresenter;
class MenuEntryListProvider;
class MenuView;
class QtMenu;
class MenuEntryPresenter;
class MenuEntryView;
class QtAction;

class QtViewComponentFactory;
typedef std::shared_ptr<QtViewComponentFactory> QtViewComponentFactoryPtr;

class QtViewComponentFactory {
public:
    static QtViewComponentFactoryPtr getNewInstance();
    virtual ~QtViewComponentFactory();
protected:
    QtViewComponentFactory();

public:
    virtual std::shared_ptr<CNComponent> makeShellComponent();
    virtual std::shared_ptr<CNComponent> makeSolutionExplorerComponent(std::shared_ptr<SelectionModel> selectionModel,
                                                                       std::shared_ptr<HierarchicModelAccess> modelAccess,
                                                                       std::shared_ptr<QtSolutionItemFactory> itemFactory);
    virtual std::shared_ptr<CNComponent> makePropertiesExplorerComponent(std::shared_ptr<SelectionModel> selectionModel,
                                                                         std::shared_ptr<HierarchicModelAccess> modelAccess,
                                                                         std::shared_ptr<QtPropertiesModelFactory> modelFactory);

    virtual std::shared_ptr<CNComponent> makeMenuBarComponent();
    virtual std::shared_ptr<CNComponent> makeMenuComponent(std::string title, std::string tag);
    virtual std::shared_ptr<CNComponent> makeUndoActionComponent(std::shared_ptr<CBCommandHistory> commandHistory);
    virtual std::shared_ptr<CNComponent> makeRedoActionComponent(std::shared_ptr<CBCommandHistory> commandHistory);
    virtual std::shared_ptr<CNComponent> makeRemoveActionComponent(std::shared_ptr<SelectionModel> selectionModel,
                                                                   std::shared_ptr<InsertingHierarchicModel> model,
                                                                   std::shared_ptr<CBCommandInvoker> invoker);

protected:
    virtual std::shared_ptr<QtMenu> makeQtMenu(std::string title, std::string tag);
    virtual std::shared_ptr<QtAction> makeQtAction();
    virtual std::shared_ptr<MenuEntryPresenter> makeMenuEntryPresenter(std::shared_ptr<MenuEntryView> view,
                                                                       std::shared_ptr<CBTransActionAppearance> appearance,
                                                                       std::shared_ptr<CBTransAction> action);
    virtual std::shared_ptr<DynamicMenuPresenter> makeDynamicMenuPresenter(std::shared_ptr<MenuView> view,
                                                                  std::shared_ptr<CNComposer> composer,
                                                                  std::shared_ptr<MenuEntryListProvider> listProvider);

    virtual std::shared_ptr<CBTransActionAppearance> makeCBTransActionAppearance(std::shared_ptr<CBActionAccessibility> accessibility,
                                                                               std::shared_ptr<CBActionState> state,
                                                                               std::shared_ptr<CBActionTitle> title);
    virtual std::shared_ptr<CBTransActionAppearance> makeCBFixedTransActionAppearance(bool accessibility, CBActionStates state, std::string title);

    virtual std::shared_ptr<CBActionState> makeCBFixedActionState(CBActionStates state);
    virtual std::shared_ptr<CBActionTitle> makeCBFixedActionTitle(std::string title);

    virtual std::shared_ptr<CBActionAccessibility> makeUndoDependenAccessibility(std::shared_ptr<CBCommandHistory> commandHistory);
    virtual std::shared_ptr<CBActionAccessibility> makeRedoDependenAccessibility(std::shared_ptr<CBCommandHistory> commandHistory);
    virtual std::shared_ptr<CBActionAccessibility> makeSelectionDependenAccessibility(std::shared_ptr<SelectionModel> selectionModel);

    virtual std::shared_ptr<CNComponent> makeCNComposable(std::shared_ptr<CNVisitable> visitable,
                                                          std::shared_ptr<CNComposer> composer);
    virtual std::shared_ptr<CNComposer> makeCNVisitingComposer(std::shared_ptr<CNVisitor> composing,
                                                               std::shared_ptr<CNVisitor> decomposing);
    virtual std::shared_ptr<CNComposer> makeCNNullComposer();

private:
    std::shared_ptr<CNComponentFactory> componentFactory;
    std::shared_ptr<CNComposerFactory> composerFactory;
    std::shared_ptr<CBActionAppearanceFactory> appearanceFactory;
};

#endif //QTVIEWS_QTVIEWCOMPONENTFACTORY_H