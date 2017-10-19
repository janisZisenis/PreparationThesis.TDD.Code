#ifndef CROSSVIEWS_MENUENTRYVIEW_H
#define CROSSVIEWS_MENUENTRYVIEW_H

#include <CodeBase/CBTransActionAppearance/CBActionState.h>
#include <CrossNative/CNVisitable/CNVisitable.h>

class MenuEntryView;
typedef std::shared_ptr<MenuEntryView> MenuEntryViewPtr;

class MenuEntryView : public virtual CNVisitable {
public:
    virtual ~MenuEntryView() {}
protected:
    MenuEntryView() {}

public:
    virtual void setAccessibility(bool newAccessibility) = 0;
    virtual void setState(CBActionStates newState) = 0;
    virtual void setTitle(std::string newTitle) = 0;
};

#endif //CROSSVIEWS_MENUENTRYVIEW_H