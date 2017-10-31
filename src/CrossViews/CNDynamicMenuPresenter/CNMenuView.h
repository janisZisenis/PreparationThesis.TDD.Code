#ifndef CROSSNATIVE_MENUVIEW_H
#define CROSSNATIVE_MENUVIEW_H

#include <Hierarchies/CNVisitable/CNVisitable.h>

class CNMenuView;
typedef std::shared_ptr<CNMenuView> CNMenuViewPtr;

class CNMenuView : public virtual CNVisitable {
public:
    virtual ~CNMenuView() {}
protected:
    CNMenuView() {}
};

#endif //CROSSNATIVE_MENUVIEW_H