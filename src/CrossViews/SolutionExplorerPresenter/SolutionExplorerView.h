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
};

#endif //CROSSVIEWS_SOLUTIONEXPLORERVIEW_H