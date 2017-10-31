#ifndef CROSSNATIVE_MENUENTRYVIEW_H
#define CROSSNATIVE_MENUENTRYVIEW_H

#include <Base/TransActionAppearances/CNTransActionAppearanceImp/CNTransActionState.h>
#include <Hierarchies/CNVisitable/CNVisitable.h>

class CNMenuEntryListener;

class CNMenuEntryView;
typedef std::shared_ptr<CNMenuEntryView> CNMenuEntryViewPtr;

class CNMenuEntryView : public virtual CNVisitable {
public:
    virtual ~CNMenuEntryView() {}
protected:
    CNMenuEntryView() {}

public:
    virtual void setTitle(std::string newTitle) = 0;

    virtual void check() = 0;
    virtual void uncheck() = 0;

    virtual void enable() = 0;
    virtual void disable() = 0;

    virtual void setListener(std::shared_ptr<CNMenuEntryListener> listener) = 0;
};

#endif //CROSSNATIVE_MENUENTRYVIEW_H