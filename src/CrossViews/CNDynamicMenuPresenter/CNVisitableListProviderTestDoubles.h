#ifndef CROSSNATIVE_VISITABLELISTPROVIDER_TESTDOUBLES_H
#define CROSSNATIVE_VISITABLELISTPROVIDER_TESTDOUBLES_H

#include "CNVisitableListProvider.h"

class CNVisitableListProviderDummy;
typedef std::shared_ptr<CNVisitableListProviderDummy> CNVisitableListProviderDummyPtr;

class CNVisitableListProviderDummy : public CNVisitableListProvider {
public:
    static CNVisitableListProviderDummyPtr getNewInstance() {
        return CNVisitableListProviderDummyPtr(new CNVisitableListProviderDummy());
    }
    virtual ~CNVisitableListProviderDummy() {}
protected:
    CNVisitableListProviderDummy() {}

public:
    virtual const std::vector< std::shared_ptr<CNVisitable> > getVisitables() {
        return std::vector< std::shared_ptr<CNVisitable> >();
    };
};

class CNVisitableListProviderStub;
typedef std::shared_ptr<CNVisitableListProviderStub> CNVisitableListProviderStubPtr;

class CNVisitableListProviderStub : public CNVisitableListProviderDummy {
public:
    static CNVisitableListProviderStubPtr getNewInstance() {
        return CNVisitableListProviderStubPtr(new CNVisitableListProviderStub());
    }
    virtual ~CNVisitableListProviderStub() {}
protected:
    CNVisitableListProviderStub() {}

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


#endif //CROSSNATIVE_VISITABLELISTPROVIDER_TESTDOUBLES_H