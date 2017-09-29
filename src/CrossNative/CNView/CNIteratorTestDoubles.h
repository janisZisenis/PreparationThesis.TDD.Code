#ifndef CROSSNATIVE_ITERATOR_TESTDOUBLES_H
#define CROSSNATIVE_ITERATOR_TESTDOUBLES_H

#include "CNIterator.h"

class CNIteratorDummy;
typedef std::shared_ptr<CNIteratorDummy> CNIteratorDummyPtr;
class CNIteratorDummy : public CNIterator {
public:
    static CNIteratorDummyPtr getNewInstance() {
        return CNIteratorDummyPtr(new CNIteratorDummy());
    }
    virtual ~CNIteratorDummy() {};
protected:
    CNIteratorDummy() {};

public:
    virtual void first() override {}
    virtual void next() override {}
    virtual bool isDone() override {
        return false;
    }
    virtual std::shared_ptr<CNView> current() override {
        return nullptr;
    }
};

class CNIteratorStub;
typedef std::shared_ptr<CNIteratorStub> CNIteratorStubPtr;
class CNIteratorStub : public CNIteratorDummy {
public:
    static CNIteratorStubPtr getNewInstance() {
        return CNIteratorStubPtr(new CNIteratorStub());
    }
    virtual ~CNIteratorStub() {};
protected:
    CNIteratorStub() {};

public:
    virtual void setIsDone(bool done) {
        this->done = done;
    }
    virtual bool isDone() override {
        return done;
    }

private:
    bool done = false;
};


#endif //CROSSNATIVE_ITERATOR_TESTDOUBLES_H