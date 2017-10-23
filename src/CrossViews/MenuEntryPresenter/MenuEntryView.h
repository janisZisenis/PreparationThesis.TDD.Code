#ifndef CROSSVIEWS_MENUENTRYVIEW_H
#define CROSSVIEWS_MENUENTRYVIEW_H

#include <CodeBase/CBTransActionAppearance/CBActionState.h>
#include <CrossNative/CNVisitable/CNVisitable.h>

class MenuEntryListener;

class MenuEntryView;
typedef std::shared_ptr<MenuEntryView> MenuEntryViewPtr;

class MenuEntryView : public virtual CNVisitable {
public:
    virtual ~MenuEntryView() {}
protected:
    MenuEntryView() {}

public:
    virtual void setTitle(std::string newTitle) = 0;

    virtual void check() = 0;
    virtual void uncheck() = 0;

    virtual void enable() = 0;
    virtual void disable() = 0;

    virtual void setListener(std::shared_ptr<MenuEntryListener> listener) = 0;
};

#endif //CROSSVIEWS_MENUENTRYVIEW_H