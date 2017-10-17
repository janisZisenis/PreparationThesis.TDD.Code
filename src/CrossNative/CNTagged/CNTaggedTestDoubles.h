#ifndef CROSSNATIVE_TAGGED_TESTDOUBLES_H
#define CROSSNATIVE_TAGGED_TESTDOUBLES_H

#include "CNTagged.h"

class CNTaggedDummy;
typedef std::shared_ptr<CNTaggedDummy> CNTaggedDummyPtr;

class CNTaggedDummy : public CNTagged {
public:
    static CNTaggedDummyPtr getNewInstance() {
        return CNTaggedDummyPtr(new CNTaggedDummy());
    }
    virtual ~CNTaggedDummy() {}
protected:
    CNTaggedDummy() {}

public:
    virtual std::string getTag() override {
        return std::string();
    }
};

class CNTaggedStub;
typedef std::shared_ptr<CNTaggedStub> CNTaggedStubPtr;

class CNTaggedStub : public CNTagged {
public:
    static CNTaggedStubPtr getNewInstance() {
        return CNTaggedStubPtr(new CNTaggedStub());
    }
    virtual ~CNTaggedStub() {}
protected:
    CNTaggedStub() {}

public:
    virtual void setTag(std::string tag) {
        this->tag = tag;
    }
    virtual std::string getTag() override {
        return tag;
    }

private:
    std::string tag = std::string();
};

#endif //CROSSNATIVE_TAGGED_TESTDOUBLES_H
