#ifndef CROSSVIEWS_SOLUTIONEXPLORERPRESENTER_H
#define CROSSVIEWS_SOLUTIONEXPLORERPRESENTER_H

#include <CodeBase/CBObserver/CBObserver.h>
#include <CrossNative/CNVisitable/CNVisitable.h>

#include "HierarchyIndex.h"

class SolutionExplorerView;

class SolutionExplorerPresenter;
typedef std::shared_ptr<SolutionExplorerPresenter> SolutionExplorerPresenterPtr;

class SolutionExplorerPresenter : public virtual CNVisitable {
public:
    static SolutionExplorerPresenterPtr getNewInstance(std::shared_ptr<SolutionExplorerView> view);
    virtual ~SolutionExplorerPresenter();
private:
    SolutionExplorerPresenter(std::shared_ptr<SolutionExplorerView> view);

public:
    virtual void accept(CNVisitorPtr visitor) override;

    virtual void onRemove(const HierarchyIndex& index);
private:
    std::shared_ptr<SolutionExplorerView> view;
};

#endif //CROSSVIEWS_SOLUTIONEXPLORERPRESENTER_H