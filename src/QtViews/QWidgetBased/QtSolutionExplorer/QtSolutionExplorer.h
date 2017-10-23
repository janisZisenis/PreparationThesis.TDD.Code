#ifndef QTVIEWS_QTSOLUTIONEXPLORER_H
#define QTVIEWS_QTSOLUTIONEXPLORER_H

#include <qobject.h>
#include <CrossViews/SolutionExplorerPresenter/SolutionExplorerView.h>
#include "QtViews/QWidgetBased/QWidgetBased.h"

class CNAcceptor;

class QItemSelection;
class QTreeView;
class QPushButton;
class QtSolutionModel;
class QtSolutionItem;
class QtSolutionItemFactory;

class QtSolutionExplorer;
typedef std::shared_ptr<QtSolutionExplorer> QtSolutionExplorerPtr;

class QtSolutionExplorer : public QObject, public QWidgetBased, public SolutionExplorerView, public std::enable_shared_from_this<QtSolutionExplorer> {
public:
    Q_OBJECT
public:
    static QtSolutionExplorerPtr getNewInstance(std::shared_ptr<QtSolutionItemFactory> itemFactory);
    virtual ~QtSolutionExplorer();
private:
    QtSolutionExplorer(std::shared_ptr<QtSolutionItemFactory> itemFactory);

public:
    virtual QWidget* getQWidget() override;
    virtual std::string getTitle() override;

    virtual void removeIndex(const CNHierarchyIndex &index) override;
    virtual CNHierarchyIndex getSelectedIndex() override;
    virtual void insertItem(CNVisitablePtr visitable, const CNHierarchyIndex &index, int childPos) override;

    virtual void accept(CNVisitorPtr visitor) override;
    virtual void setListener(std::shared_ptr<SolutionExplorerListener> listener) override;
private:
    virtual std::shared_ptr<QtSolutionItem> makeItem(CNVisitablePtr visitable);

    QtSolutionExplorerPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;
    std::shared_ptr<SolutionExplorerListener> listener;
    std::shared_ptr<QtSolutionItemFactory> itemFactory;
    QWidget* widget;
    QPushButton* deselectButton;
    QTreeView* treeView;
    QtSolutionModel* solutionModel;

private slots:
    virtual void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    virtual void onDeselectClicked();
};

#endif //QTVIEWS_QTSOLUTIONEXPLORER_H