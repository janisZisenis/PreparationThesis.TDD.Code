#ifndef CROSSVIEWS_MENUENTRYLISTPROVIDER_H
#define CROSSVIEWS_MENUENTRYLISTPROVIDER_H

#include <memory>
#include <vector>

class CNVisitable;

class MenuEntryListProvider;
typedef std::shared_ptr<MenuEntryListProvider> MenuEntryListProviderPtr;

class MenuEntryListProvider {
public:
    virtual ~MenuEntryListProvider() {}
protected:
    MenuEntryListProvider() {}

public:
    virtual std::vector< std::shared_ptr<CNVisitable> > getMenuEntryList() = 0;
};

#endif //CROSSVIEWS_MENUENTRYLISTPROVIDER_H