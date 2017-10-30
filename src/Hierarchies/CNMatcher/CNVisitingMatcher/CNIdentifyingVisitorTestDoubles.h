#ifndef CROSSNATIVE_IDENTIFYINGVISITOR_TESTDOUBLES_H
#define CROSSNATIVE_IDENTIFYINGVISITOR_TESTDOUBLES_H

#include "CNIdentifyingVisitor.h"

class CNIdentifyingVisitorDummy;
typedef std::shared_ptr<CNIdentifyingVisitorDummy> CNIdentifyingVisitorDummyPtr;
class CNIdentifyingVisitorDummy : public CNIdentifyingVisitor {
public:
    static CNIdentifyingVisitorDummyPtr getNewInstance() {
        return CNIdentifyingVisitorDummyPtr(new CNIdentifyingVisitorDummy());
    };

    virtual ~CNIdentifyingVisitorDummy() {};
private:
    CNIdentifyingVisitorDummy() {};

public:
    virtual bool hasIdentified() override {
        return false;
    }
};

class CNIdentifyingVisitorStub;
typedef std::shared_ptr<CNIdentifyingVisitorStub> CNIdentifyingVisitorStubPtr;
class CNIdentifyingVisitorStub : public CNIdentifyingVisitor {
public:
    static CNIdentifyingVisitorStubPtr getNewInstance() {
        return CNIdentifyingVisitorStubPtr(new CNIdentifyingVisitorStub());
    };

    virtual ~CNIdentifyingVisitorStub() {};
private:
    CNIdentifyingVisitorStub() {};

public:
    virtual void setIdentified(bool identified) {
        this->identified = identified;
    }
    virtual bool hasIdentified() override {
        return identified;
    }
private:
    bool identified = false;
};

#endif //CROSSNATIVE_IDENTIFYINGVISITOR_TESTDOUBLES_H