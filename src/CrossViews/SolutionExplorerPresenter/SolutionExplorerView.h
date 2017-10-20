#ifndef CROSSVIEWS_SOLUTIONEXPLORERVIEW_H
#define CROSSVIEWS_SOLUTIONEXPLORERVIEW_H

#include <CodeBase/CBTransActionAppearance/CBActionState.h>
#include <CrossNative/CNVisitable/CNVisitable.h>
#include "CrossNative/CNHierarchy/CNHierarchyIndex.h"

class SolutionExplorerView;
typedef std::shared_ptr<SolutionExplorerView> SolutionExplorerViewPtr;

class SolutionExplorerView : public virtual CNVisitable {
public:
    virtual ~SolutionExplorerView() {}

protected:
    SolutionExplorerView() {}

public:
    virtual void removeIndex(const CNHierarchyIndex& index) = 0;
    virtual void insertItem(CNVisitablePtr visitable, const CNHierarchyIndex& parent, int childPos) = 0;
    virtual CNHierarchyIndex getSelectedIndex() = 0;
};

#endif //CROSSVIEWS_SOLUTIONEXPLORERVIEW_H