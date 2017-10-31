#ifndef CROSSNATIVE_SOLUTIONEXPLORERVIEW_H
#define CROSSNATIVE_SOLUTIONEXPLORERVIEW_H

#include <Base/CNTransActionAppearance/CNTransActionState.h>
#include <Hierarchies/CNVisitable/CNVisitable.h>
#include <Hierarchies/CNHierarchy/CNHierarchyIndex.h>

class CNSolutionExplorerListener;

class CNSolutionExplorerView;
typedef std::shared_ptr<CNSolutionExplorerView> CNSolutionExplorerViewPtr;

class CNSolutionExplorerView : public virtual CNVisitable {
public:
    virtual ~CNSolutionExplorerView() {}

protected:
    CNSolutionExplorerView() {}

public:
    virtual void removeIndex(const CNHierarchyIndex& index) = 0;
    virtual void insertItem(CNVisitablePtr visitable, const CNHierarchyIndex& parent, int childPos) = 0;
    virtual CNHierarchyIndex getSelectedIndex() = 0;

    virtual void setListener(std::shared_ptr<CNSolutionExplorerListener> listener) = 0;
};

#endif //CROSSNATIVE_SOLUTIONEXPLORERVIEW_H