#ifndef QTVIEWS_QTSOLUTIONEXPLORER_H
#define QTVIEWS_QTSOLUTIONEXPLORER_H

#include <qobject.h>

class QItemSelection;
class QTreeView;
class QPushButton;
class QtSolutionModel;
class QtSolutionItem;

class QtSolutionExplorer;
typedef std::shared_ptr<QtSolutionExplorer> QtSolutionExplorerPtr;

class QtSolutionExplorer : public QObject {
public:
    Q_OBJECT
public:
    static QtSolutionExplorerPtr getNewInstance();
    virtual ~QtSolutionExplorer();
private:
    QtSolutionExplorer();

public:
    virtual QWidget* getQWidget();

    virtual std::string getTitle();
    virtual bool isVisible();
    void toggleVisibility();

    virtual void removeIndex(const QModelIndex &index);
    virtual QModelIndex getSelectedIndex();
    virtual void insertItem(std::shared_ptr<QtSolutionItem> item, const QModelIndex &index, int childPos);

private:
    QWidget* widget;
    QPushButton* deselectButton;
    QTreeView* treeView;
    QtSolutionModel* solutionModel;

private slots:
    virtual void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    virtual void onDeselectClicked();
};

#endif //QTVIEWS_QTSOLUTIONEXPLORER_H