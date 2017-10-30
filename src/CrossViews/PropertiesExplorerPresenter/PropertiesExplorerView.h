#ifndef CROSSVIEWS_PROPERTIESEXPLORERVIEW_H
#define CROSSVIEWS_PROPERTIESEXPLORERVIEW_H

#include <CodeBase/CBTransActionAppearance/CBActionState.h>
#include <Hierarchies/CNVisitable/CNVisitable.h>

class PropertiesExplorerView;
typedef std::shared_ptr<PropertiesExplorerView> PropertiesExplorerViewPtr;

class PropertiesExplorerView : public virtual CNVisitable {
public:
    virtual ~PropertiesExplorerView() {}

protected:
    PropertiesExplorerView() {}

public:
    virtual void displayPropertiesFor(CNVisitablePtr visitable) = 0;
    virtual void displayEmptyProperties() = 0;
};

#endif //CROSSVIEWS_PROPERTIESEXPLORERVIEW_H