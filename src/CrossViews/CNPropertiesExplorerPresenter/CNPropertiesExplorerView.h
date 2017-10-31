#ifndef CROSSNATIVE_PROPERTIESEXPLORERVIEW_H
#define CROSSNATIVE_PROPERTIESEXPLORERVIEW_H

#include <Base/CNTransActionAppearance/CNTransActionState.h>
#include <Hierarchies/CNVisitable/CNVisitable.h>

class CNPropertiesExplorerView;
typedef std::shared_ptr<CNPropertiesExplorerView> CNPropertiesExplorerViewPtr;

class CNPropertiesExplorerView : public virtual CNVisitable {
public:
    virtual ~CNPropertiesExplorerView() {}

protected:
    CNPropertiesExplorerView() {}

public:
    virtual void displayPropertiesFor(CNVisitablePtr visitable) = 0;
    virtual void displayEmptyProperties() = 0;
};

#endif //CROSSNATIVE_PROPERTIESEXPLORERVIEW_H