#ifndef QTVIEWS_QTVIEWCOMPONENTFACTORY_H
#define QTVIEWS_QTVIEWCOMPONENTFACTORY_H

#include <memory>
#include <string>
#include <Base/CNTransActionAppearance/CNTransActionState.h>

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
class QtSolutionItemFactory;
class QtPropertiesModelFactory;

class CNDynamicMenuPresenter;
class CNComponentListProvider;
class CNMenuView;
class QtMenu;
class MenuEntryPresenter;
class CNMenuEntryView;
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
    virtual std::shared_ptr<CNComponent> makeSolutionExplorerComponent(std::shared_ptr<CNSelectionModel> selectionModel,
                                                                       std::shared_ptr<CNHierarchicComponentAccess> modelAccess,
                                                                       std::shared_ptr<QtSolutionItemFactory> itemFactory);
    virtual std::shared_ptr<CNComponent> makePropertiesExplorerComponent(std::shared_ptr<CNSelectionModel> selectionModel,
                                                                         std::shared_ptr<CNHierarchicComponentAccess> modelAccess,
                                                                         std::shared_ptr<QtPropertiesModelFactory> modelFactory);

    virtual std::shared_ptr<CNComponent> makeMenuBarComponent();
    virtual std::shared_ptr<CNComponent> makeMenuComponent(std::string title, std::string tag);
    virtual std::shared_ptr<CNComponent> makeUndoActionComponent(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual std::shared_ptr<CNComponent> makeRedoActionComponent(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual std::shared_ptr<CNComponent> makeRemoveActionComponent(std::shared_ptr<CNSelectionModel> selectionModel,
                                                                   std::shared_ptr<CNComponentInserter> model,
                                                                   std::shared_ptr<CNCommandInvoker> invoker);

protected:
    virtual std::shared_ptr<QtMenu> makeQtMenu(std::string title, std::string tag);
    virtual std::shared_ptr<QtAction> makeQtAction();
    virtual std::shared_ptr<MenuEntryPresenter> makeMenuEntryPresenter(std::shared_ptr<CNMenuEntryView> view,
                                                                       std::shared_ptr<CNTransActionAppearance> appearance,
                                                                       std::shared_ptr<CNTransAction> action);
    virtual std::shared_ptr<CNDynamicMenuPresenter> makeDynamicMenuPresenter(std::shared_ptr<CNMenuView> view,
                                                                  std::shared_ptr<CNComposer> composer,
                                                                  std::shared_ptr<CNComponentListProvider> listProvider);

    virtual std::shared_ptr<CNTransActionAppearance> makeCBTransActionAppearance(std::shared_ptr<CNTransActionAccessibility> accessibility,
                                                                               std::shared_ptr<CNTransActionState> state,
                                                                               std::shared_ptr<CNTransActionTitle> title);
    virtual std::shared_ptr<CNTransActionAppearance> makeCBFixedTransActionAppearance(bool accessibility, CNTransActionStateValues state, std::string title);

    virtual std::shared_ptr<CNTransActionState> makeCBFixedActionState(CNTransActionStateValues state);
    virtual std::shared_ptr<CNTransActionTitle> makeCBFixedActionTitle(std::string title);

    virtual std::shared_ptr<CNTransActionAccessibility> makeUndoDependenAccessibility(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual std::shared_ptr<CNTransActionAccessibility> makeRedoDependenAccessibility(std::shared_ptr<CNCommandHistory> commandHistory);
    virtual std::shared_ptr<CNTransActionAccessibility> makeSelectionDependenAccessibility(std::shared_ptr<CNSelectionModel> selectionModel);

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

#endif //QTVIEWS_QTVIEWCOMPONENTFACTORY_H