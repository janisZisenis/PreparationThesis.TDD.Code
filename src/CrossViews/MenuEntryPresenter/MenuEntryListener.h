#ifndef CROSSVIEWS_MENUENTRYLISTENER_H
#define CROSSVIEWS_MENUENTRYLISTENER_H

#include <memory>

class MenuEntryListener;
typedef std::shared_ptr<MenuEntryListener> MenuEntryListenerPtr;

class MenuEntryListener {
public:
    virtual ~MenuEntryListener() {}
protected:
    MenuEntryListener() {}

public:
    virtual void onTriggered() = 0;
};

#endif //CROSSVIEWS_MENUENTRYLISTENER_H