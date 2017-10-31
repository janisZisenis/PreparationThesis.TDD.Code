#ifndef CROSSNATIVE_COMPONENTLISTPROVIDER_TESTDOUBLES_H
#define CROSSNATIVE_COMPONENTLISTPROVIDER_TESTDOUBLES_H

#include "CNVisitableListProvider.h"

class CNComponentListProviderDummy;
typedef std::shared_ptr<CNComponentListProviderDummy> CNComponentListProviderDummyPtr;

class CNComponentListProviderDummy : public CNVisitableListProvider {
public:
    static CNComponentListProviderDummyPtr getNewInstance() {
        return CNComponentListProviderDummyPtr(new CNComponentListProviderDummy());
    }
    virtual ~CNComponentListProviderDummy() {}
protected:
    CNComponentListProviderDummy() {}

public:
    virtual const std::vector< std::shared_ptr<CNVisitable> > getVisitables() {
        return std::vector< std::shared_ptr<CNVisitable> >();
    };
};

class CNComponentListProviderStub;
typedef std::shared_ptr<CNComponentListProviderStub> CNComponentListProviderStubPtr;

class CNComponentListProviderStub : public CNComponentListProviderDummy {
public:
    static CNComponentListProviderStubPtr getNewInstance() {
        return CNComponentListProviderStubPtr(new CNComponentListProviderStub());
    }
    virtual ~CNComponentListProviderStub() {}
protected:
    CNComponentListProviderStub() {}

public:
    virtual void setMenuEntryList(std::vector< std::shared_ptr<CNVisitable> > visitables) {
        this->visitables = visitables;
    }
    virtual const std::vector< std::shared_ptr<CNVisitable> > getMenuEntryList() {
        return visitables;
    };

private:
    std::vector< std::shared_ptr<CNVisitable> > visitables;
};


#endif //CROSSNATIVE_COMPONENTLISTPROVIDER_TESTDOUBLES_H