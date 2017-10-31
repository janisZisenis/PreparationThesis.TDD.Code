#ifndef CROSSNATIVE_MENUENTRYLISTENER_H
#define CROSSNATIVE_MENUENTRYLISTENER_H

#include <memory>

class CNMenuEntryListener;
typedef std::shared_ptr<CNMenuEntryListener> CNMenuEntryListenerPtr;

class CNMenuEntryListener {
public:
    virtual ~CNMenuEntryListener() {}
protected:
    CNMenuEntryListener() {}

public:
    virtual void onTriggered() = 0;
};

#endif //CROSSNATIVE_MENUENTRYLISTENER_H