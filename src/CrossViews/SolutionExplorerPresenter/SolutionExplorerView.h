#ifndef CROSSVIEWS_SOLUTIONEXPLORERVIEW_H
#define CROSSVIEWS_SOLUTIONEXPLORERVIEW_H

#include <CodeBase/CBTransActionAppearance/CBActionState.h>
#include <CrossNative/CNVisitable/CNVisitable.h>
#include "HierarchyIndex.h"

class SolutionExplorerView;
typedef std::shared_ptr<SolutionExplorerView> SolutionExplorerViewPtr;

class SolutionExplorerView : public virtual CNVisitable {
public:
    virtual ~SolutionExplorerView() {}

protected:
    SolutionExplorerView() {}

public:
    virtual void removeIndex(const HierarchyIndex& index) = 0;
    virtual void insertItem(CNVisitablePtr visitable, const HierarchyIndex& parent, int childPos) = 0;
};

#endif //CROSSVIEWS_SOLUTIONEXPLORERVIEW_H