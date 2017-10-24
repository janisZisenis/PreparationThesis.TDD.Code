#ifndef CROSSVIEWS_MENUENTRYLISTPROVIDER_TESTDOUBLES_H
#define CROSSVIEWS_MENUENTRYLISTPROVIDER_TESTDOUBLES_H

#include "MenuEntryListProvider.h"

class MenuEntryListProviderDummy;
typedef std::shared_ptr<MenuEntryListProviderDummy> MenuEntryListProviderDummyPtr;

class MenuEntryListProviderDummy : public MenuEntryListProvider {
public:
    static MenuEntryListProviderDummyPtr getNewInstance() {
        return MenuEntryListProviderDummyPtr(new MenuEntryListProviderDummy());
    }
    virtual ~MenuEntryListProviderDummy() {}
protected:
    MenuEntryListProviderDummy() {}

public:
    virtual std::vector< std::shared_ptr<CNVisitable> > getMenuEntryList() {
        return std::vector< std::shared_ptr<CNVisitable> >();
    };
};

class MenuEntryListProviderStub;
typedef std::shared_ptr<MenuEntryListProviderStub> MenuEntryListProviderStubPtr;

class MenuEntryListProviderStub : public MenuEntryListProviderDummy {
public:
    static MenuEntryListProviderStubPtr getNewInstance() {
        return MenuEntryListProviderStubPtr(new MenuEntryListProviderStub());
    }
    virtual ~MenuEntryListProviderStub() {}
protected:
    MenuEntryListProviderStub() {}

public:
    virtual void addMenuEntryList(std::shared_ptr<CNVisitable> visitable) {
        visitables.push_back(visitable);
    }
    virtual std::vector< std::shared_ptr<CNVisitable> > getMenuEntryList() {
        return visitables;
    };

private:
    std::vector< std::shared_ptr<CNVisitable> > visitables;
};


#endif //CROSSVIEWS_MENUENTRYLISTPROVIDER_TESTDOUBLES_H