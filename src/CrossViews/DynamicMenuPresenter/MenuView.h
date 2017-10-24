#ifndef CROSSVIEWS_MENUVIEW_H
#define CROSSVIEWS_MENUVIEW_H

#include <CrossNative/CNVisitable/CNVisitable.h>

class MenuView;
typedef std::shared_ptr<MenuView> MenuViewPtr;

class MenuView : public virtual CNVisitable {
public:
    virtual ~MenuView() {}
protected:
    MenuView() {}

public:
    virtual void clear() = 0;
};

#endif //CROSSVIEWS_MENUVIEW_H