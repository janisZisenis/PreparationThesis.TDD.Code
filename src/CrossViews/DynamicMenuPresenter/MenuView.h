#ifndef CROSSVIEWS_MENUVIEW_H
#define CROSSVIEWS_MENUVIEW_H

#include <Hierarchies/CNVisitable/CNVisitable.h>

class MenuView;
typedef std::shared_ptr<MenuView> MenuViewPtr;

class MenuView : public virtual CNVisitable {
public:
    virtual ~MenuView() {}
protected:
    MenuView() {}
};

#endif //CROSSVIEWS_MENUVIEW_H