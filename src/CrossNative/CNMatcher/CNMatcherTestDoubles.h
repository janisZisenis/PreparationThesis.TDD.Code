#ifndef CROSSNATIVE_MATCHER_TESTDOUBLES_H
#define CROSSNATIVE_MATCHER_TESTDOUBLES_H

#include "CNMatcher.h"

class CNMatcherDummy;
typedef std::shared_ptr<CNMatcherDummy> CNMatcherDummyPtr;
class CNMatcherDummy : public CNMatcher {
public:
    static CNMatcherDummyPtr getNewInstance() {
        return CNMatcherDummyPtr(new CNMatcherDummy());
    }
    virtual ~CNMatcherDummy() {};
protected:
    CNMatcherDummy() {};

public:
    virtual bool matches(std::shared_ptr<CNComponent> view) override {
        return false;
    };
};

class CNMatcherStub;
typedef std::shared_ptr<CNMatcherStub> CNMatcherStubPtr;
class CNMatcherStub : public CNMatcherDummy {
public:
    static CNMatcherStubPtr getNewInstance() {
        return CNMatcherStubPtr(new CNMatcherStub());
    }
    virtual ~CNMatcherStub() {};
protected:
    CNMatcherStub() {};

public:
    virtual bool matches(std::shared_ptr<CNComponent> view) override {
        return isMatching;
    };

    virtual void setIsMatching(bool isMatching) {
        this->isMatching = isMatching;
    }

private:
    bool isMatching = false;
};


#endif //CROSSNATIVE_MATCHER_TESTDOUBLES_H