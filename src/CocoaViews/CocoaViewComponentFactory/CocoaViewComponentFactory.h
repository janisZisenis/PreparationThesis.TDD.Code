#ifndef COCOAVIEWS_COCOAVIEWCOMPONENTFACTORY_H
#define COCOAVIEWS_COCOAVIEWCOMPONENTFACTORY_H

#include <memory>
#include <string>
#include <CodeBase/CBTransActionAppearance/CBActionState.h>

class CBTransAction;
class CBTransActionAppearance;
class CBActionAccessibility;
class CBActionTitle;
class CBActionState;
class CBCommandHistory;
class CBCommandInvoker;

class CNComponent;
class CNVisitable;
class CNComposer;
class CNVisitor;

class SelectionModel;
class HierarchicModelAccess;
class InsertingHierarchicModel;
class CocoaSolutionItemFactory;
class CocoaPropertiesModelFactory;

class MenuEntryView;
class MenuEntryPresenter;

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
    virtual std::shared_ptr<CNComponent> makeUndoActionComponent(std::shared_ptr<CBCommandHistory> commandHistory);
    virtual std::shared_ptr<CNComponent> makeRedoActionComponent(std::shared_ptr<CBCommandHistory> commandHistory);
    virtual std::shared_ptr<CNComponent> makeRemoveActionComponent(std::shared_ptr<SelectionModel> selectionModel,
                                                                   std::shared_ptr<InsertingHierarchicModel> model,
                                                                   std::shared_ptr<CBCommandInvoker> invoker);

protected:
    virtual std::shared_ptr<MenuEntryView> makeMenuEntryView();
    virtual std::shared_ptr<MenuEntryPresenter> makeMenuEntryPresenter(std::shared_ptr<MenuEntryView> view,
                                                                       std::shared_ptr<CBTransActionAppearance> appearance,
                                                                       std::shared_ptr<CBTransAction> action);

    virtual std::shared_ptr<CBTransActionAppearance> makeTransActionAppearance(std::shared_ptr<CBActionAccessibility> accessibility,
                                                                               std::shared_ptr<CBActionState> state,
                                                                               std::shared_ptr<CBActionTitle> title);
    virtual std::shared_ptr<CBTransActionAppearance> makeFixedTransActionAppearance(bool accessibility, CBActionStates state, std::string title);
    virtual std::shared_ptr<CBActionAccessibility> makeFixedActionAcessibility(bool accessibility);
    virtual std::shared_ptr<CBActionAccessibility> makeUndoDependenAccessibility(std::shared_ptr<CBCommandHistory> commandHistory);
    virtual std::shared_ptr<CBActionAccessibility> makeRedoDependenAccessibility(std::shared_ptr<CBCommandHistory> commandHistory);
    virtual std::shared_ptr<CBActionAccessibility> makeSelectionDependenAccessibility(std::shared_ptr<SelectionModel> selectionModel);
    virtual std::shared_ptr<CBActionState> makeFixedActionState(CBActionStates state);
    virtual std::shared_ptr<CBActionTitle> makeFixedActionTitle(std::string title);

    virtual std::shared_ptr<CNComponent> makeComposable(std::shared_ptr<CNVisitable> visitable, std::shared_ptr<CNComposer> composer);
    virtual std::shared_ptr<CNComposer> makeVisitingComposer(std::shared_ptr<CNVisitor> composing, std::shared_ptr<CNVisitor> decomposing);
    virtual std::shared_ptr<CNComposer> makeNullComposer();
};

#endif //COCOAVIEWS_COCOAVIEWCOMPONENTFACTORY_H