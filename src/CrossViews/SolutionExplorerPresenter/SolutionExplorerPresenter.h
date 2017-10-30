#ifndef CROSSVIEWS_SOLUTIONEXPLORERPRESENTER_H
#define CROSSVIEWS_SOLUTIONEXPLORERPRESENTER_H

#include <Hierarchies/CNVisitable/CNVisitable.h>
#include "CrossViews/HierarchicModel/HierarchicModelListener.h"
#include "SolutionExplorerListener.h"

class SolutionExplorerView;
class SelectionModel;

class SolutionExplorerPresenter;
typedef std::shared_ptr<SolutionExplorerPresenter> SolutionExplorerPresenterPtr;

class SolutionExplorerPresenter : public virtual CNVisitable, public HierarchicModelListener, public SolutionExplorerListener {
public:
    static SolutionExplorerPresenterPtr getNewInstance(std::shared_ptr<SolutionExplorerView> view,
                                                       std::shared_ptr<SelectionModel> selectionModel);
    virtual ~SolutionExplorerPresenter();
private:
    SolutionExplorerPresenter(std::shared_ptr<SolutionExplorerView> view,
                              std::shared_ptr<SelectionModel> selectionModel);

public:
    virtual void accept(CNVisitorPtr visitor) override;

    virtual void onRemove(const CNHierarchyIndex& index) override;
    virtual void onInsert(CNVisitablePtr visitable, const CNHierarchyIndex& index, int childPos) override;

    virtual void onSelectionChanged() override;
private:
    std::shared_ptr<SolutionExplorerView> view;
    std::shared_ptr<SelectionModel> selectionModel;
};

#endif //CROSSVIEWS_SOLUTIONEXPLORERPRESENTER_H