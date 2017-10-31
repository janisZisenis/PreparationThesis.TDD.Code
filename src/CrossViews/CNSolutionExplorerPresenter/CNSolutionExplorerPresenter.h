#ifndef CROSSNATIVE_SOLUTIONEXPLORERPRESENTER_H
#define CROSSNATIVE_SOLUTIONEXPLORERPRESENTER_H

#include <Hierarchies/CNVisitable/CNVisitable.h>
#include "CrossViews/CNHierarchicModel/CNHierarchicModelListener.h"
#include "CNSolutionExplorerListener.h"

class CNSolutionExplorerView;
class CNSelectionModel;

class CNSolutionExplorerPresenter;
typedef std::shared_ptr<CNSolutionExplorerPresenter> CNSolutionExplorerPresenterPtr;

class CNSolutionExplorerPresenter : public virtual CNVisitable, public CNHierarchicModelListener, public CNSolutionExplorerListener {
public:
    static CNSolutionExplorerPresenterPtr getNewInstance(std::shared_ptr<CNSolutionExplorerView> view,
                                                       std::shared_ptr<CNSelectionModel> selectionModel);
    virtual ~CNSolutionExplorerPresenter();
private:
    CNSolutionExplorerPresenter(std::shared_ptr<CNSolutionExplorerView> view,
                                std::shared_ptr<CNSelectionModel> selectionModel);

public:
    virtual void accept(CNVisitorPtr visitor) override;

    virtual void onRemove(const CNHierarchyIndex& index) override;
    virtual void onInsert(CNVisitablePtr visitable, const CNHierarchyIndex& index, int childPos) override;

    virtual void onSelectionChanged() override;
private:
    std::shared_ptr<CNSolutionExplorerView> view;
    std::shared_ptr<CNSelectionModel> selectionModel;
};

#endif //CROSSNATIVE_SOLUTIONEXPLORERPRESENTER_H