#ifndef QTVIEWS_QTSOLUTIONEXPLORER_H
#define QTVIEWS_QTSOLUTIONEXPLORER_H

#include <qobject.h>
#include <CrossViews/SolutionExplorerPresenter/SolutionExplorerView.h>
#include "QtViews/QtWidget/QtWidget.h"

class CNAcceptor;

class QItemSelection;
class QTreeView;
class QPushButton;
class QtSolutionModel;
class QtSolutionItem;

class QtSolutionExplorer;
typedef std::shared_ptr<QtSolutionExplorer> QtSolutionExplorerPtr;

class QtSolutionExplorer : public QObject, public QtWidget, public SolutionExplorerView, public std::enable_shared_from_this<QtSolutionExplorer> {
public:
    Q_OBJECT
public:
    static QtSolutionExplorerPtr getNewInstance();
    virtual ~QtSolutionExplorer();
private:
    QtSolutionExplorer();

public:
    virtual QWidget* getQWidget() override;
    virtual std::string getTitle() override;

    virtual void removeIndex(const CNHierarchyIndex &index) override;
    virtual CNHierarchyIndex getSelectedIndex() override;
    virtual void insertItem(CNVisitablePtr visitable, const CNHierarchyIndex &index, int childPos) override;

    virtual void accept(CNVisitorPtr visitor) override;
private:
    virtual std::shared_ptr<QtSolutionItem> makeItem(CNVisitablePtr visitable);

    QtSolutionExplorerPtr me();

private:
    std::shared_ptr<CNAcceptor> acceptor;

    QWidget* widget;
    QPushButton* deselectButton;
    QTreeView* treeView;
    QtSolutionModel* solutionModel;

private slots:
    virtual void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    virtual void onDeselectClicked();
};

#endif //QTVIEWS_QTSOLUTIONEXPLORER_H